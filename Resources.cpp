//
// Created by Bogdan on 11/5/2023.
//

#include "Resources.h"

Resources::Resources() {
    mListOfFonts = {
            "MerriweatherSans-Regular"
    };

}

Resources::~Resources() = default;

bool Resources::LoadFonts() {
    const std::string pathToFont = "../resources/fonts/";

    for(const std::string& fontName: mListOfFonts) {
        if(!mFonts[fontName].loadFromFile(pathToFont+fontName+".ttf")) {
            std::cout<<fontName<<" could not be loaded.\n";
            return true;
        }
    }

    return false;
}

sf::Font* Resources::GetFont(const std::string& fontName) {
    return &mFonts[fontName];
}