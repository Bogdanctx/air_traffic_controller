//
// Created by Bogdan on 11/5/2023.
//

#ifndef AIR_TRAFFIC_CONTROLLER_AIRPLANE_H
#define AIR_TRAFFIC_CONTROLLER_AIRPLANE_H

#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Math.h"
#include "enums.h"

class Airplane {
public:
    Airplane();
    Airplane(Resources *pResources);
    ~Airplane();

    void Update(sf::Vector2f cursorPosition);
    void Render(sf::RenderTarget *pWindow);
    void HandleEvent(sf::Event *pEvent);

    int GetAltitude();
    sf::Vector2f GetPosition();
    void SetTCAS(const int code);
    void SetFlag(const AIRPLANE_FLAGS flag);
    void ResetFlag(const AIRPLANE_FLAGS flag);
    sf::FloatRect GetBounds();

private:
    void UpdateTextPosition(sf::Vector2f position);
    void MoveAirplane();

    void DetectNewHeading();
    void DetectNewAltitude();
    void DetectNewSpeed();
    void HandleDataChange();

    bool mAirplaneIsSelected{};

    std::vector<bool>mFlags = {false, false};

    sf::RectangleShape mAirplane;

    sf::Text mCallsign;
    std::string mCallsignValue;

    int mTCAS;

    sf::Text mAltitude, mNewAltitude;
    int mAltitudeValue, mNewAltitudeValue;

    sf::Text mSpeed, mNewSpeed;
    int mSpeedValue, mNewSpeedValue;

    sf::Text mHeading, mNewHeading;
    int mHeadingValue, mNewHeadingValue;
    sf::RectangleShape mHeadingStick;

    // Clocks below are for simulation effect
    sf::Clock moveClock; // used to move the airplane position in a given interval
    sf::Clock altitudeChangeClock; // used to change altitude in a given interval
    sf::Clock speedChangeClock; // used to change speed in a given interval
    sf::Clock headingChangeClock; // used to change heading in a given interval

    sf::Vector2f mCursorPosition;
};


#endif //AIR_TRAFFIC_CONTROLLER_AIRPLANE_H
