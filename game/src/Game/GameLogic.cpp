#include "Game/GameLogic.h"

using namespace Game;

void GameLogic::setup(const std::string& renderer) {
    engine = Spectre::Engine::getInstance();
    engine->initialise("Heroes of Colossus", renderer);

    run();
}

void GameLogic::run() {
    LOG_INFO("Game", "GameLogic::run");
    // while(engine->isRunning()) {
    //     engine->step();
    // }
}