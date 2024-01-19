#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED

#include <SFML/Graphics.hpp>

class Plane { // Plane sprite
public:
    Plane();
    void update(sf::RenderWindow& window, float deltaTime);
    void increaseVel(float velRange);

private:
    sf::Texture texture;
    sf::Sprite sprite;

    static sf::Vector2f velocity; // Initial velocity
    static sf::Vector2f maxVel;
    static float velDif;

    static float spawnTimer;
    static float spawnInterval;

    void movement(float deltaTime);

    void randomProp();
};

#endif // PLANE_H_INCLUDED
