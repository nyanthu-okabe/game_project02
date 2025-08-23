#include "platform_utils.h"

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

void* getNativeWindowHandle(GLFWwindow* window) {
    return (void*)glfwGetX11Window(window);
}
