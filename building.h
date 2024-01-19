#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

#include "background.h" // Needed for add score function


class Building { // Building sprite
public:
    Building();
    void update(sf::RenderWindow& window, float deltaTime);
    void increaseVel(float velRange);

private:
    sf::Texture texture;
    sf::Sprite sprite;

    static sf::Vector2f velocity;
    static sf::Vector2f maxVel;
    static float velDif;

    static float spawnTimer;
    static float spawnInterval;

    void movement(float deltaTime);
    void randomProp();
};

#endif // BUILDING_H_INCLUDED
