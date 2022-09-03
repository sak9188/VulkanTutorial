#ifndef __RENDERINTERFACE_H__
#define __RENDERINTERFACE_H__

#define GLFW_INCLUDE_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#include "GLFW/glfw3.h"
#include "Config.h"

#include <vector>
#include <memory>

namespace solis
{
    // RHI 渲染硬件接口
    class SOLIS_API RenderInterface
    {
    public:
        RenderInterface(GLFWwindow* window);

        virtual ~RenderInterface();

    private:
        static const std::vector<const char*> validationLayers;

        GLFWwindow* window_;

        // Instance
        VkInstance instance_;

        // GPU
        VkPhysicalDevice physicalDevice_;

        // Logic Device
        VkDevice device_;

        // Debug Messager
        VkDebugUtilsMessengerEXT debugMessenger_;

        // Queue Family
        uint32_t graphicsQueueFamilyIndex_;

        // Queue
        VkQueue graphicsQueue_;

        // surface
        VkSurfaceKHR surface_;

        // 获得层的扩展
        std::vector<const char*> getRequiredExtensions();

        // 是否开启验证层
        constexpr bool validationEnable() 
        {
            #ifdef VK_VALIDATION_REQURED
                return true;
            #else:
                return false;
            #endif
        }

        // 检查验证层是否支持
        bool checkValidationLayerSupport();

        // 创建Vulkan Debug Messenger
        void enableDebugMessenger();
        void disableDebugMessenger();

        // 初始化Vulkan的Instance
        void initVulkan();

        // 创建Vulkan的Surface
        void initSurface();

        // 创建Vulkan PhyInstance
        void initPhysicalDevice();

        // 初始化Quue
        VkDeviceQueueCreateInfo initQueue();

        // 初始化逻辑设备
        void initDevice();

    };
} // namespace solisc

#endif