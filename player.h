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

private:
    sf::Texture texture;
    sf::Texture deathTexture;
    sf::Texture hitPlayer;

    sf::Sprite sprite;
    sf::Sprite deathSprite;

    static float speed; // Static means the value is shared for all instances of that class
    static float gravity;
    static float terminalVel;
    static float maxRotation;
    static float playerTimer;
    static bool collided;
    static bool hitSoundPlayed;
    static bool gameOverPlayed;
    static float deathScreenTime;

    static sf::Vector2f velocity;

    void handleInput(float deltaTime, int gameState);
    void applyGravity(float deltaTime);
    void menuFloating(float deltaTime);
    void deathCheck(int& gameState, int screenHeight, Sounds& sound);
    void collision(int& gameState, Building& building, Plane& plane, Helicopter& helicopter, sf::RenderWindow& window);
    void hitSequence(float deltaTime, sf::RenderWindow& window, Sounds& sound);
};

#endif // PLAYER_H
