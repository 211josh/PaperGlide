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
    void themeSunset();
    void themeSpace();
    void themeApoc();

    static int Style;

    static bool isDay;
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

//    static sf::Vector2f sunInitialPos;
//    static sf::Vector2f sunSunsetInitialPos;

    static sf::Vector2f initialVel;
    static sf::Vector2f velocity;
    static sf::Vector2f sunVelocity;
    static sf::Vector2f maxVel;

    static float transitionTime;
    static int transition;
    static float transitionInterval;

    static float velDif;

    void movement(float deltaTime);
    void dayNight(float deltaTime);
    void resetPos();

    void readTheme(); // Read the theme saved in txt file
};

#endif // BACKGROUND_H_INCLUDED
