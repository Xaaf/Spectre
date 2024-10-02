#ifndef GAME_H
#define GAME_H

#include "Spectre/Engine.h"

namespace Game {
class GameLogic {
    private:
        Spectre::Engine* engine;

    public:
        void setup(const std::string& renderer);
        void run();
};
}  // namespace Game

#endif  // GAME_H
