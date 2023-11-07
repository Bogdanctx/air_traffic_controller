#include "Game.h"
#include <random>

int main() {
    srand(time(nullptr));

    Game game = Game();

    game.Initialize();
    game.Run();

    return 0;
}
