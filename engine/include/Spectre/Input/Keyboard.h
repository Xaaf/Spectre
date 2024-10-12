#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "InputCodes.h"
#include "sppch.h"

namespace Spectre {
/**
 * @brief Manages keyboard input for the engine.
 *
 * Provides a singleton interface to handle keyboard events. It allows
 * registering per-key actions and the querying of said keys through their
 * respective methods.
 */
class Keyboard {
    private:
        /**
         * @brief Singleton instance of the Keyboard class.
         */
        static Keyboard* instance;

    private:
        /**
         * @brief Construct a new Keyboard
         *
         * This constructor is private in order to facilitate the singleton
         * design pattern the class follows.
         */
        Keyboard();

        /**
         * @brief Destroy the Keyboard object
         */
        ~Keyboard();

    public:
        /**
         * @brief Get the singleton instance of the Keyboard class.
         *
         * This function provides access to the singleton instance of the
         * Keyboard class. If this instance does not exist, it will be created.
         *
         * @return Pointer to the singleton instance of the Keyboard class.
         */
        static Keyboard* getInstance();

        /**
         * @brief Registers a keyboard action.
         *
         * This function registers an action related to keyboard input, e.g.
         * pressing or releasing a specific key.
         *
         * @param key The keycode representing the key which fired the event.
         * @param action The action that triggered the event.
         */
        static void registerAction(int key, int action);

        /**
         * @brief Checks if a key is currently being pressed down.
         *
         * @param key The keycode representing the key to check.
         * @return True if the key is being held down, false otherwise.
         */
        static bool isKeyDown(int key);

        /**
         * @brief Checks if a key has been pressed.
         *
         * @param key The keycode representing the key to check.
         * @return True if the key has been pressed, false otherwise.
         */
        static bool isKeyPressed(int key);
};
}  // namespace Spectre

#endif  // KEYBOARD_H