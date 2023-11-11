//
// Created by Bogdan on 11/5/2023.
//

#include "Game.h"

Game::Game() = default;

void Game::Run() {

    while(mWindow.isOpen()) {
        HandleEvents();
        Update();
        Render();
    }


}

void Game::Initialize() {
    mWindow.setFramerateLimit(60);
    mWindow.create(sf::VideoMode(800, 800),
                  "Air Traffic Controller",
                  sf::Style::Close | sf::Style::Titlebar);

    if(mResources.LoadFonts()) { // has error
        mWindow.close();
    }
    Airplane airplane = Airplane(&mResources);
    mAirplanes.push_back(airplane);
    airplane = Airplane(&mResources);
    mAirplanes.push_back(airplane);
}

void Game::Update() {
    sf::Vector2i cursorPosition = sf::Mouse::getPosition(mWindow);
    for(auto &it: mAirplanes) {
        it.Update(sf::Vector2f(cursorPosition.x, cursorPosition.y));
    }
}

void Game::Render() {
    mWindow.clear();

    // Draw things
    for(auto &it: mAirplanes) {
        it.Render(&mWindow);
    }

    mWindow.display();

}

void Game::HandleEvents() {
    sf::Vector2i cursorPosition = sf::Mouse::getPosition(mWindow);
    while(mWindow.pollEvent(mGameEvent)) {
        switch (mGameEvent.type) {
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::MouseButtonPressed:
                if(mGameEvent.mouseButton.button == sf::Mouse::Left) {
                    for(auto &it: mAirplanes) {
                        it.HandleEvent(&mGameEvent);
                    }
                }
                break;
            case sf::Event::KeyPressed:

                break;

            default:
                break;
        }
    }
}