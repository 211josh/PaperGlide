#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "background.h"

float velCof; // velocity coefficient

sf::Vector2f sunInitialPos{1500,150};
sf::Vector2f sunSunsetInitialPos{1800,650};
sf::Vector2f sunSpaceInitialPos{1600,360};
sf::Vector2f sunApocInitialPos{1600,150};

sf::Vector2f Background::initialVel{-187.0f,0.0f};

sf::Vector2f Background::velocity = Background::initialVel;
sf::Vector2f Background::sunVelocity{-50.0f,0.0f}; // 50 is good
// sun velocity doesn't change

sf::Vector2f Background::maxVel{-800.0,0.0f};

bool Background::isDay = 1;
int Background::Style;


float Background::velDif = (velocity.x - maxVel.x);

Background::Background(){

    Background::Style = 3; // Which background is being used. Will be stored in a file

    // Normal theme
    //Sun & Moon
    if(!sunTexture.loadFromFile("sprites/Sun.png")){
        std::cout <<"Could not load Sun texture";
    }
    if(!sunShineTexture.loadFromFile("sprites/sunShine.png")){
        std::cout <<"Could not load Sun texture";
    }

    if(!moonTexture.loadFromFile("sprites/Moon.png")){
        std::cout <<"Could not load Moon texture";
    }

    // Background
    if(!bgSkyTexture.loadFromFile("sprites/backgroundSky.png")){
        std::cout << "Could not load Background Sky texture";
        }
    if(!bgBuildingsTexture.loadFromFile("sprites/backgroundBuildings.png")){
        std::cout << "Could not load Background Buildings texture";
        }

    // Sunset theme
    if(!bgSkySunsetTexture.loadFromFile("sprites/bgSkySunset.png")){
        std::cout << "Could not load Background Sky Sunset texture";
        }
    if(!bgBuildingsSunsetTexture.loadFromFile("sprites/bgBuildingsSunset.png")){
        std::cout << "Could not load Background Buildings Sunset texture";
        }

    // Space theme
    if(!sunSpaceTexture.loadFromFile("sprites/sunSpace.png")){
        std::cout << "Could not load Background Sun Space texture";
        }
    if(!bgSkySpaceTexture.loadFromFile("sprites/bgSkySpace.png")){
        std::cout << "Could not load Background Sky Space texture";
        }
    if(!bgBuildingsSpaceTexture.loadFromFile("sprites/bgBuildingsSpace.png")){
        std::cout << "Could not load Background Buildings Space texture";
        }

    // Apocalypse theme
    if(!sunApocTexture.loadFromFile("sprites/sunApoc.png")){
        std::cout << "Could not load Background Sun Apocalypse texture";
        }
    if(!bgSkyApocTexture.loadFromFile("sprites/bgSkyApoc.png")){
        std::cout << "Could not load Background Sky Apocalypse texture";
        }

    backgroundSky.setPosition(sf::Vector2f(0,0));
    backgroundBuildings.setPosition(sf::Vector2f(0,0));

    sunShine.setTexture(sunShineTexture);
//    sunShine.setScale({0.75,0.75});
//    sunShine.setOrigin({sunShineTexture.getSize().x/2,sunShineTexture.getSize().y/2});

    if(Style == 0){
        themeNormal();
        }
    if(Style == 2){
        themeSunset();
        }
    if(Style == 3){
        themeSpace();
    }
    if(Style == 4){
        themeApoc();
        }
    dayCycle();
}

void Background::update(sf::RenderWindow& window, float deltaTime){
    shineFollow();
    movement(deltaTime);
    resetPos();
    window.draw(backgroundSky);
    window.draw(sunShine);
    window.draw(Sun);
    window.draw(backgroundBuildings);

}

