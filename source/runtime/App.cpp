#include "App.h"

namespace solis
{
        void SolisApp::initWindow(int width, int height) {
            glfwInit();

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

            window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);
        }

        void SolisApp::initVulkan() {

        }

        void SolisApp::mainLoop() {
            while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();
            }
        }

        void SolisApp::cleanup() {
            glfwDestroyWindow(window);

            glfwTerminate();
        }
}
