#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include <fstream>
#include "utility.h"
#include "plane.h"
#include "helicopter.h"

class Background{
public:
    Background(Plane& plane, Helicopter& helicopter);
    void update(sf::RenderWindow& window, float deltaTime);
    void increaseVel(float velRange);
    void resetGame();

    void themeNormal(Plane& plane, Helicopter& helicopter);
    void themePixel(Plane& plane, Helicopter& helicopter);
    void themeSunset(Plane& plane, Helicopter& helicopter);
    void themeSpace(Plane& plane, Helicopter& helicopter);
    void themeApoc(Plane& plane, Helicopter& helicopter);

    void dayNight(float deltaTime);
    void trailerNight();

    int Style; // theme style

    bool isDay;
    void dayCycle(); // public as retrying resets to day

    void writeTheme(); // Re-write theme saved in txt file

private:

    void shineFollow();

    sf::Texture bgSkyTexture;
    sf::Texture bgSkySunsetTexture;
    sf::Texture bgSkySpaceTexture;
    sf::Texture bgSkyApocTexture;

    sf::Texture sunShineTexture;

    sf::Texture sunTexture;
    sf::Texture sunPixelTexture;
    sf::Texture moonTexture;
    sf::Texture moonPixelTexture;
    sf::Texture sunSpaceTexture;
    sf::Texture sunApocTexture;

    sf::Texture bgBuildingsTexture;
    sf::Texture bgBuildingsSpaceTexture;
    sf::Texture bgBuildingsSunsetTexture;

    sf::Sprite backgroundSky;
    sf::Sprite Sun;
    sf::Sprite sunShine;
    sf::Sprite backgroundBuildings;

    sf::Vector2f sunInitialPos;
    sf::Vector2f sunSunsetInitialPos;
    sf::Vector2f sunApocInitialPos;
    sf::Vector2f sunSpaceInitialPos;

    sf::Vector2f initialVel;
    sf::Vector2f velocity;
    sf::Vector2f sunVelocity;
    sf::Vector2f maxVel;

    float transitionTime;
    int transition;
    float transitionInterval;

    float velDif;
    float velCof; // velocity co-efficient

    void movement(float deltaTime);
    void resetPos();

    void readTheme(); // Read the theme saved in txt file
};

#endif // BACKGROUND_H_INCLUDED
