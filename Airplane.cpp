//
// Created by Bogdan on 11/5/2023.
//

#include "Airplane.h"

Airplane::Airplane() {
    sf::Vector2f randomPosition(rand()%800, rand()%800);

    mCallsignValue = "WZZ123";
    mAltitudeValue = 36000;

    InitializeText(randomPosition);
}

Airplane::Airplane(Resources *pResources): Airplane() {
    sf::Font *font = pResources->GetFont("MerriweatherSans-Regular");
    mCallsign.setFont(*font);
    mAltitude.setFont(*font);
}

Airplane::~Airplane() = default;

void Airplane::Update() {

}

void Airplane::Render(sf::RenderTarget *pWindow) {
    pWindow->draw(mAirplane);
    pWindow->draw(mCallsign);

    pWindow->draw(mAltitude);
    pWindow->draw(mNewAltitude);

}

void Airplane::InitializeText(sf::Vector2f position) {
    mAirplane.setSize(sf::Vector2f (10,10));
    mAirplane.setFillColor(sf::Color::White);
    mAirplane.setPosition(position);

    mCallsign.setPosition(position.x, position.y-15);
    mCallsign.setString(mCallsignValue);
    mCallsign.setCharacterSize(10);

    std::string displayAltitude = std::to_string(mAltitudeValue/10000) + std::to_string(mAltitudeValue%10000/100);
    mAltitude.setString(displayAltitude);
    mAltitude.setPosition(callsignBounds.left + mCallsign.getLocalBounds().width, position.y-15);
    mAltitude.setCharacterSize(10);
}