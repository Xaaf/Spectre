#ifndef WINDOW_H
#define WINDOW_H

#include "Spectre/Rendering/Renderer.h"
#include "Spectre/Rendering/RendererInterface.h"
#include "sppch.h"

namespace Spectre {
class Window {
    private:
        std::string m_WindowName;
        int m_Width;
        int m_Height;

    public:
        Window(std::string window_name, int width, int height,
               RendererType rendererType);
        ~Window();

        bool create();
        void update();
        void close();
        void stop();
};
}  // namespace Spectre

#endif  // WINDOW_H