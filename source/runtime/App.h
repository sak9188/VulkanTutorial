#ifndef __APP_H__
#define __APP_H__

#include "Config.h"

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "memory"

#include "RenderInterface.h"

namespace solis
{
    class SOLIS_API SolisApp{
    public:
        void Run();

    private:
        std::unique_ptr<RenderInterface> renderer_;

        GLFWwindow* window_;

        void InitWindow(int width=800, int height=600);

        void InitVulkan();

        void MainLoop();

        void CleanUp();
    };
}

#endif