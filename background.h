#include "obstacle.h"

#include <SFML/Graphics.hpp>

#ifndef BACKGROUND_H
#define BACKGROUND_H

class Background : public Obstacle {
public:
    Background(Data& data);
    void update(sf::RenderWindow& window, Data& data);
    void setTheme(Data& data) override;
    void respawn(Data& data); // overload of obstacle respawn

private:
    void loadTextures();
    bool isDay;

    void dayNight(Data& data);

    bool daynightComplete;
    float daynightTimer;
    float daynightInterval;

    sf::Vector2f sunInitialPos;

    sf::Sprite sky;
    sf::Sprite buildings;
    sf::Sprite sun;
    sf::Sprite sunShine;

    sf::Texture skyNormal;
    sf::Texture skyPixel;
    sf::Texture skySunset;
    sf::Texture skyApoc;
    sf::Texture skySpace;

    sf::Texture buildingsNormal;
    sf::Texture buildingsPixel;
    sf::Texture buildingsSunset;
    sf::Texture buildingsApoc;
    sf::Texture buildingsSpace;

    sf::Texture sunNormal;
    sf::Texture moonNormal;

    sf::Texture sunPixel;
    sf::Texture moonPixel;

    sf::Texture sunApoc;

    sf::Texture sunSpace;

    sf::Texture tsunShine;
};

#endif
