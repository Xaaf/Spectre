#ifndef MOUSE_H
#define MOUSE_H

#include <glm/vec2.hpp>
#include "InputCodes.h"
#include "sppch.h"

namespace Spectre {
class Mouse {
    private:
        static Mouse* instance;

    private:
        Mouse();
        ~Mouse();

    public:
        static Mouse* getInstance();
        static void registerAction(int button, int action);
        static void registerMove(double newX, double newY);

        static bool isButtonDown(int button);
        static bool isButtonPressed(int button);

        static glm::vec2 getMousePosition();
};
}  // namespace Spectre

#endif  // MOUSE_H