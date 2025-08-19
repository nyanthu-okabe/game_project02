#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#include <GLFW/glfw3.h>

// Manually declare glfwGetCocoaWindow with extern "C"
extern "C" {
    id glfwGetCocoaWindow(GLFWwindow* window);
}

#include "platform_utils.h"

// Function to get the Metal layer from a GLFW window
void* getNativeWindowHandle(GLFWwindow* window) {
    NSWindow *nswin = glfwGetCocoaWindow(window);
    if (nswin.contentView.layer == nil) {
        [nswin.contentView setWantsLayer:YES];
        CAMetalLayer* layer = [CAMetalLayer layer];
        nswin.contentView.layer = layer;
    }
    return (__bridge void*)nswin.contentView.layer;
}