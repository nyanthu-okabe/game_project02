#pragma once

#include "renderer.h"

// Forward declare GLFWwindow
struct GLFWwindow;

namespace nyanchu {

class RendererMetal : public IRenderer
{
public:
    RendererMetal();
    ~RendererMetal() override;

    bool initialize(GLFWwindow* window, uint32_t width, uint32_t height) override;
    void render() override;
    void shutdown() override;

    void drawMesh(const char* meshName) override;
};

} // namespace nyanchu