//
// Created by Bogdan on 11/6/2023.
//

#include "Math.h"

Math::Math() = default;

sf::Vector2f Math::GetPositionToDirection(double speed, double direction) {
    double degreesInRadians = ConvertDegreesToRadians(direction);

    sf::Vector2f position(
            speed * cos(degreesInRadians),
            speed * sin(degreesInRadians)
            );
    return position;
}

double Math::ConvertDegreesToRadians(double degrees) {
    return degrees * PI / 180;
}