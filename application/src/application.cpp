#include "application.h"
#include <iostream>

Application::Application()
{
    m_engine = std::make_unique<nyanchu::Engine>();
}

Application::~Application()
{
}

bool Application::initialize()
{
    m_engine->init();
    return true;
}

void Application::run()
{
    while (m_engine->isRunning())
    {
        m_engine->pollEvents();
        m_engine->beginFrame();

        // From design doc
        m_engine->getRenderer().drawMesh("/Users/riookabe/Desktop/nyanthu/nyanthu - game/project_back/application/materials/con.obj");
        m_engine->getAudio().playSound("/Users/riookabe/Desktop/nyanthu/nyanthu - game/project_back/application/materials/bgm.wav");

        m_engine->endFrame();
    }
}

void Application::shutdown()
{
    m_engine->shutdown();
}
