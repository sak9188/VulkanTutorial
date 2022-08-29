#include "Config.h"

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

namespace solis
{
    class SOLIS_API SolisApp{
    public:
        void run() {
            initWindow();
            initVulkan();
            mainLoop();
            cleanup();
        }

    private:
        GLFWwindow* window;

        void initWindow(int width=800, int height=600);

        void initVulkan();

        void mainLoop();

        void cleanup();
    };
}
