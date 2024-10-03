#include "Spectre/Rendering/Renderer.h"
#include "Spectre/Rendering/Arch/OpenGL/OpenGLRenderer.h"

using namespace Spectre;

Renderer* Renderer::m_Instance = nullptr;
std::shared_ptr<RendererInterface> Renderer::m_Renderer = nullptr;

Renderer* Renderer::getInstance() {
    if (m_Instance == nullptr) {
        LOG_TRACE("Renderer", "There is no renderer! Creating one now.");
        m_Instance = new Renderer();
    }

    return m_Instance;
}

bool Renderer::createRenderer(RendererType type) {
    switch (type) {
        case RendererType::OpenGL:
            m_Renderer = std::make_shared<OpenGLRenderer>();
            m_Renderer->initialise();

            return true;
        case RendererType::Vulkan:
            LOG_ERROR("Renderer",
                      "Trying to create a Vulkan renderer, but Vulkan isn't "
                      "supported!");
            return false;
        default:
            LOG_ERROR("Renderer", "Unknown renderer!");
            return false;
    }
}

std::shared_ptr<RendererInterface> Renderer::getRenderer() {
    return m_Renderer;
}

RendererType Renderer::stringToRenderType(const std::string& renderer) {
    if (renderer == "Vulkan") {
        return RendererType::Vulkan;
    } else {
        // If we get some string we don't recognise, just use OpenGL
        return RendererType::OpenGL;
    }
}
