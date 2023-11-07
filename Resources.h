//
// Created by Bogdan on 11/5/2023.
//

#ifndef AIR_TRAFFIC_CONTROLLER_RESOURCES_H
#define AIR_TRAFFIC_CONTROLLER_RESOURCES_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <iostream>

class Resources {
public:
    Resources();
    ~Resources();

    bool LoadFonts();
    sf::Font *GetFont(const std::string& fontName);

private:
    std::unordered_map<std::string, sf::Font>mFonts;
    std::vector<std::string>mListOfFonts;
};


#endif //AIR_TRAFFIC_CONTROLLER_RESOURCES_H
