//
// Created by Bogdan on 11/5/2023.
//

#include "Airplane.h"

Airplane::Airplane() = default;

Airplane::Airplane(Resources *pResources): Airplane() {
    sf::Font *font = pResources->GetFont("MerriweatherSans-Regular");
    mCallsign.setFont(*font);
    mAltitude.setFont(*font);
    mNewAltitude.setFont(*font);
    mSpeed.setFont(*font);
    mNewSpeed.setFont(*font);
    mHeading.setFont(*font);
    mNewHeading.setFont(*font);

    sf::Vector2f randomPosition(rand()%800, rand()%800);

    mCallsignValue = "ROT124";
    mAltitudeValue = 300;
    mNewAltitudeValue = 300;
    mSpeedValue = 310;
    mNewSpeedValue = 215;
    mAirplaneIsSelected = false;
    mHeadingValue = mNewHeadingValue = Math::GetDirectionToPoint(randomPosition, sf::Vector2f(400, 400));

    sf::FloatRect mAirplaneBounds = mAirplane.getGlobalBounds();
    mAirplane.setSize(sf::Vector2f(10, 10));
    mAirplane.setOrigin(
            sf::Vector2f(mAirplaneBounds.left + 5, mAirplaneBounds.top + 5)
            );
    mAirplane.setPosition(randomPosition);


    mCallsign.setString(mCallsignValue);
    mCallsign.setCharacterSize(10);

    std::string currentAltitude = std::to_string(mAltitudeValue);
    mAltitude.setString(currentAltitude);
    mAltitude.setCharacterSize(10);

    mNewAltitude.setString(currentAltitude);
    mNewAltitude.setCharacterSize(10);

    mSpeed.setString(std::to_string(mSpeedValue));
    mSpeed.setCharacterSize(10);

    mNewSpeed.setString(std::to_string(mNewSpeedValue));
    mNewSpeed.setCharacterSize(10);

    mHeading.setCharacterSize(10);
    mHeading.setString(std::to_string(mHeadingValue));
    mNewHeading = mHeading;
    mNewHeading.setFillColor(sf::Color::Cyan);

    mHeadingStick.setFillColor(sf::Color::Cyan);
    mHeadingStick.setPosition(randomPosition.x+5, randomPosition.y+5);
    mHeadingStick.setSize(sf::Vector2f(26, 1.2));
    mHeadingStick.setRotation(mHeadingValue);

    UpdateTextPosition(randomPosition);
}

Airplane::~Airplane() = default;

void Airplane::Update(sf::Vector2f cursorPosition) {
    mCursorPosition = cursorPosition;

    if(mFlags[AIRPLANE_FLAGS::SAFE_COLLISION_DISTANCE] == true && mFlags[AIRPLANE_FLAGS::DANGER_COLLISION_DISTANCE] == false) {
        mAirplane.setFillColor(sf::Color(181, 101, 25));
    }
    else if(mFlags[AIRPLANE_FLAGS::DANGER_COLLISION_DISTANCE]) {
        mAirplane.setFillColor(sf::Color::Red);
    }
    else {
        mAirplane.setFillColor(sf::Color::White);
    }

    MoveAirplane();
    UpdateTextPosition(mAirplane.getPosition());
    HandleDataChange();
}

void Airplane::SetFlag(const AIRPLANE_FLAGS flag) {
    mFlags[flag] = true;
}
void Airplane::ResetFlag(const AIRPLANE_FLAGS flag) {
    mFlags[flag] = false;
}

sf::FloatRect Airplane::GetBounds() {
    return mAirplane.getGlobalBounds();
}

void Airplane::MoveAirplane() {
    if (moveClock.getElapsedTime().asMilliseconds() >= 700) {
        mAirplane.move(Math::TranslatePositionToPoint(mSpeedValue, mHeadingValue));

        mHeading.setString(std::to_string(mHeadingValue));
        mHeadingStick.setRotation(mHeadingValue-90);

        moveClock.restart();
    }
}

void Airplane::Render(sf::RenderTarget *pWindow) {
    pWindow->draw(mAirplane);
    pWindow->draw(mCallsign);

    if(mAirplaneIsSelected) {
        pWindow->draw(mHeading);
        pWindow->draw(mNewHeading);
        pWindow->draw(mHeadingStick);

        pWindow->draw(mAltitude);
        pWindow->draw(mNewAltitude);

        pWindow->draw(mSpeed);
        pWindow->draw(mNewSpeed);
    }

}

int Airplane::GetAltitude() {
    return mAltitudeValue;
}

void Airplane::SetTCAS(const int code) {
    mTCAS = code;

    switch(code) {
        case 1: // moderatly close
            break;
        case 2:
            mAirplane.setFillColor(sf::Color::Red);
            break;
        default:
            break;
    }
}

void Airplane::DetectNewHeading() {
    mNewHeadingValue = Math::GetDirectionToPoint(mAirplane.getPosition(), mCursorPosition);
    mNewHeading.setString(std::to_string(mNewHeadingValue));
    mHeadingStick.setRotation(mNewHeadingValue - 90);
}

