#pragma once

#include <cstdint>

// Forward declare GLFWwindow
struct GLFWwindow;

namespace nyanchu {

// Abstract base class for renderers
class IRenderer
{
public:
    virtual ~IRenderer() = default;

    virtual bool initialize(GLFWwindow* window, uint32_t width, uint32_t height) = 0;
    virtual void render() = 0;
    virtual void shutdown() = 0;

    virtual void drawMesh(const char* meshName) = 0;
};

} // namespace nyanchu