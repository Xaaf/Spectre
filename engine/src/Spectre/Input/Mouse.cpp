#include "Spectre/Input/Mouse.h"
#include <algorithm>

using namespace Spectre;

Mouse* Mouse::instance = nullptr;

bool buttons[SP_MOUSE_BUTTON_LAST];
std::vector<int> pressed_buttons;

double mouseX, mouseY;

Mouse::Mouse() = default;
Mouse::~Mouse() = default;

Mouse* Mouse::getInstance() {
    if (instance == nullptr) {
        instance = new Mouse();
    }

    return instance;
}

void Mouse::registerAction(int button, int action) {
    LOG_TRACE("Regsitering input for button '" << button << "' with action '"
                                               << action << "'");
    buttons[button] = action != SP_RELEASE;

    auto it = std::find(pressed_buttons.begin(), pressed_buttons.end(), button);
    if (action == SP_RELEASE && it != pressed_buttons.end()) {
        pressed_buttons.erase(it);
    }
}

void Mouse::registerMove(double newX, double newY) {
    LOG_TRACE("Registering input for mouse movement, with " << newX << ", "
                                                            << newY);
    mouseX = newX;
    mouseY = newY;
}

bool Mouse::isButtonDown(int button) { return buttons[button]; }

bool Mouse::isButtonPressed(int button) {
    if (!buttons[button]) return false;

    auto it = std::find(pressed_buttons.begin(), pressed_buttons.end(), button);
    if (it != pressed_buttons.end()) {
        return false;
    }

    pressed_buttons.push_back(button);
    return true;
}

glm::vec2 Mouse::getMousePosition() { return glm::vec2(0, 0); }