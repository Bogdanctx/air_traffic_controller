#include "Game.h"
#include <random>

int main() {
    srand(time(nullptr));

    Game game = Game();

    game.Run();

    return 0;
}
