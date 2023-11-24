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

    static int GetDirectionToPoint(sf::Vector2f origin, sf::Vector2f point);
    static sf::Vector2f TranslatePositionToPoint(double speed, double direction);
    static double GetDistance(sf::Vector2f a, sf::Vector2f b);

private:
    static double degrees(double x);
    static double radians(double x);

};

#endif //AIR_TRAFFIC_CONTROLLER_MATH_H
