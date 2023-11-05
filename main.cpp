#include "Game.h"

int main() {
    srand(time(0));

    Game game = Game();

    game.Initialize();
    game.Run();

    return 0;
}
