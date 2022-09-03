#ifndef __RENDERINTERFACE_H__
#define __RENDERINTERFACE_H__

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include "Config.h"

#include <vector>

namespace solis
{
    // RHI 渲染硬件接口
    class SOLIS_API RenderInterface
    {
    public:
        RenderInterface();

        virtual ~RenderInterface();


    private:
        static const std::vector<const char*> validationLayers;

        // Instance
        VkInstance instance_;

        // GPU
        VkPhysicalDevice physicalDevice_;

        // Logic Device
        VkDevice device_;

        VkDebugUtilsMessengerEXT debugMessenger_;

        // Queue Family
        uint32_t graphicsQueueFamilyIndex_;

        // Queue
        VkQueue graphicsQueue_;

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

        // 创建Vulkan PhyInstance
        void initPhysicalDevice();

        // 初始化Quue
        VkDeviceQueueCreateInfo initQueue();

        // 初始化逻辑设备
        void initDevice();

    };
} // namespace solisc

#endif