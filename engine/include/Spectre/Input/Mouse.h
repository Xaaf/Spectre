#ifndef MOUSE_H
#define MOUSE_H

#include "sppch.h"
#include <glm/vec2.hpp>
#include "InputCodes.h"

namespace Spectre {
/**
 * @brief Manages mouse input for the engine.
 *
 * Provides a singleton interface to handle mouse events. It allows registering
 * per-button actions, as well as keeping account of the mouse's X and Y
 * positions. Also, it allows for querying the different mouse buttons and
 * position through their respective methods.
 */
class Mouse {
    private:
        /**
         * @brief Singleton instance of the Mouse class.
         */
        static Mouse* instance;

    private:
        /**
         * @brief Construct a new Mouse.
         *
         * This constructor is private in order to facilitate the singleton
         * design pattern the class follows.
         */
        Mouse();

        /**
         * @brief Destroy the Mouse object.
         */
        ~Mouse();

    public:
        /**
         * @brief Get the singleton instance of the Mouse class.
         *
         * This function provides access to the singleton instance of the
         * Mouse class. If this instance does not exist, it will be created.
         *
         * @return Pointer to the singleton instance of the Mouse class.
         */
        static Mouse* getInstance();

        /**
         * @brief Registers a mouse action.
         *
         * This function registers an action related to mouse input, e.g.
         * pressing or releasing a specific mouse button.
         *
         * @param button The keycode representing the mouse button which fired
         * the event.
         * @param action The action that triggered the event.
         */
        static void registerAction(int button, int action);

        /**
         * @brief Registers a mouse movement.
         *
         * This function registers a mouse movement, updating the current X and
         * Y positions of the mouse. These being tracked in the Mouse instance
         * through this function.
         *
         * @param newX The new X position of the mouse, relative to the game
         * window.
         * @param newY The new Y position of the mouse, relative to the game
         * window.
         */
        static void registerMove(double newX, double newY);

        /**
         * @brief Checks if a mouse button is currently being pressed down.
         *
         * @param button The keycode representing the mouse button to check.
         * @return True if the mouse button is being held down, false otherwise.
         */
        static bool isButtonDown(int button);

        /**
         * @brief Checks if a mouse button has been pressed.
         *
         * @param key The keycode representing the mouse button to check.
         * @return True if the mouse button has been pressed, false otherwise.
         */
        static bool isButtonPressed(int button);

        /**
         * @brief Get the current mouse position.
         *
         * This function returns the current position of the mouse, which is
         * being tracked in the Mouse instance.
         *
         * @return The mouse's X and Y posititions in a Vector2.
         */
        static glm::vec2 getMousePosition();
};
}  // namespace Spectre

#endif  // MOUSE_H