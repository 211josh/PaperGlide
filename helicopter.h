#ifndef HELICOPTER_H_INCLUDED
#define HELICOPTER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>



class Helicopter { // Helicopter sprite
public:
    Helicopter();
    void update(sf::RenderWindow& window, float deltaTime);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    static sf::Vector2f velocity;

    static float spawnTimer;
    static float spawnInterval;
    static float heliTimer;
    static float initialyPos;

    void movement(float deltaTime);
    void randomProp();

};

#endif // HELICOPTER_H_INCLUDED
