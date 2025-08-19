#include "platform_utils.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

void* getNativeWindowHandle(GLFWwindow* window) {
    return (void*)glfwGetWin32Window(window);
}
