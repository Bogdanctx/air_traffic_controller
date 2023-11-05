//
// Created by Bogdan on 11/5/2023.
//

#ifndef AIR_TRAFFIC_CONTROLLER_AIRPLANE_H
#define AIR_TRAFFIC_CONTROLLER_AIRPLANE_H

#include <SFML/Graphics.hpp>
#include "Resources.h"

class Airplane {
public:
    Airplane();
    Airplane(Resources *pResources);
    ~Airplane();

    void Update();
    void Render(sf::RenderTarget *window);
private:
    sf::RectangleShape mAirplane;

    sf::Text mCallsign;
    std::string mCallsignValue;

    sf::Text mCurrentAltitude, mNewAltitude;
    int mCurrentAltitudeValue, mNewAltitudeValue;


    sf::Text mSpeed, mNewSpeed;
    int mSpeedValue, mNewSpeedValue;

    sf::Text mHeading, mNewHeading;
    int mHeadingValue, mNewHeadingValue;
};


#endif //AIR_TRAFFIC_CONTROLLER_AIRPLANE_H