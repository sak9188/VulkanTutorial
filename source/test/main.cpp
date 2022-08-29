#define GLFW_INCLUDE_VULKAN

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "App.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

int main() {
    solis::SolisApp app;

    try
    {
        app.Run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}