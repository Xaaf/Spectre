#ifndef WINDOW_H
#define WINDOW_H

#include "Spectre/Rendering/Renderer.h"
#include "Spectre/Rendering/RendererInterface.h"
#include "sppch.h"

namespace Spectre {
/**
 * @brief Instance of a Window using the Spectre engine.
 */
class Window {
    private:
        /**
         * @brief Name of the window.
         */
        std::string m_WindowName;

        /**
         * @brief Width of the window.
         */
        int m_Width;

        /**
         * @brief Height of the window.
         */
        int m_Height;

    public:
        /**
         * @brief Construct a new Window object.
         *
         * This constructor creates a new Window object for a given
         * `RendererType`.
         *
         * @param window_name Name for the new window.
         * @param width Width for the new window.
         * @param height Height for the new window.
         * @param rendererType Renderer for the new window.
         */
        Window(std::string window_name, int width, int height,
               RendererType rendererType);

        /**
         * @brief Destroy the Window object.
         */
        ~Window();

        /**
         * @brief Create the actual window with the renderer.
         *
         * This function calls the renderer to actually create a window with the
         * information passed in the constructor.
         *
         * @return True if the window was created succesfully, false otherwise.
         */
        bool create();

        /**
         * @brief Update this window.
         *
         * This function handles updating this window, including calling the
         * renderer's update function.
         */
        void update();

        /**
         * @brief Closes this window.
         *
         * This function handles closing this window, including telling the
         * renderer that it can stop.
         */
        void close();
};
}  // namespace Spectre

#endif  // WINDOW_H