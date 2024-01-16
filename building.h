#ifndef BUILDING_H_INCLUDED
#define BUILDING_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

#include "sounds.h"
#include "score.h"

class Building { // Building sprite
public:
    Building();
    void update(sf::RenderWindow& window, float deltaTime, Score& score, Sounds& sound);

private:
    sf::Texture texture;
    sf::Sprite sprite;

    static sf::Vector2f velocity;
    static float spawnTimer;
    static float spawnInterval;

    void movement(float deltaTime);
    void randomProp();
};

#endif // BUILDING_H_INCLUDED
