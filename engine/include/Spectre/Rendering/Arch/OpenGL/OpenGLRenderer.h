#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "sppch.h"
#include "Spectre/Engine.h"
#include "Spectre/Rendering/Arch/OpenGL/OpenGLShader.h"
#include "Spectre/Rendering/RendererBase.h"

namespace Spectre {
/**
 * @brief OpenGL implementation of the RendererBase.
 *
 * Uses the OpenGL API (through glfw) to handle rendering.
 */
class OpenGLRenderer : public RendererBase {
    private:
        /**
         * @brief Reference to the GLFW window struct.
         */
        GLFWwindow* m_Window;

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

    private:
        /**
         * @brief Callback for when the window gets resized.
         *
         * This function gets called by GLFW when the window gets resized. It
         * follows the `GLFWwindowsizefun` spec for its parameters.
         *
         * @param window Window that got resized.
         * @param width Width after resizing.
         * @param height Height after resizing.
         */
        void resizeCallback(GLFWwindow* window, int width, int height);

    public:
        /**
         * @brief Handles OpenGL's initialisation steps.
         *
         * This function makes sure that the renderer is ready to go. It makes
         * sure that GLFW is initialised, so that we can use the OpenGL calls we
         * want to use.
         *
         * @return True if the initialisation was a success, false otherwise.
         */
        bool initialise() override;

        /**
         * @brief Create a new window using OpenGL.
         *
         * This function creates a new OpenGL window, by calling
         * `glfwCreateWindow`. It then initialies GLAD, after which we can
         * finally use any OpenGL calls we desire. Finally, it setes a few
         * callbacks for things like input handling.
         *
         * @param title Title for the new window.
         * @param width Width for the new window.
         * @param height Height for the new window.
         * @return True if the window creation was a success, false otherwise.
         */
        bool createWindow(const std::string& title, int width,
                          int height) override;

        /**
         * @brief Update/"Tick" this renderer.
         *
         * This function is called each frame to signal that this renderer
         * should perform an update, e.g. draw a new frame or poll for inputs
         * using GLFW.
         */
        void update() override;

        /**
         * @brief Stop the renderer.
         *
         * Used as a semi-deconstructor. This function ensures that the renderer
         * gets time to safely stop, e.g. by calling `glfwTerminate`.
         */
        void stop() override;
};
}  // namespace Spectre

#endif  // OPENGLRENDERER_H