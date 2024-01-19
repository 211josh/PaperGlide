#include "helicopter.h"

sf::Vector2f Helicopter::velocity{-150.0f,0.0f};
sf::Vector2f Helicopter:: maxVel{-600.0f,0.0f};
float Helicopter::velDif = (velocity.x - maxVel.x);

float Helicopter::spawnTimer = 0.0f;
float Helicopter::spawnInterval;
float Helicopter::heliTimer = 0;
float Helicopter::initialyPos;

Helicopter::Helicopter() {
if(!texture.loadFromFile("sprites/Helicopter.png")){
    std::cout <<"Could not load Helicopter texture";
    }
    sprite.setTexture(texture);
    sprite.setPosition(4000.0f,4000.0f);
    spawnInterval = -(1000.0f/velocity.x); // Initial spawn interval
}

void Helicopter::update(sf::RenderWindow& window, float deltaTime){
    if(spawnTimer >= spawnInterval){
        randomProp();
        spawnTimer = 0.0f + (static_cast<float>(std::rand() % (800))/-velocity.x); // Resets spawn timer, with some randomness deducted
        spawnInterval = -(2200.0f/velocity.x); // Regular spawn interval
        std::cout << spawnTimer << std::endl;
        }
    movement(deltaTime);
    spawnTimer += deltaTime;
    std::cout << spawnTimer << std::endl;
    window.draw(sprite);
    }

void Helicopter::movement(float deltaTime){ // Movement across screen
    heliTimer += deltaTime;
    sprite.move(velocity*deltaTime);
    sf::Vector2f position = sprite.getPosition();
    sprite.setPosition(position.x,200*sin(heliTimer) + initialyPos); // y-position = (movement range) * sin(time) + initial y-pos
    }


void Helicopter::randomProp(){ // Random properties between different helicopters
    sprite.setScale(sf::Vector2f(1,1));
    // First number is the random range 0 to x. The + shifts that range.
    float yPos = static_cast<float>((std::rand() % 620)+50); // In SFML, 0,0 is the top left, screenWidthxscreenHeight is the bottom right.
    float scale = static_cast<float>((std::rand() % 1)*1.5 +0.5);
    sprite.scale(sf::Vector2f(scale,scale));
    sf::Vector2u textureSize = texture.getSize();
    sprite.setOrigin(textureSize.x/2,textureSize.y/2);
    sprite.setPosition(sf::Vector2f(1400,yPos));
    sprite.setRotation(20.0f);
    initialyPos = yPos;
    }

void Helicopter::increaseVel(float velRange){
    velocity.x -= velDif/velRange;
 //   std::cout << velocity.x << std::endl;
    }
