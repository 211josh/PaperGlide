#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "sounds.h"
#include "background.h"
#include "player.h"
#include "building.h"
#include "helicopter.h"
#include "plane.h"
#include "score.h"

class Menu{
public:
    Menu();
    void menuUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, Score& score);
    void tryUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, int& current_score, Score& score);

    int menuSelect; // determines which option to select. 0 for play, 1 for settings, 2 for quit.
    float selectTimer; // Prevents fast menu scrolling

private:
    sf::Font font;

    sf::Text playText;
    sf::Text settingsText;
    sf::Text quitText;
    sf::Text versionText;
    sf::Text holdSpaceText;

    static sf::Sprite upArrow;
    sf::Texture arrowTexture;

    void handleInput(sf::RenderWindow& window, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, int& current_score, Score& score);
    void holdSpaceDisplay(sf::RenderWindow& window, Player& player);
};

#endif // MENU_H_INCLUDED
