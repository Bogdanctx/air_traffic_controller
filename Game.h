//
// Created by Bogdan on 11/5/2023.
//

#ifndef AIR_TRAFFIC_CONTROLLER_GAME_H
#define AIR_TRAFFIC_CONTROLLER_GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Airplane.h"
#include "Resources.h"

class Game {
public:
    Game();

    void Initialize();
    void Run();

private:
    void HandleEvents();
    void Update();
    void Render();

    Airplane airplane;
    Resources resources;

    sf::RenderWindow window;

    sf::Event gameEvent{};
};


#endif //AIR_TRAFFIC_CONTROLLER_GAME_H
