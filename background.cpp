#include <SFML/Graphics.hpp>
#include <iostream>

#include "background.h"

Background::Background(){
    if(!texture.loadFromFile("sprites/Background.png")){
    std::cout << "Could not load Background texture";
    }
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(0,0));
}



void Background::update(sf::RenderWindow& window, float deltaTime){
    movement(deltaTime);
    resetPos();
    window.draw(sprite);
}

sf::Vector2f Background::velocity{-200.0f,0.0f}; // Initial velocity

void Background::movement(float deltaTime){
    sprite.move(velocity*deltaTime);
}

void Background::resetPos(){ // First screen size of background texture is identical to last. Reset pos for infinite scroll illusion
    sf::Vector2f position = sprite.getPosition();
 //   std::cout << position.x << std::endl;
    if(position.x <= -5120){ // Beginning of last frame x value is 2560
        sprite.setPosition(sf::Vector2f{0.0f,0.0f});
    }
}
