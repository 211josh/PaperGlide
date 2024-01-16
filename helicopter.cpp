#include "helicopter.h"


Helicopter::Helicopter() {
if(!texture.loadFromFile("sprites/Helicopter.png")){
    std::cout <<"Could not load Helicopter texture";
    }

sprite.setTexture(texture);
sprite.setPosition(4000.0f,4000.0f);
}

void Helicopter::update(sf::RenderWindow& window, float deltaTime){
    if(spawnTimer >= spawnInterval){
        randomProp();
        spawnTimer = 0.0f + (static_cast<float>(std::rand() % -(800))/velocity.x); // Resets spawn timer, with some randomness deducted
        }
    movement(deltaTime);
    spawnTimer += deltaTime;
    window.draw(sprite);
    }

sf::Vector2f Helicopter::velocity{-200.0f,0.0f};

float Helicopter::spawnTimer = 0.0f;
float Helicopter::spawnInterval = -(2000.0f/velocity.x);
float Helicopter::heliTimer = 0;
float Helicopter::initialyPos;

void Helicopter::movement(float deltaTime){ // Movement across screen
    heliTimer += deltaTime;
    sprite.move(velocity*deltaTime);
    sf::Vector2f position = sprite.getPosition();
    sprite.setPosition(position.x,200*sin(heliTimer) + initialyPos); // y-position = (movement range) * sin(time) + initial y-pos
    }


void Helicopter::randomProp(){ // Random properties between different helicopters
    sprite.setScale(sf::Vector2f(1,1));
    // First number is the random range 0 to x. The + shifts that range.
    float yPos = static_cast<float>((std::rand() % 720)); // In SFML, 0,0 is the top left, screenWidthxscreenHeight is the bottom right.
    float scale = static_cast<float>((std::rand() % 1)*1.5 +0.5);
    sprite.scale(sf::Vector2f(scale,scale));
    sf::Vector2u textureSize = texture.getSize();
    sprite.setOrigin(textureSize.x/2,textureSize.y/2);
    sprite.setPosition(sf::Vector2f(1400,yPos));
    sprite.setRotation(20.0f);
    initialyPos = yPos;
    }
