#include "RenderInterface.h"

#include <iostream>
#include <cstring>

namespace solis
{
    const std::vector<const char*> RenderInterface::validationLayers = {
        "VK_LAYER_KHRONOS_validation" 
    };

    RenderInterface::RenderInterface()
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
        auto&& extensions = getRequiredExtensions();
        std::cout << "after move 0:" << &extensions << "\n";
        std::cout << "after move 1:" << static_cast<void*>(extensions.data()) << "\n";

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

    RenderInterface::~RenderInterface()
    {
        std::cout << "render interface over \n"; 
        vkDestroyInstance(instance_, nullptr);
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
        std::cout << "before move 0:" << &extensions << "\n";
        std::cout << "before move 1:" << static_cast<void*>(extensions.data()) << "\n";

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
}