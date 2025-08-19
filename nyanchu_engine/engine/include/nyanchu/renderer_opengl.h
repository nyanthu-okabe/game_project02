#pragma once

#include "renderer.h" // Include the IRenderer interface
#include <bgfx/bgfx.h>
#include <cstdint>

// Forward declare GLFWwindow
struct GLFWwindow;

namespace nyanchu {

// Concrete BGFX implementation
class RendererBGFX : public IRenderer
{
public:
    RendererBGFX();
    ~RendererBGFX() override;

    bool initialize(GLFWwindow* window, uint32_t width, uint32_t height) override;
    void render() override;
    void shutdown() override;

    void drawMesh(const char* meshName) override;

private:
    bgfx::VertexBufferHandle m_vbh;
    bgfx::ProgramHandle m_program;

    // Helper function to load shader binaries
    static const bgfx::Memory* loadShader(const char* _name);
};

} // namespace nyanchu