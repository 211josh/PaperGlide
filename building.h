#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

#include "background.h"


class Building { // Building sprite
public: // Can be accessed outside the class
    Building();
    void update(sf::RenderWindow& window, float deltaTime); // void = no return value
    void increaseVel(float velRange);
    void resetGame();
    sf::Vector2f getPos(); // function returns a sf::Vector2f (2 float vector)
    sf::FloatRect getHitbox();

private: // Can only be accessed by code inside the class
    sf::Texture texture;
    sf::Sprite sprite;

    static sf::Vector2f initialVel;
    static sf::Vector2f velocity;
    static sf::Vector2f maxVel;
    static float velDif;

    static float spawnTimer;
    static float spawnInterval;

    void movement(float deltaTime);
    void randomProp();
};

#endif // BUILDING_H_INCLUDED
