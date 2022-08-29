#include "RenderInterface.h"

#include <iostream>
#include <vector>

namespace solis
{
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
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        // 全局验证层
        createInfo.enabledLayerCount = 0;

        // 导致VK创建失败
        VkResult ret = vkCreateInstance(&createInfo, nullptr, &instance_);
        if (ret != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance");
        }

        // 在这里检查一下支持哪些扩展
        uint32_t extensionCount{0};
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::cout << "available extensions:" << extensionCount
                  << std::endl;
        for (const auto &extension : extensions)
        {
            std::cout << '\t' << extension.extensionName << '\n';
        }
    }

    RenderInterface::~RenderInterface()
    {
        std::cout << "render interface over \n"; 
        vkDestroyInstance(instance_, nullptr);
    }
}