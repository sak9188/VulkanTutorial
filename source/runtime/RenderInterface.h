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

        VkInstance instance_;

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

        
    };
} // namespace solisc

#endif