void Background::movement(float deltaTime){
    backgroundSky.move(velCof*velocity*deltaTime);
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
    if(sunPos.x <= -150 && Style == 0){ // Normal reset position
        isDay = !isDay;
        dayCycle();
        }
    if(sunPos.x <= -400 && Style == 2){ // Sunset reset position
        dayCycle();
        }
    if(sunPos.x <= -250 && Style == 3){ // Space reset position
        dayCycle();
        }
    if(sunPos.x <= -250 && Style == 4){ // Apoc reset position
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
    if(Style == 2){
        Sun.setPosition(sunSunsetInitialPos);
        }
    if(Style == 3){
        Sun.setPosition(sunSpaceInitialPos);
        }
    if(Style == 4){
        Sun.setPosition(sunApocInitialPos);
        }
    }

void Background::shineFollow(){
    sf::Vector2f sunPos = Sun.getPosition();
    sunShine.setPosition(sunPos);
    }

void Background::themeNormal(){
    velCof = 1;

    std::cout << "NORMAL" << std::endl;
    Style = 0;
    isDay = 1;
    backgroundSky.setTexture(bgSkyTexture);
    backgroundBuildings.setTexture(bgBuildingsTexture);
    backgroundBuildings.setColor(sf::Color({255,255,255,100}));

    Sun.setTexture(sunTexture);
    Sun.setPosition(sunInitialPos);
    Sun.setColor(sf::Color({255,255,160,255}));
    Sun.setScale({0.75,0.75});

    sunShine.setColor({255,255,255,200});
    sunShine.setScale({0.9,0.9});
    sunShine.setOrigin({sunShineTexture.getSize().x/2,sunShineTexture.getSize().y/2});

    sf::Vector2f origin = Sun.getOrigin(); // sets origin of sun to right side to ensure sun is off screen
    Sun.setOrigin({sunTexture.getSize().x/2,sunTexture.getSize().y/2});
    }

void Background::themeMedival(){
    velCof = 1;
    }

void Background::themeSunset(){
    velCof = 1;

    std::cout << "SUNSET" << std::endl;
    Style = 2;
    backgroundSky.setTexture(bgSkySunsetTexture);
    backgroundBuildings.setTexture(bgBuildingsSunsetTexture);
    backgroundBuildings.setColor(sf::Color({255,255,255,255}));
    backgroundSky.setColor(sf::Color({255,255,255,255}));

    Sun.setTexture(sunTexture);
    Sun.setPosition(sunSunsetInitialPos);
    Sun.setColor(sf::Color({255,0,255,255}));
    Sun.setScale({2.2,2.2});

    sunShine.setColor({0,0,0,0}); // no sun shine on sunset theme
    sunShine.setScale({0,0});

    sf::Vector2f origin = Sun.getOrigin();
    Sun.setOrigin({sunTexture.getSize().x/2,sunTexture.getSize().y/2});
    }

void Background::themeSpace(){
    velCof = 0.5;

    Style = 3;
    backgroundSky.setTexture(bgSkySpaceTexture);
    // buildings
    backgroundSky.setColor(sf::Color({255,255,255,255}));

    backgroundBuildings.setTexture(bgBuildingsSpaceTexture);
    backgroundBuildings.setColor({255,255,255,255});

  //  sunShine.setColor({135,0,0,255});
    sunShine.setColor({255,255,255,200});
    sunShine.setScale({0.1,0.1});
    sunShine.setOrigin({sunShineTexture.getSize().x/2,sunShineTexture.getSize().y/2});

    Sun.setTexture(sunSpaceTexture);
    Sun.setPosition(sunSpaceInitialPos);
    Sun.setColor(sf::Color({255,255,255,255}));
    Sun.setScale({0.9,0.9});

    sf::Vector2f origin = Sun.getOrigin();
    Sun.setOrigin({sunSpaceTexture.getSize().x/2,sunSpaceTexture.getSize().y/2});
    }

void Background::themeApoc(){
    velCof = 1;

    Style = 4;
    backgroundSky.setTexture(bgSkyApocTexture);
    // buildings
    backgroundSky.setColor(sf::Color({255,255,255,255}));

    backgroundBuildings.setTexture(bgBuildingsTexture);
    backgroundBuildings.setColor({135,0,0,100});

  //  sunShine.setColor({135,0,0,255});
    sunShine.setColor({255,0,0,200});
    sunShine.setScale({1.4,1.4});
    sunShine.setOrigin({sunShineTexture.getSize().x/2,sunShineTexture.getSize().y/2});

    Sun.setTexture(sunApocTexture);
    Sun.setPosition(sunApocInitialPos);
    Sun.setColor(sf::Color({255,255,255,255}));
    Sun.setScale({0.9,0.9});

    sf::Vector2f origin = Sun.getOrigin();
  //  Sun.setOrigin({sunApocTexture.getSize().x,origin.y});
    Sun.setOrigin({sunApocTexture.getSize().x/2,sunApocTexture.getSize().y/2});
    }


