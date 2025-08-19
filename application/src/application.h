#pragma once

#include <nyanchu/engine.h>
#include <memory>

class Application
{
public:
    Application();
    ~Application();

    bool initialize();
    void run();
    void shutdown();

private:
    std::unique_ptr<nyanchu::Engine> m_engine;
};