#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED

#include <SFML/Graphics.hpp>

class Plane { // Plane sprite
public:
    Plane();
    void update(sf::RenderWindow& window, float deltaTime);
    void increaseVel(float velRange);
    void resetGame();

    static sf::Sprite sprite;

private:
    sf::Texture texture;

    static sf::Vector2f initialVel; // Initial velocity
    static sf::Vector2f velocity; // Initial velocity
    static sf::Vector2f maxVel;
    static float velDif;

    static float spawnTimer;
    static float spawnInterval;

    void movement(float deltaTime);

    void randomProp();

};

#endif // PLANE_H_INCLUDED
