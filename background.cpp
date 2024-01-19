#include <SFML/Graphics.hpp>
#include <iostream>

#include "background.h"

sf::Vector2f Background::velocity{-187.0f,0.0f}; // Initial velocity
sf::Vector2f Background::maxVel{-800.0,0.0f};
float Background::velDif = (velocity.x - maxVel.x);

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

void Background::movement(float deltaTime){
    sprite.move(velocity*deltaTime);
}

void Background::resetPos(){ // First screen size of background texture is identical to last. Reset pos for infinite scroll illusion
    sf::Vector2f position = sprite.getPosition();
    if(position.x <= -5120){ // Beginning of last frame x value
        sprite.setPosition(sf::Vector2f{0.0f,0.0f});
    }
}

void Background::increaseVel(float velRange){ // Increase velocity
    velocity.x -= velDif/velRange;
}
