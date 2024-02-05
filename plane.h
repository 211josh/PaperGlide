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
    static sf::IntRect rectFirstSprite;

    static float spawnTimer;
    static float spawnTimerMax;
    static float animationTimer;

    static sf::Vector2f initialVel; // Initial velocity
    static sf::Vector2f velocity; // Initial velocity
    static sf::Vector2f maxVel;
    static float velDif;

    void movement(float deltaTime);

    void randomProp();

    void animation(float deltaTime);


};

#endif // PLANE_H_INCLUDED
