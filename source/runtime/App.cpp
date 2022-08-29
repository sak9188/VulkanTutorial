#include "App.h"

namespace solis
{
    void SolisApp::Run()
    {
        InitWindow();
        InitVulkan();
        MainLoop();
        CleanUp();
    }

    void SolisApp::InitWindow(int width, int height) {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window_ = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);
    }

    void SolisApp::InitVulkan() {

    }

    void SolisApp::MainLoop() {
        while (!glfwWindowShouldClose(window_)) {
            glfwPollEvents();
        }
    }

    void SolisApp::CleanUp() {
        glfwDestroyWindow(window_);

        glfwTerminate();
    }
}