void Airplane::DetectNewAltitude() {
    if(altitudeChangeClock.getElapsedTime().asMilliseconds() >= 150) {
        bool isUpArrowPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        bool isDownArrowPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

        if(isUpArrowPressed) {
            mNewAltitudeValue ++;
        }
        else if(isDownArrowPressed) {
            mNewAltitudeValue --;
        }

        std::string newAltitude = std::to_string(mNewAltitudeValue);
        if(mNewAltitudeValue < 100) {
            newAltitude = "0" + mNewAltitudeValue;
        }
        mNewAltitude.setString(newAltitude);

        altitudeChangeClock.restart();
    }
}

void Airplane::DetectNewSpeed() {
    if(speedChangeClock.getElapsedTime().asMilliseconds() >= 150) {
        bool isUpArrowPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        bool isDownArrowPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

        if(isUpArrowPressed) {
            mNewSpeedValue ++;
        }
        else if(isDownArrowPressed) {
            mNewSpeedValue --;
        }
        mNewSpeed.setString(std::to_string(mNewSpeedValue));
        speedChangeClock.restart();
    }
}

void Airplane::HandleEvent(sf::Event *pEvent) {
    switch (pEvent->type) {
        case sf::Event::MouseButtonPressed:
            if (pEvent->mouseButton.button == sf::Mouse::Left) {
                sf::FloatRect airplaneBounds = mAirplane.getGlobalBounds();
                if(airplaneBounds.contains(sf::Vector2f(mCursorPosition.x * 1.f, mCursorPosition.y * 1.f))) {
                    mAirplaneIsSelected = !mAirplaneIsSelected;
                }
                else {
                    mAirplaneIsSelected = false;
                }
                UpdateTextPosition(sf::Vector2f(airplaneBounds.left, airplaneBounds.top));
            }
            break;
        default:
            break;
    }
}

void Airplane::HandleDataChange() {

    // SPACE -> USED TO CHANGE AIRPLANE ALTITUDE
    if(mAirplaneIsSelected && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        DetectNewAltitude();
    }
    else {
        if(mAltitudeValue != mNewAltitudeValue) { // Processing a new altitude
            if(altitudeChangeClock.getElapsedTime().asMilliseconds() >= 150) {
                if(mAltitudeValue > mNewAltitudeValue) {
                    mAltitudeValue --;
                }
                else if(mAltitudeValue < mNewAltitudeValue) {
                    mAltitudeValue ++;
                }

                std::string currentAltitude = std::to_string(mAltitudeValue);
                if(mAltitudeValue < 100) {
                    currentAltitude = "0" + currentAltitude;
                }

                mAltitude.setString(currentAltitude);
                altitudeChangeClock.restart();
            }
        }
    }

    // LCTRL -> USED TO CHANGE AIRPLANE SPEED
    if(mAirplaneIsSelected && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        DetectNewSpeed();
    }
    else {
        if(mNewSpeedValue != mSpeedValue) { // Processing new speed
            if(speedChangeClock.getElapsedTime().asMilliseconds() >= 150) {
                if(mNewSpeedValue > mSpeedValue) {
                    mSpeedValue++;
                }
                else if(mNewSpeedValue < mSpeedValue) {
                    mSpeedValue--;
                }

                mSpeed.setString(std::to_string(mSpeedValue));
                speedChangeClock.restart();
            }
        }
    }

    // LSHIFT -> USED TO CHANGE AIRPLANE HEADING
    if(mAirplaneIsSelected && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        DetectNewHeading();
    }
    else {
        if(mNewHeadingValue != mHeadingValue) { // Processing new heading
            if(headingChangeClock.getElapsedTime().asMilliseconds() >= 60) {
                if(mHeadingValue < mNewHeadingValue)
                    mHeadingValue++;
                else
                    mHeadingValue--;

                if(mHeadingValue < 0)
                    mHeadingValue += 360;

                mHeadingValue %= 360;
                headingChangeClock.restart();
            }
        }
    }
}

void Airplane::UpdateTextPosition(sf::Vector2f position) {
    if(mAirplaneIsSelected) {
        mCallsign.setPosition(position.x - 20, position.y-40);
    }
    else {
        mCallsign.setPosition(position.x - 20, position.y-20);
    }

    mHeadingStick.setPosition(position.x, position.y);
    mHeading.setPosition(position.x - 20 + mCallsign.getLocalBounds().width + 5,position.y-40);
    mNewHeading.setPosition(mHeading.getPosition().x + mHeading.getLocalBounds().width + 5, position.y - 40);
    mAltitude.setPosition(position.x - 20,position.y - 30);
    mNewAltitude.setPosition(position.x - 20 + mAltitude.getLocalBounds().width + 5,position.y - 30);
    mSpeed.setPosition(position.x - 20,position.y - 20);
    mNewSpeed.setPosition(position.x - 20 + mSpeed.getLocalBounds().width + 5,position.y - 20);
}

sf::Vector2f Airplane::GetPosition() {
    return mAirplane.getPosition();
}