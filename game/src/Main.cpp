#include "Game/GameLogic.h"

Game::GameLogic game = Game::GameLogic();
int main(int argc, char* argv[]) {
    std::string renderer = "OpenGL";
    LOG_INFO("Game", "Launching with renderer: " << renderer);

    game.setup(renderer);

    return 0;
}