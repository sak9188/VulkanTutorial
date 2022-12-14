#include "RenderInterface.h"

#include <iostream>
#include <cstring>

#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

namespace solis
{
    const std::vector<const char*> RenderInterface::validationLayers = {
        "VK_LAYER_KHRONOS_validation" 
    };

    RenderInterface::RenderInterface(GLFWwindow* window) : window_(window)
    {
        // init vulkan instance
        initVulkan();

        // init surface
        initSurface();

        // 初始化物理设备
        initPhysicalDevice();

        // 初始化逻辑设备
        initDevice();
    }

    RenderInterface::~RenderInterface()
    {
        std::cout << "render interface over \n"; 

        if(device_ != nullptr)
        {
            vkDestroyDevice(device_, nullptr);
        }

        if(surface_ != nullptr)
        {
            vkDestroySurfaceKHR(instance_, surface_, nullptr);
        }

        disableDebugMessenger();

        if(instance_ != nullptr)
        {
            vkDestroyInstance(instance_, nullptr);
        }
    }

    void RenderInterface::initVulkan()
    {
        // 初始化Vulkan
        // VKAppInfo
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Traingle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "solis";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        // CreateInfo
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // Vulkan 扩展
        auto extensions = getRequiredExtensions();

        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        // Vulkan 全局验证层
        if(validationEnable())
        {
            if (!checkValidationLayerSupport())
            {
                throw std::runtime_error("validation layers required, bug not available!");
            }

            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        // 导致VK创建失败
        VkResult ret = vkCreateInstance(&createInfo, nullptr, &instance_);
        if (ret != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance");
        }
    }

    std::vector<const char*> RenderInterface::getRequiredExtensions()
    {
        // 在这里检查一下支持哪些扩展
        uint32_t extensionCount{0};
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensionsProperties(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionsProperties.data());

        std::cout << "available extensions:" << extensionCount
                  << std::endl;
        for (const auto& extension : extensionsProperties)
        {
            std::cout << '\t' << extension.extensionName << '\n';
        }

        // 这里载入需要的扩展
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if(validationEnable())
        {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        // 这里检验一下是否发生移动了
        return extensions;
    }


    bool RenderInterface::checkValidationLayerSupport()
    {
        uint32_t layerCount;

        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> avaliableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, avaliableLayers.data());

        std::cout << "available layers:" << layerCount
                  << std::endl;
        for (const auto &layer: avaliableLayers)
        {
            std::cout << '\t' << layer.layerName<< '\n';
        }

        for(const char* layerName : validationLayers)
        {
            for(const auto& layerProperties : avaliableLayers) 
            {
                if(strcmp(layerName, layerProperties.layerName) == 0)
                {
                    return true;
                }
            }
        }

        return false;
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData)
    {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }

    void RenderInterface::enableDebugMessenger()
    {
        if (!validationEnable())
        {
            return;
        }

        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;

        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance_, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            if(func(instance_, &createInfo, nullptr, &debugMessenger_) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to set up debug messenger!");
            }
        }
    }

    void RenderInterface::disableDebugMessenger()
    {
        if(debugMessenger_ != nullptr)
        {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance_, "vkDestroyDebugUtilsMessengerEXT");
            if (func != nullptr)
            {
                func(instance_, debugMessenger_, nullptr);
            }
        }
    }

    bool isDeviceSuitable(VkPhysicalDevice deviece)
    {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;

        vkGetPhysicalDeviceProperties(deviece, &deviceProperties);
        vkGetPhysicalDeviceFeatures(deviece, &deviceFeatures);

        std::cout << "device name: " << deviceProperties.deviceName << std::endl;
        std::cout << "device api version: " << deviceProperties.apiVersion << std::endl;
        std::cout << "device driver version: " << deviceProperties.driverVersion << std::endl;
        std::cout << "device vendor id: " << deviceProperties.vendorID << std::endl;
        std::cout << "device device id: " << deviceProperties.deviceID << std::endl;
        std::cout << "device type: " << deviceProperties.deviceType << std::endl;

        return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
    }

    void RenderInterface::initSurface()
    {
        VkWin32SurfaceCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        createInfo.hwnd = glfwGetWin32Window(window_);
        createInfo.hinstance = GetModuleHandle(nullptr);

        if(glfwCreateWindowSurface(instance_, window_, nullptr, &surface_) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void RenderInterface::initPhysicalDevice()
    {
        // 在这里检查一下支持哪些设备
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance_, &deviceCount, nullptr);
        if (deviceCount == 0)
        {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance_, &deviceCount, devices.data());
        for (const auto& device : devices)
        {
            if (isDeviceSuitable(device))
            {
                physicalDevice_ = device;
                break;
            }
        }

        if (physicalDevice_ == VK_NULL_HANDLE)
        {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    VkDeviceQueueCreateInfo RenderInterface::initQueue()
    {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice_, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice_, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies)
        {
            if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                graphicsQueueFamilyIndex_ = i;
                break;
            }
            i++;
        }

        // 初始化Queue
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = graphicsQueueFamilyIndex_;
        queueCreateInfo.queueCount = 1;
        float queuePriority = 1.0f;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        return queueCreateInfo;
    }

    void RenderInterface::initDevice()
    {
        // init Vk logical device
        VkDeviceCreateInfo deviceCreateInfo{};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        auto queueCreateInfo = initQueue();
        deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
        deviceCreateInfo.queueCreateInfoCount = 1;

        VkPhysicalDeviceFeatures deviceFeatures{};
        deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

        if(vkCreateDevice(physicalDevice_, &deviceCreateInfo, nullptr, &device_) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create logical device!");
        }

        // init Vk queue
        vkGetDeviceQueue(device_, graphicsQueueFamilyIndex_, 0, &graphicsQueue_);
    }

}