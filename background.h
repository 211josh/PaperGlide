#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

class Background{
public:
    Background();
    void update(sf::RenderWindow& window, float deltaTime);
    void increaseVel(float velRange);
    void resetGame();

    void themeNormal();
    void themeMedival();
    void themeSunset();
    void themeSpace();
    void themeApoc();

    static int Style;

    static bool isDay;
    void dayCycle(); // public as retrying resets to day
private:

    void shineFollow();

    sf::Texture bgSkyTexture;
    sf::Texture bgSkySunsetTexture;
    sf::Texture bgSkySpaceTexture;
    sf::Texture bgSkyApocTexture;

    sf::Texture sunShineTexture;

    sf::Texture sunTexture;
    sf::Texture moonTexture;
    sf::Texture sunSpaceTexture;
    sf::Texture sunApocTexture;

    sf::Texture bgBuildingsTexture;
    sf::Texture bgBuildingsSpaceTexture;
    sf::Texture bgBuildingsSunsetTexture;

    sf::Sprite backgroundSky;
    sf::Sprite Sun;
    sf::Sprite sunShine;
    sf::Sprite backgroundBuildings;

//    static sf::Vector2f sunInitialPos;
//    static sf::Vector2f sunSunsetInitialPos;

    static sf::Vector2f initialVel;
    static sf::Vector2f velocity;
    static sf::Vector2f sunVelocity;
    static sf::Vector2f maxVel;

    static float velDif;

    void movement(float deltaTime);
    void resetPos();
};

#endif // BACKGROUND_H_INCLUDED
