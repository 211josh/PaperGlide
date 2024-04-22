#ifndef HELICOPTER_H_INCLUDED
#define HELICOPTER_H_INCLUDED

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

class Helicopter { // Helicopter sprite
public:
    Helicopter();
    void update(sf::RenderWindow& window, float deltaTime);
    void increaseVel(float velRange);
    void resetGame();

    void themeNormal();
    void themePixel();
    void themeSpace();

    void testMode(sf::RenderWindow& window, float deltaTime);

    sf::Sprite sprite;

private:
    sf::Texture texture;
    sf::Texture texturePixel;
    sf::Texture textureSpace;

    float spawnTimer;
    float spawnTimerMax;

    sf::Vector2f initialVel;
    sf::Vector2f velocity; // Initial velocity
    sf::Vector2f maxVel;
    float velDif;
    float heliTimer;
    float animationTimer;
    float initialyPos;

    void movement(float deltaTime);
    void randomProp();
    void animation(float deltaTime);

    sf::IntRect rectFirstSprite;

};

#endif // HELICOPTER_H_INCLUDED
