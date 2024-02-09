#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <fstream>

#include "sounds.h"
#include "background.h"
#include "player.h"
#include "building.h"
#include "helicopter.h"
#include "plane.h"
#include "score.h"

void loadWindow(int screenWidth, int screenHeight, int& isFullscreen, sf::RenderWindow& window);

class Menu{
public:
    Menu(int screenWidth);
    void menuUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, Score& score, int& isFullscreen, int screenHeight);
    void tryUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, int& current_score, Score& score, int& isFullscreen, int screenHeight);
    void settingsUpdate(sf::RenderWindow& window, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, int& current_score, Score& score, int screenWidth, int& isFullscreen, int screenHeight);
    void customiseUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, Score& score, int& isFullscreen, int screenHeight);

    int menuSelect; // determines which option to select. 0 for play, 1 for settings, 2 for quit.
    int playerSelect;
    int themeSelect;
    float selectTimer; // Prevents fast menu scrolling

private:
    sf::Font font;

    // Menu text
    sf::Text titleText;
    sf::Text playText;
    sf::Text customiseText;
    sf::Text settingsText;
    sf::Text quitText;
    sf::Text versionText;
    sf::Text holdSpaceText;

    // Customisation text
    sf::Text playerText;
    sf::Text themeText;
    sf::Text unlockText;

    // Settings text
    sf::Text fullscreenText;
    sf::Text volumeText;
    sf::Text backText;

    // Retry text
    sf::Text retryText;
    sf::Text menuText;
    sf::Text quit2Text;

    static sf::Sprite upArrow;
    sf::Texture arrowTexture;

    void handleInput(sf::RenderWindow& window, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, int& current_score, Score& score, int& isFullscreen, int screenWidth, int screenHeight);
    void holdSpaceDisplay(sf::RenderWindow& window, Player& player);

};

#endif // MENU_H_INCLUDED
