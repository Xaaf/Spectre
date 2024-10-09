#include "Spectre/Input/Keyboard.h"
#include <algorithm>

using namespace Spectre;

Keyboard* Keyboard::instance = nullptr;

bool keys[SP_KEY_LAST];
std::vector<int> pressed_keys;

Keyboard::Keyboard() = default;
Keyboard::~Keyboard() = default;

Keyboard* Keyboard::getInstance() {
    if (instance == nullptr) {
        instance = new Keyboard();
    }

    return instance;
}

void Keyboard::registerAction(int key, int action) {
    LOG_TRACE("Registering input for key '" << key << "' with action '"
                                            << action << "'");

    keys[key] = action != SP_RELEASE;

    auto it = std::find(pressed_keys.begin(), pressed_keys.end(), key);
    if (action == SP_RELEASE && it != pressed_keys.end()) {
        pressed_keys.erase(it);
    }
}

bool Keyboard::isKeyDown(int key) { return keys[key]; }

bool Keyboard::isKeyPressed(int key) {
    if (!keys[key]) return false;

    auto it = std::find(pressed_keys.begin(), pressed_keys.end(), key);
    if (it != pressed_keys.end()) {
        return false;
    }

    pressed_keys.push_back(key);
    return true;
}