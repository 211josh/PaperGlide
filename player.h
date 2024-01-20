#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
public:
    Player();
    void update(sf::RenderWindow& window, float deltaTime, int& gameState, int screenHeight); // Update for game state
    void menuUpdate(sf::RenderWindow& window, float deltaTime); // Update for menu state
    void resetGame(int gameState);

private:
    sf::Texture texture;
    sf::Sprite sprite;

    static float speed; // Static means the value is shared for all instances of that class
    static float gravity;
    static float terminalVel;
    static float maxRotation;
    static float playerTimer;

    static sf::Vector2f velocity;

    void handleInput(float deltaTime);
    void applyGravity(float deltaTime);
    void menuFloating(float deltaTime);
    void deathCheck(int& gameState, int screenHeight);
};

#endif // PLAYER_H
