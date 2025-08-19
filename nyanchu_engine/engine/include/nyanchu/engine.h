#pragma once

#include "renderer.h"
#include "audio.h"

#include <memory>

// Forward declare GLFWwindow
struct GLFWwindow;

namespace nyanchu {

class Engine {
public:
    Engine();
    ~Engine();

    void init();
    void shutdown();
    bool isRunning();

    void pollEvents();
    void beginFrame();
    void endFrame();

    IRenderer& getRenderer();
    Audio& getAudio();

private:
    GLFWwindow* m_window;
    std::unique_ptr<IRenderer> m_renderer;
    std::unique_ptr<Audio> m_audio;
    bool m_isRunning = true;
};

} // namespace nyanchu