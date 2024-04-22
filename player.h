#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Collision.hpp"

#include <iostream>

#include "building.h"
#include "plane.h"
#include "helicopter.h"
#include "sounds.h"

class Player {
public:
    Player();
    void update(sf::RenderWindow& window, float deltaTime, int screenHeight, int& gameState, Building& building, Plane& plane, Helicopter& helicopter, Sounds& sound); // Update for game state
    void menuUpdate(sf::RenderWindow& window, float deltaTime); // Update for menu state
    void resetGame(int gameState);

    void testMode(sf::RenderWindow& window, float deltaTime, Helicopter& helicopter, Plane& plane, Building& building);

    void themeNormal();
    void themePixel();
    void themeOrigami();
    void themeGold();
    void themeKing();

    int Style;

    float playerTimer;

    void writeTheme(); // re-write txt file for player theme

private:
    sf::Texture playerNormal;
    sf::Texture playerPixel;
    sf::Texture playerOrigami;
    sf::Texture playerGold;
    sf::Texture playerKing;

    sf::Texture deathTexture;

    sf::Sprite sprite;
    sf::Sprite deathSprite;

    float speed; // Static means the value is shared for all instances of that class
    float gravity;
    float terminalVel;
    float maxRotation;
    bool collided;
    bool hitSoundPlayed;
    bool gameOverPlayed;
    float deathScreenTime;

    sf::Vector2f velocity;

    void handleInput(float deltaTime, int gameState);
    void applyGravity(float deltaTime);
    void menuFloating(float deltaTime);
    void deathCheck(int& gameState, int screenHeight, Sounds& sound);
    void collision(int& gameState, Building& building, Plane& plane, Helicopter& helicopter, sf::RenderWindow& window);
    void hitSequence(float deltaTime, sf::RenderWindow& window, Sounds& sound, int& gameState);

    void readTheme(); // check txt file for player theme
};

#endif // PLAYER_H
