#include "Spectre/Engine.h"

using namespace Spectre;

Engine* Engine::instance = nullptr;

Engine::Engine() { m_IsRunning = false; }
Engine::~Engine() { delete m_Window; }

Engine* Engine::getInstance() {
    if (instance == nullptr) {
        instance = new Engine();
    }

    return instance;
}

void Engine::initialise(const std::string& title, const std::string& renderer) {
    LOG_INFO("Engine", "Initialising with name '"
                           << title << "' (renderer: " << renderer << ")");

    m_Window =
        new Window(title, 1280, 720, Renderer::stringToRenderType(renderer));
    if (!m_Window->create()) {
        LOG_ERROR("Engine", "Unable to create a window. Exiting...");
        exit(-1);
    }

    m_IsRunning = true;
}

void Engine::step() { m_Window->update(); }

void Engine::stop() {
    m_IsRunning = false;
    m_Window->close();
}

bool Engine::isRunning() const { return m_IsRunning; }
