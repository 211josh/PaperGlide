#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED

#include <SFML/Graphics.hpp>

class Plane { // Plane sprite
public:
    Plane();
    void update(sf::RenderWindow& window, float deltaTime);
    void increaseVel(float velRange);
    void resetGame();

    // Themes
    void themeNormal();
    void themePixel();
    void themeSpace();

    void testMode(sf::RenderWindow& window, float deltaTime);

    sf::Sprite sprite;

private:
    sf::Texture texture;
    sf::Texture texturePixel;
    sf::Texture textureSpace;
    sf::IntRect rectFirstSprite;

    float spawnTimer;
    float spawnTimerMax;
    float animationTimer;

    sf::Vector2f initialVel; // Initial velocity
    sf::Vector2f velocity; // Initial velocity
    sf::Vector2f maxVel;
    float velDif;

    void movement(float deltaTime);

    void randomProp();

    void animation(float deltaTime);


};

#endif // PLANE_H_INCLUDED
