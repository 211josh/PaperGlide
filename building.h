#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

#include "background.h"
#include "score.h"

class Score;

class Building { // Building sprite
public: // Can be accessed outside the class
    Building(Background& background);
    void update(sf::RenderWindow& window, float deltaTime, Score& score); // void = no return value
    void increaseVel(float velRange);
    void resetGame(Score& score);
    sf::Vector2f getPos(); // function returns a sf::Vector2f (2 float vector)

    void themeNormal();
    void themeMedival();
    void themeSunset();
    void themeApoc();
    void themeSpace();
    void testMode(sf::RenderWindow& window, float deltaTime);

    int Style;

    sf::Sprite sprite;

private: // Can only be accessed by code inside the class
    sf::Texture textureNormal;
    sf::Texture textureSunset;
    sf::Texture textureMedival;
    sf::Texture textureApoc;
    sf::Texture textureSpace;

    sf::IntRect rectFirstSprite;

    sf::Vector2f initialVel;
    sf::Vector2f velocity;
    sf::Vector2f maxVel;
    float velDif;

    float spawnTimer;
    float spawnInterval;
    float animationTimer;

    void movement(float deltaTime);
    void randomProp(Score& score);
    void animation(float deltaTime);
};

#endif // BUILDING_H_INCLUDED
