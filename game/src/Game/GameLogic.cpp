#include "Game/GameLogic.h"
#include "Spectre/Input/Keyboard.h"

using namespace Game;

void GameLogic::setup(const std::string& renderer) {
    engine = Spectre::Engine::getInstance();
    engine->initialise("Heroes of Colossus", renderer);

    run();
}

void GameLogic::run() {
    while(engine->isRunning()) {
        engine->step();

        if (Spectre::Keyboard::isKeyDown(SP_KEY_ESCAPE)) {
            engine->stop();
        }
    }
}