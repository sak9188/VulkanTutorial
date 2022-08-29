#ifndef __RENDERINTERFACE_H__
#define __RENDERINTERFACE_H__

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "Config.h"

namespace solis
{
    class SOLIS_API RenderInterface
    {
    public:
        RenderInterface();

        virtual ~RenderInterface();
    private:
        VkInstance instance_;
    };
} // namespace solisc

#endif