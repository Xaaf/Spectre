#ifndef RENDERERBASE_H
#define RENDERERBASE_H

#include "sppch.h"
#include "Spectre/Rendering/Model.h"

namespace Spectre {
/**
 * @brief Holds abstract methods related to a basic renderer instance.
 *
 * Provides the basic structure of a renderer. More importantly, each renderer
 * needs at least the functions contained in this interface to be viable for use
 * in the engine.
 */
class RendererBase {
    public:
        /**
         * @brief Destroy the renderer object.
         *
         */
        virtual ~RendererBase() = default;

        /**
         * @brief Initialise a new renderer.
         *
         * This function is called so that new renderers have an entrypoint at
         * which they can initialise themselves. It is called when a renderer
         * gets created.
         *
         * @return True if the initialisation was a success, false otherwise.
         */
        virtual bool initialise() = 0;

        /**
         * @brief Create a new window with this renderer.
         *
         * This function uses the current in-use renderer to create a new indow.
         *
         * @param title Title for the new window.
         * @param width Width for the new window.
         * @param height Height for the new window.
         * @return True if the window creation was a success, false otherwise.
         */
        virtual bool createWindow(const std::string& title, int width,
                                  int height) = 0;

        /**
         * @brief Update/"Tick" the renderer.
         *
         * This function is called each frame to signal that the renderer should
         * perform an update, e.g. draw a new frame or poll for inputs using a
         * renderer-specific API call.
         */
        virtual void update() = 0;

        /**
         * @brief Stop the renderer.
         *
         * Used as a semi-deconstructor. This function ensures that the renderer
         * gets time to safely stop, e.g. terminating GLFW on OpenGL.
         */
        virtual void stop() = 0;

        void addModel(Model* model) { models.push_back(model); }
        std::vector<Model*> getModels() { return models; }
        void clearModels() { models.clear(); }

    protected:
        std::vector<Model*> models;
};
}  // namespace Spectre

#endif  // RENDERERBASE_H