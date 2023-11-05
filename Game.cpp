//
// Created by Bogdan on 11/5/2023.
//

#include "Game.h"

Game::Game() = default;

void Game::Run() {

    while(window.isOpen()) {
        HandleEvents();
        Update();
        Render();
    }


}

void Game::Initialize() {
    window.setFramerateLimit(60);
    window.create(sf::VideoMode(800, 800),
                  "Air Traffic Controller",
                  sf::Style::Close | sf::Style::Titlebar);

    if(resources.LoadFonts()) { // has error
        window.close();
    }
    airplane = Airplane(&resources);
}

void Game::Update() {
    airplane.Update();
}

void Game::Render() {
    window.clear();

    // Draw things
    airplane.Render(&window);


    window.display();

}

void Game::HandleEvents() {
    while(window.pollEvent(gameEvent)) {
        switch (gameEvent.type) {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
        }
    }
}