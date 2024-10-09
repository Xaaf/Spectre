#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "InputCodes.h"
#include "sppch.h"

namespace Spectre {
class Keyboard {
    private:
        static Keyboard* instance;

    private:
        Keyboard();
        ~Keyboard();

    public:
        static Keyboard* getInstance();
        static void registerAction(int key, int action);

        static bool isKeyDown(int key);
        static bool isKeyPressed(int key);
};
}  // namespace Spectre

#endif  // KEYBOARD_H