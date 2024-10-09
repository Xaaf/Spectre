#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "Spectre/Engine.h"
#include "Spectre/Rendering/RendererInterface.h"
#include "sppch.h"

namespace Spectre {
class OpenGLRenderer : public RendererInterface {
    private:
        GLFWwindow* m_Window;

        std::string m_WindowName;
        int m_Width;
        int m_Height;

    private:
        void resizeCallback(GLFWwindow* window, int width, int height);

    public:
        bool initialise() override;
        bool createWindow(const std::string& title, int width,
                          int height) override;

        void update() override;
        void stop() override;
};
}  // namespace Spectre

#endif  // OPENGLRENDERER_H