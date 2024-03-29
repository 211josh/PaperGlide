#include "plane.h"
#include <iostream>

sf::Sprite Plane::sprite;

float Plane::spawnTimer = 0;
float Plane::animationTimer = 0;
float Plane::spawnTimerMax; // Maximum amount of spawn delay between plane leaving and re-entering screen

sf::Vector2f Plane::initialVel{-1050.0f,0.0f}; // Initial velocity
sf::Vector2f Plane::velocity = Plane::initialVel; // Initial velocity
sf::Vector2f Plane::maxVel{-2000.0f,0.0f};
float Plane::velDif = (velocity.x - maxVel.x);

sf::IntRect Plane::rectFirstSprite(0,0,550,300); // For animation. First texture is (0,0) to (550,300)

Plane::Plane(){
    if(!texture.loadFromFile("sprites/Plane.png")){
        std::cout << "Could not load Plane texture";
        }
    sprite.setTexture(texture);
    sprite.setTextureRect(rectFirstSprite);
    sprite.setPosition(2000,2000);
    }

    void Plane::update(sf::RenderWindow& window, float deltaTime){

        animation(deltaTime);

        spawnTimerMax = -750.0f / velocity.x; // slowest: 0.75s max. fastest: 0.375 second max.

        sf::Vector2f position = sprite.getPosition();
        if(position.x < -100){
            spawnTimer += deltaTime;
            if(spawnTimer > spawnTimerMax){
                randomProp();
                }
            } // random prop sets a random beginning time between 0 and spawntimermax. when plane goes offscreen, timer begins to increase.
              // this adds an element of randomness for how long the plane respawns on the other side of the screen

        movement(deltaTime);
        window.draw(sprite);
    }

void Plane::movement(float deltaTime){ // Movement across screen
        sprite.move(velocity*deltaTime);
    }

void Plane::randomProp(){ // Random properties between different planes

    sprite.setScale(sf::Vector2f(1,1));

    float yPos = static_cast<float>(std::rand() % 400);
    float scale = static_cast<float>((std::rand() % 1) + 0.5f);

    sprite.scale(sf::Vector2f(scale,scale)); // Increase by random size, calculated above

    sf::Vector2u textureSize = texture.getSize();
    sprite.setOrigin(textureSize.x/8,textureSize.y/2); // divided by 8 because animation is 4 frames

    sprite.setPosition(sf::Vector2f(1400,yPos)); // y-pos is random, calculated above

    spawnTimer = (static_cast<float>(std::rand()) / RAND_MAX) * spawnTimerMax; // float between 0 and spawnTimerMax
    }

void Plane::increaseVel(float velRange){
    velocity.x -= velDif/velRange;
    }

void Plane::resetGame(){
    velocity = initialVel;
    sprite.setPosition(3000,2000);
    }

void Plane::animation(float deltaTime){
    animationTimer += deltaTime;
    if(animationTimer > 0.05f){
        if(rectFirstSprite.left == 1650){ // if it's on the last one, reset to beginning
            rectFirstSprite.left = 0;
        } else{
        rectFirstSprite.left += 550; // Sprite texture shifts 300 to the right
        }
    sprite.setTextureRect(rectFirstSprite);
    animationTimer = 0;
    }
    }

void Plane::testMode(sf::RenderWindow& window, float deltaTime){
    sprite.setPosition({500,300});
    animation(deltaTime);
    window.draw(sprite);
    }
