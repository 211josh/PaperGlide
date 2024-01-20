#include "plane.h"
#include <iostream>

sf::Vector2f Plane::initialVel{-1050.0f,0.0f}; // Initial velocity
sf::Vector2f Plane::velocity = Plane::initialVel; // Initial velocity
sf::Vector2f Plane::maxVel{-2000.0f,0.0f};
float Plane::velDif = (velocity.x - maxVel.x);

float Plane::spawnTimer = 3.0f;
float Plane::spawnInterval = -(1700.0f/(velocity.x));

Plane::Plane(){
    if(!texture.loadFromFile("sprites/Plane.png")){
    std::cout << "Could not load Plane texture";
    }
    sprite.setTexture(texture);
    }

    void Plane::update(sf::RenderWindow& window, float deltaTime){
        if(spawnTimer >= spawnInterval){
            randomProp();
        }
        movement(deltaTime);
        spawnTimer += deltaTime;
        window.draw(sprite);
    }

void Plane::movement(float deltaTime){ // Movement across screen
        sprite.move(velocity*deltaTime);
    }

void Plane::randomProp(){ // Random properties between different planes
    spawnTimer = 0.0f + (static_cast<float>(std::rand() % -(800))/velocity.x); // Incorporate randomness into spawn interval
    spawnInterval = -(1700.0f/(velocity.x));

    sprite.setScale(sf::Vector2f(1,1));

    float yPos = static_cast<float>(std::rand() % 400);
    float scale = static_cast<float>((std::rand() % 1) + 0.5f);

    sprite.scale(sf::Vector2f(scale,scale)); // Increase by random size, calculated above

    sf::Vector2u textureSize = texture.getSize();
    sprite.setOrigin(textureSize.x/2,textureSize.y/2);

    sprite.setPosition(sf::Vector2f(1400,yPos)); // y-pos is random, calculated above
    }

void Plane::increaseVel(float velRange){
    velocity.x -= velDif/velRange;
    }

void Plane::resetGame(){
    velocity = initialVel;
    sprite.setPosition(2000,2000);
    }
