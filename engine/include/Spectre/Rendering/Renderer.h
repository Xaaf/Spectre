#ifndef RENDERER_H
#define RENDERER_H

#include "Spectre/Rendering/RendererInterface.h"
#include "sppch.h"

namespace Spectre {
enum class RendererType { OpenGL, Vulkan };

class Renderer {
    private:
        static Renderer* m_Instance;

        static std::shared_ptr<RendererInterface> m_Renderer;

    private:
        Renderer() = default;

    public:
        static Renderer* getInstance();
        static std::shared_ptr<RendererInterface> getRenderer();

        static bool createRenderer(RendererType type);
        static RendererType stringToRenderType(const std::string& renderer);
};
}  // namespace Spectre

#endif  // RENDERER_H