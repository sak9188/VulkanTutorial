#ifndef __RENDERINTERFACE_H__
#define __RENDERINTERFACE_H__

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

namespace solis
{
    class SOLIS_API RenderInterface
    {
    public:
        RenderInterface()
        {
            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "Hello Traingle";
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        }

    private:
        VkInstance instance_;
    

    };
} // namespace solisc

#endif