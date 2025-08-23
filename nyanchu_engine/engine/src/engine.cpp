#include "nyanchu/engine.h"
#include <GLFW/glfw3.h>
#include <iostream>

#ifdef __APPLE__
#include "nyanchu/renderer_metal.h"
#else
#include "nyanchu/renderer_opengl.h"
#endif

namespace nyanchu {

Engine::Engine() : m_window(nullptr) {}

Engine::~Engine() {
    // shutdown should be called explicitly
}

void Engine::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    // For now, let's create a window here. This might be configurable later.
    m_window = glfwCreateWindow(800, 600, "Nyanthu Engine", NULL, NULL);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_window);

    #ifdef __APPLE__
    m_renderer = std::make_unique<RendererMetal>();
#else
    m_renderer = std::make_unique<RendererBGFX>();
#endif
    if (!m_renderer->initialize(m_window, 800, 600)) {
        std::cerr << "Failed to initialize Renderer" << std::endl;
        return;
    }

    m_audio = std::make_unique<Audio>();

    m_isRunning = true;
    std::cout << "Engine initialized" << std::endl;
}

void Engine::shutdown() {
    m_renderer->shutdown();
    glfwDestroyWindow(m_window);
    glfwTerminate();
    std::cout << "Engine shutdown" << std::endl;
}

bool Engine::isRunning() {
    return m_isRunning && !glfwWindowShouldClose(m_window);
}

void Engine::pollEvents() {
    glfwPollEvents();
}

void Engine::beginFrame() {
    // Nothing for now
}

void Engine::endFrame() {
    m_renderer->render(); // This will contain the bgfx::frame() call
    glfwSwapBuffers(m_window);
}

IRenderer& Engine::getRenderer() {
    return *m_renderer;
}

Audio& Engine::getAudio() {
    return *m_audio;
}

} // namespace nyanchu
