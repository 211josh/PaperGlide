#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "background.h"

sf::Vector2f sunInitialPos{1500,50};
sf::Vector2f sunSunsetInitialPos{1800,450};

sf::Vector2f Background::initialVel{-187.0f,0.0f};

sf::Vector2f Background::velocity = Background::initialVel;
sf::Vector2f Background::sunVelocity{-50.0f,0.0f}; // 20 is good
// sun velocity doesn't change

sf::Vector2f Background::maxVel{-800.0,0.0f};

bool Background::isDay = 1;
int Background::Style;


float Background::velDif = (velocity.x - maxVel.x);

Background::Background(){

    Background::Style = 0; // Which background is being used. Will be stored in a file

    // Normal theme
    if(!bgSkyTexture.loadFromFile("sprites/backgroundSky.png")){
        std::cout << "Could not load Background Sky texture";
        }
    if(!bgBuildingsTexture.loadFromFile("sprites/backgroundBuildings.png")){
        std::cout << "Could not load Background Buildings texture";
        }
    if(!sunTexture.loadFromFile("sprites/Sun.png")){
        std::cout <<"Could not load Sun texture";
    }
    if(!moonTexture.loadFromFile("sprites/Moon.png")){
        std::cout <<"Could not load Moon texture";
    }

    // Sunset theme
    if(!bgSkySunsetTexture.loadFromFile("sprites/bgSkySunset.png")){
        std::cout << "Could not load Background Sky Sunset texture";
        }
    if(!bgBuildingsSunsetTexture.loadFromFile("sprites/bgBuildingsSunset.png")){
        std::cout << "Could not load Background Buildings Sunset texture";
        }

    backgroundSky.setPosition(sf::Vector2f(0,0));
    backgroundBuildings.setPosition(sf::Vector2f(0,0));

    if(Style == 0){
        themeNormal();
        }
    if(Style == 1){
        themeSunset();
        }
    dayCycle();
}

void Background::update(sf::RenderWindow& window, float deltaTime){
    movement(deltaTime);
    resetPos();
    window.draw(backgroundSky);
    window.draw(Sun);
    window.draw(backgroundBuildings);
}

void Background::movement(float deltaTime){
    backgroundSky.move(velocity*deltaTime);
    backgroundBuildings.move(velocity*deltaTime);
    Sun.move(sunVelocity*deltaTime);
}

void Background::resetPos(){ // First screen size of background texture is identical to last. Reset pos for infinite scroll illusion
    sf::Vector2f position = backgroundSky.getPosition();
    if(position.x <= -5120){ // Beginning of last frame x value
        backgroundSky.setPosition(sf::Vector2f{0.0f,0.0f});
        backgroundBuildings.setPosition(sf::Vector2f{0.0f,0.0f});
    }

    sf::Vector2f sunPos = Sun.getPosition();
        if(sunPos.x <= -80){
            isDay = !isDay;
            dayCycle();
    }
}

void Background::increaseVel(float velRange){ // Increase velocity
    velocity.x -= velDif/velRange;
    }

void Background::resetGame(){ // Function if die and retry
    velocity = initialVel;
    resetPos();
    isDay = 1;
    dayCycle();
    }

void Background::dayCycle(){
    if(Style == 0){ // Normal theme
        Sun.setPosition(sunInitialPos);
        if(isDay == 1){
            Sun.setTexture(sunTexture);
            Sun.setColor(sf::Color({255,255,160,255}));
            backgroundSky.setColor(sf::Color({255,255,255,255}));
        } else{
            Sun.setTexture(moonTexture);
            Sun.setColor(sf::Color({255,255,255,255}));
            backgroundSky.setColor(sf::Color({40,40,40,255}));
            }
        }
    if(Style == 1){
        Sun.setPosition(sunSunsetInitialPos);
        }
    }

void Background::themeNormal(){
    std::cout << "NORMAL" << std::endl;
    Style = 0;
    isDay = 1;
    backgroundSky.setTexture(bgSkyTexture);
    backgroundBuildings.setTexture(bgBuildingsTexture);
    backgroundBuildings.setColor(sf::Color({255,255,255,100}));

    Sun.setTexture(sunTexture);
    Sun.setPosition(sunInitialPos);
    Sun.setColor(sf::Color({255,255,160,255}));
    Sun.setScale({6,6});

    sf::Vector2f origin = Sun.getOrigin(); // sets origin of sun to right side to ensure sun is off screen
    Sun.setOrigin({sunTexture.getSize().x,origin.y});
    }


void Background::themeSunset(){
    std::cout << "SUNSET" << std::endl;
    Style = 1;
    backgroundSky.setTexture(bgSkySunsetTexture);
    backgroundBuildings.setTexture(bgBuildingsSunsetTexture);
    backgroundBuildings.setColor(sf::Color({255,255,255,255}));
    backgroundSky.setColor(sf::Color({255,255,255,255}));

    Sun.setTexture(sunTexture);
    Sun.setPosition(sunSunsetInitialPos);
    Sun.setColor(sf::Color({255,0,255,255}));
    Sun.setScale({12,12});

    sf::Vector2f origin = Sun.getOrigin();
    Sun.setOrigin({sunTexture.getSize().x,origin.y});
    }
