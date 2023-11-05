//
// Created by Bogdan on 11/5/2023.
//

#include "Airplane.h"

Airplane::Airplane() {
    sf::Vector2f randomPosition(rand()%800, rand()%800);

    mAirplane.setSize(sf::Vector2f (10,10));
    mAirplane.setFillColor(sf::Color::White);
    mAirplane.setPosition(randomPosition);

    mCallsignValue = "WZZ123";
    mCallsign.setPosition(randomPosition.x, randomPosition.y-30);
    mCallsign.setString(mCallsignValue);
    mCallsign.setCharacterSize(10);

    mCurrentAltitudeValue = 5700;
    mCurrentAltitude.setString(std::to_string(mCurrentAltitudeValue));
    mCurrentAltitude.setPosition(randomPosition.x, randomPosition.y-20);
    mCurrentAltitude.setCharacterSize(10);
    mNewAltitude = mCurrentAltitude;
};

Airplane::Airplane(Resources *pResources): Airplane() {
    sf::Font *font = pResources->GetFont("MerriweatherSans-Regular");
    mCallsign.setFont(*font);
    mCurrentAltitude.setFont(*font);
}

Airplane::~Airplane() = default;

void Airplane::Update() {

}

void Airplane::Render(sf::RenderTarget *pWindow) {
    pWindow->draw(mAirplane);
    pWindow->draw(mCallsign);
    pWindow->draw(mCurrentAltitude);
    pWindow->draw(mNewAltitude);
}