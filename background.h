#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

class Background{
public:
    Background();
    void update(sf::RenderWindow& window, float deltaTime);
    void increaseVel(float velRange);
    void resetGame();

    static int Style;

    static bool isDay;
    void dayCycle(); // public as retrying resets to day
private:
    sf::Texture bgSkyTexture;
    sf::Texture bgSkySunsetTexture;

    sf::Texture sunTexture;
    sf::Texture moonTexture;

    sf::Texture bgBuildingsTexture;
    sf::Texture bgBuildingsSunsetTexture;

    sf::Sprite backgroundSky;
    sf::Sprite Sun;
    sf::Sprite backgroundBuildings;

    static sf::Vector2f sunInitialPos;
    static sf::Vector2f sunSunsetInitialPos;

    static sf::Vector2f initialVel;
    static sf::Vector2f velocity;
    static sf::Vector2f sunVelocity;
    static sf::Vector2f maxVel;

    static float velDif;

    void movement(float deltaTime);
    void resetPos();
};

#endif // BACKGROUND_H_INCLUDED
