#include "nyanchu/renderer_opengl.h"
#include "platform/platform_utils.h"

#include <iostream>
#include <fstream>
#include <cstdio>

namespace nyanchu {

struct PosColorVertex
{
    float x, y, z;
    uint32_t abgr;
};

static PosColorVertex s_triangleVertices[] =
{
    {-0.5f, -0.5f,  0.0f, 0xff0000ff }, // Bottom-left, red
    { 0.5f, -0.5f,  0.0f, 0xff00ff00 }, // Bottom-right, green
    { 0.0f,  0.5f,  0.0f, 0xffff0000 }, // Top-middle, blue
};

static bgfx::VertexLayout s_vertexLayout;

// Helper function to load shader binaries
const bgfx::Memory* RendererBGFX::loadShader(const char* _name)
{
    // This path is fragile. It assumes the executable is run from the root of the build directory.
    char filePath[512];
    snprintf(filePath, sizeof(filePath), "shaders/%s", _name);

    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        // Let's try another common path for development
        snprintf(filePath, sizeof(filePath), "../nyanchu_engine/shaders/%s", _name);
        file.open(filePath, std::ios::binary | std::ios::ate);
        if(!file.is_open()){
            std::cerr << "Failed to open shader file at secondary path: " << filePath << std::endl;
            return NULL;
        }
    }

    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    const bgfx::Memory* mem = bgfx::alloc(static_cast<uint32_t>(fileSize));
    if (mem == NULL)
    {
        std::cerr << "Failed to allocate memory for shader: " << filePath << std::endl;
        return NULL;
    }

    file.read(reinterpret_cast<char*>(mem->data), fileSize);
    file.close();

    return mem;
}

RendererBGFX::RendererBGFX()
    : m_vbh(BGFX_INVALID_HANDLE)
    , m_program(BGFX_INVALID_HANDLE)
{
}

RendererBGFX::~RendererBGFX()
{
}

bool RendererBGFX::initialize(GLFWwindow* window, uint32_t width, uint32_t height)
{
    bgfx::PlatformData pd;
    pd.nwh = getNativeWindowHandle(window);

    bgfx::Init bgfxInit;
    bgfxInit.type = bgfx::RendererType::Count;
    bgfxInit.resolution.width = width;
    bgfxInit.resolution.height = height;
    bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
    bgfxInit.platformData = pd;

    if (!bgfx::init(bgfxInit))
    {
        std::cerr << "Failed to initialize BGFX" << std::endl;
        return false;
    }

    // Initialize vertex layout
    s_vertexLayout
        .begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
        .end();

    // Create vertex buffer
    m_vbh = bgfx::createVertexBuffer(
        bgfx::makeRef(s_triangleVertices, sizeof(s_triangleVertices)),
        s_vertexLayout
    );

    // Load shaders and create program
    bgfx::ShaderHandle vsh = bgfx::createShader(loadShader("vs_triangle.bin"));
    bgfx::ShaderHandle fsh = bgfx::createShader(loadShader("fs_triangle.bin"));
    if (!bgfx::isValid(vsh) || !bgfx::isValid(fsh)) {
        std::cerr << "Failed to load shaders" << std::endl;
        return false;
    }
    m_program = bgfx::createProgram(vsh, fsh, true);

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);

    return true;
}

void RendererBGFX::render()
{
    bgfx::setViewRect(0, 0, 0, 800, 600);
    bgfx::touch(0);

    // Set vertex buffer
    bgfx::setVertexBuffer(0, m_vbh);

    // Set render states.
    bgfx::setState(BGFX_STATE_DEFAULT);

    // Submit primitive for rendering to view 0.
    bgfx::submit(0, m_program);

    // bgfx::frame() is now called in Engine::endFrame()
}

void RendererBGFX::shutdown()
{
    bgfx::destroy(m_vbh);
    bgfx::destroy(m_program);
    bgfx::shutdown();
}

void RendererBGFX::drawMesh(const char* meshName) {
    // Placeholder implementation
    std::cout << "Drawing mesh: " << meshName << std::endl;
    // In a real implementation, this would involve loading mesh data,
    // setting up different vertex/index buffers, and submitting a draw call.
}

} // namespace nyanchu
