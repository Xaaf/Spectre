#include "Spectre/Rendering/Window.h"

using namespace Spectre;

Window::Window(std::string title, int width, int height,
               RendererType rendererType) {
    LOG_TRACE("Window", "Calling Window::constructor");
    Renderer::getInstance();
    Renderer::createRenderer(rendererType);

    m_WindowName = title;
    m_Width = width;
    m_Height = height;
}

Window::~Window() { LOG_TRACE("Window", "Calling Window::destructor"); }

bool Window::create() {
    LOG_TRACE("Window", "Calling Window::create");
    LOG_INFO("Window", "Creating new Window");

    if (!Renderer::getRenderer()->createWindow(m_WindowName, m_Width, m_Height)) {
        LOG_ERROR("Window", "Failed to create new Window!");
        return false;
    }

    return true;
}

void Window::update() {
    Renderer::getRenderer()->render();
}

void Window::close() {
    LOG_TRACE("Window", "Calling Window::close");
    Renderer::getRenderer()->stop();
}