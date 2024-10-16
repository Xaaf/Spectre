#ifndef ENGINE_H
#define ENGINE_H

#include "Spectre/Rendering/Renderer.h"
#include "Spectre/Rendering/RendererBase.h"
#include "Spectre/Rendering/Window.h"
#include "sppch.h"

namespace Spectre {
/**
 * @brief Main engine class, responsible for managing the game loop, rendering,
 * etc.
 *
 * Provides a singleton interface which manages the overall state of the engine,
 * including the game loop, window creation, rendering, input polling, etc. It
 * provides methods to initialise the engine, step through frames, and shut it
 * down.
 */
class Engine {
    private:
        /**
         * @brief Pointer to the main application window.
         */
        Window* m_Window;

        /**
         * @brief Boolean flag indication whether the engine is currently
         * running.
         */
        bool m_IsRunning;

        /**
         * @brief Singleton instance of the Engine class.
         */
        static Engine* instance;

    private:
        /**
         * @brief Construct a new Engine.
         *
         * This constructor is private in order to facilitate the singleton
         * design pattern the class follows.
         */
        Engine();

        /**
         * @brief Destroy the Engine object.
         */
        ~Engine();

    public:
        /**
         * @brief Get the singleton instance of the Engine class.
         *
         * This function provides access to the singleton instance of the
         * Engine class. If this instance does not exist, it will be created.
         *
         * @return Pointer to the singleton instance of the Engine class.
         */
        static Engine* getInstance();

        /**
         * @brief Initialises the engine for use.
         *
         * This function is responsible for initialising the engine, performing
         * whatever needs to be done to be ready for usage in an application.
         *
         * @param title Title of the application.
         * @param renderer Renderer for the application's window.
         */
        void initialise(const std::string& title, const std::string& renderer);

        /**
         * @brief Steps through a frame in the engine.
         *
         * This function is responsible for making sure that all subsystems get
         * called to do their per-frame actions, e.g. rendering a frame or
         * polling inputs.
         */
        void step();

        /**
         * @brief Stops the engine, shutting it down.
         */
        void stop();

        /**
         * @brief Checks whether the engine is running.
         *
         * @return True if the engine is running, false otherwise.
         */
        bool isRunning() const;
};
}  // namespace Spectre

#endif  // ENGINE_H