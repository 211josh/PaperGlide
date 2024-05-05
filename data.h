#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <fstream>

#include "utility.h"


struct Data {
    Data();

    float deltaTime;

    void changeFullscreen(sf::RenderWindow& window, bool x);
    void readDataTxt();
    void writeDataTxt();

    int gameState; // 0 = menu, 1 = play, 2 = customisation, 3 = settings, 4 = try again menu

    bool gameReset; // tell everything to reset (triggered when press play or retry)
    bool collided; // true if player has collided
    bool dead; // true if player has died (gone below screen)

    int screenWidth;
    int screenHeight;

    int currentScore;
    int highScore;

    bool isFullscreen;
    int volume;

    int playerTheme;
    int theme;

    int playerPixelScore;
    int playerGoldScore;
    int playerOrigamiScore;
    int playerKingScore;

    int themePixelScore;
    int themeSunsetScore;
    int themeApocScore;
    int themeSpaceScore;

    float velRange;

    std::unordered_map<int, std::pair<std::string, int>> playerThemeMap; // first value is the name, second value is the score requirement
    std::unordered_map<int, std::pair<std::string, int>> themeMap;
};

#endif
