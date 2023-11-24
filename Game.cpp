//
// Created by Bogdan on 11/5/2023.
//

#include "Game.h"

Game::Game() = default;

void Game::Run() {
    mWindow.setFramerateLimit(60);
    mWindow.create(sf::VideoMode(1920, 1080),
                   "Air Traffic Controller");

    if(mResources.LoadFonts()) { // has error
        mWindow.close();
    }
    Airplane airplane = Airplane(&mResources);
    mAirplanes.push_back(airplane);
    airplane = Airplane(&mResources);
    mAirplanes.push_back(airplane);

    while(mWindow.isOpen()) {
        HandleEvents();
        Update();
        Render();
    }

}

void Game::Update() {
    sf::Vector2i cursorPosition = sf::Mouse::getPosition(mWindow);

    for(auto &it: mAirplanes) {
        it.Update(sf::Vector2f(cursorPosition.x, cursorPosition.y));
    }

    DetectCollisions();
}

void Game::Render() {
    mWindow.clear();

    // Draw things
    for(auto &it: mAirplanes) {
        it.Render(&mWindow);
    }

    mWindow.display();

}

void Game::DetectCollisions() {
    sf::Vector2i cursorPosition = sf::Mouse::getPosition(mWindow);
    for(auto airplaneA=mAirplanes.begin(); airplaneA != mAirplanes.end(); airplaneA++) {
        airplaneA->Update(sf::Vector2f(cursorPosition.x, cursorPosition.y));
        for(auto airplaneB = mAirplanes.begin(); airplaneB != mAirplanes.end(); airplaneB++) {
            if(airplaneA != airplaneB) {
                int altDiff = abs(airplaneA->GetAltitude() - airplaneB->GetAltitude());
                double distance = Math::GetDistance(airplaneA->GetPosition(), airplaneB->GetPosition());

                if(altDiff <= 10) {
                    if(airplaneA->GetBounds().intersects(airplaneB->GetBounds())) { // de facut cu .intersects
                        mAirplanes.erase(airplaneA);
                        mAirplanes.erase(airplaneB);

                        return;
                    }
                    else if(distance <= 50) {
                        airplaneA->SetFlag(AIRPLANE_FLAGS::DANGER_COLLISION_DISTANCE);
                        airplaneB->SetFlag(AIRPLANE_FLAGS::DANGER_COLLISION_DISTANCE);
                    }
                    else if(distance <= 80) {
                        airplaneA->SetFlag(AIRPLANE_FLAGS::SAFE_COLLISION_DISTANCE);
                        airplaneB->SetFlag(AIRPLANE_FLAGS::SAFE_COLLISION_DISTANCE);
                    }
                }

                if(altDiff <= 10 && distance > 80 || altDiff > 10) {
                    airplaneA->ResetFlag(AIRPLANE_FLAGS::DANGER_COLLISION_DISTANCE);
                    airplaneB->ResetFlag(AIRPLANE_FLAGS::DANGER_COLLISION_DISTANCE);
                    airplaneA->ResetFlag(AIRPLANE_FLAGS::SAFE_COLLISION_DISTANCE);
                    airplaneB->ResetFlag(AIRPLANE_FLAGS::SAFE_COLLISION_DISTANCE);
                }
            }
        }
    }

}

void Game::HandleEvents() {
    //sf::Vector2i cursorPosition = sf::Mouse::getPosition(mWindow);

    while(mWindow.pollEvent(mGameEvent)) {
        switch (mGameEvent.type) {
            case sf::Event::Closed:
            {
                mWindow.close();
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if(mGameEvent.mouseButton.button == sf::Mouse::Left) {
                    for(auto &it: mAirplanes) {
                        it.HandleEvent(&mGameEvent);
                    }
                }
                break;
            }
            case sf::Event::Resized:
            {
                sf::FloatRect visibleArea(0, 0, mGameEvent.size.width, mGameEvent.size.height);
                mWindow.setView(sf::View(visibleArea));

                break;
            }
            default:
                break;
        }
    }
}