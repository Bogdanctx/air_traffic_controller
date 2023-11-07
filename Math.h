//
// Created by Bogdan on 11/6/2023.
//

#ifndef AIR_TRAFFIC_CONTROLLER_MATH_H
#define AIR_TRAFFIC_CONTROLLER_MATH_H

#include <SFML/System/Vector2.hpp>
#include <cmath>

class Math {
public:
    Math();

    constexpr static const double PI  = 3.14159265;

    static sf::Vector2f GetPositionToDirection(double speed, double direction);
    static double ConvertDegreesToRadians(double degrees);
};

#endif //AIR_TRAFFIC_CONTROLLER_MATH_H
