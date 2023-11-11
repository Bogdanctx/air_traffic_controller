//
// Created by Bogdan on 11/6/2023.
//

#include "Math.h"

Math::Math() = default;

int Math::GetDirectionToPoint(sf::Vector2f origin, sf::Vector2f point) {
    int d = degrees(atan2(origin.y-point.y, origin.x-point.x)) - 90;
    if(d<0) {
        d+=360;
    }
    return d;
}

sf::Vector2f Math::TranslatePositionToPoint(double speed, double direction) {
    sf::Vector2f p(
            sin(radians(direction)) * speed / 100,
            cos(radians(direction+180)) * speed / 100
    );
    return p;
}

double Math::degrees(double x) {
    return x*180/PI;
}

double Math::radians(double x) {
    return x * PI / 180;
}