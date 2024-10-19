#ifndef RENDERER_H
#define RENDERER_H

#include "sppch.h"
#include "Spectre/Rendering/Model.h"
#include "Spectre/Rendering/RendererBase.h"

namespace Spectre {
/**
 * @brief Enum holding the different renderer types which are supported.
 */
enum class RendererType { OpenGL, Vulkan };

/**
 * @brief Singleton renderer factory.
 *
 * This class is reponsible for creating a renderer when the engine starts up.
 * Therefore, it also holds a reference to an instance of a `RendererInterface`.
 * It also holds some quality-of-life methods, e.g. `stringToRenderType`.
 */
class Renderer {
    private:
        /**
         * @brief Singleton instance of the Renderer class.
         */
        static Renderer* m_Instance;

        /**
         * @brief Reference to the renderer used.
         *
         * This holds a reference to the specific render API that is being used,
         * e.g. an `OpenGLRenderer` instance.
         */
        static std::shared_ptr<RendererBase> m_Renderer;

    private:
        /**
         * @brief Construct a new Renderer.
         *
         * This constructor is private in order to facilitate the singleton
         * design pattern the class follows.
         */
        Renderer() = default;

    public:
        /**
         * @brief Get the singleton instance of the Renderer class.
         *
         * This function provides access to the singleton instance of the
         * Renderer class. If this instance does not exist, it will be created.
         *
         * @return Pointer to the singleton instance of the Renderer class.
         */
        static Renderer* getInstance();

        /**
         * @brief Get the current renderer.
         *
         * @return The current renderer instance, e.g. an `OpenGLRenderer`.
         */
        static std::shared_ptr<RendererBase> getRenderer();

        /**
         * @brief Create a new renderer.
         *
         * This function creates (and therefore defines `m_Renderer`) a new
         * renderer of the given `RendererType`.
         *
         * @param type Type of renderer that should be created.
         * @return True if the renderer was created succesfully, false
         * otherwise.
         */
        static bool createRenderer(RendererType type);

        /**
         * @brief Converts a `std::string` to a `RenderType`.
         *
         * @param renderer Renderer to convert from a `std::string`.
         * @return Renderer as a `RenderType`.
         */
        static RendererType stringToRenderType(const std::string& renderer);
};
}  // namespace Spectre

#endif  // RENDERER_H