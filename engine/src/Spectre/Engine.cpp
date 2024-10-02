#include "Spectre/Engine.h"

using namespace Spectre;

Engine* Engine::instance = nullptr;

Engine::Engine() {}
Engine::~Engine() {}

Engine* Engine::getInstance() {
    if (instance == nullptr) {
        instance = new Engine();
    }

    return instance;
}

void Engine::initialise(const std::string& title, const std::string& renderer) {
    LOG_INFO("Engine", "Initialising with name '"
                           << title << "' (renderer: " << renderer << ")");
}

void Engine::step() {
    // ../
}

void Engine::stop() {
    m_IsRunning = false;
    // m_Window->close();
}

bool Engine::isRunning() const { return m_IsRunning; }
