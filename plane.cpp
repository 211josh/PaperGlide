#include "plane.h"
#include <iostream>

sf::Vector2f Plane::velocity{-1050.0f,0.0f}; // Initial velocity
sf::Vector2f Plane::maxVel{-2000.0f,0.0f};
float Plane::velDif = (velocity.x - maxVel.x);

// Movement speed will slowly increase, so spawn interval is based on speed, i.e how long it takes to cross the screen
float Plane::spawnTimer = 3.0f; // Spawn  timer values
float Plane::spawnInterval = -(1700.0f/(velocity.x)); // Time between building reset

Plane::Plane(){
    if(!texture.loadFromFile("sprites/Plane.png")){
    std::cout << "Could not load Plane texture";
    }
    sprite.setTexture(texture);
    }

    void Plane::update(sf::RenderWindow& window, float deltaTime){
        if(spawnTimer >= spawnInterval){
            randomProp();
            spawnTimer = 0.0f + (static_cast<float>(std::rand() % -(800))/velocity.x); // Incorporate randomness into spawn interval
        }
        movement(deltaTime);
        spawnTimer += deltaTime;
        window.draw(sprite);
    }

void Plane::movement(float deltaTime){ // Movement across screen
        sprite.move(velocity*deltaTime);
    }

void Plane::randomProp(){ // Random properties between different buildings
    sprite.setScale(sf::Vector2f(1,1));
    // First number is the random range 0 to x. The + shifts that range.
    float yPos = static_cast<float>(std::rand() % 400); // In SFML, 0,0 is the top left, screenWidth x screenHeight is the bottom right.
    float scale = static_cast<float>((std::rand() % 1) + 0.5f);
    sprite.scale(sf::Vector2f(scale,scale));
    sf::Vector2u textureSize = texture.getSize(); // Make origin centre of texture
    sprite.setOrigin(textureSize.x/2,textureSize.y/2);
    sprite.setPosition(sf::Vector2f(1400,yPos));
    spawnInterval = -(1700.0f/(velocity.x));
    }

void Plane::increaseVel(float velRange){
    velocity.x -= velDif/velRange;
 //   std::cout << velocity.x << std::endl;
    }
