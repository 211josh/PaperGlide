#include "helicopter.h"

sf::Sprite Helicopter::sprite;

sf::Vector2f Helicopter::initialVel{-150.0f,0.0f};
sf::Vector2f Helicopter::velocity = Helicopter::initialVel;
sf::Vector2f Helicopter:: maxVel{-400.0f,0.0f};

sf::IntRect Helicopter::rectFirstSprite(0,0,550,300); // For animation. First texture is (0,0) to (550,400)

float Helicopter::velDif = (velocity.x - maxVel.x);

float Helicopter::heliTimer = 0;
float Helicopter::animationTimer = 0;
float Helicopter::initialyPos;

float Helicopter::spawnTimer = 0;
float Helicopter::spawnTimerMax; // Maximum amount of spawn delay between plane leaving and re-entering screen

Helicopter::Helicopter() {
if(!texture.loadFromFile("sprites/Helicopter.png")){
    std::cout <<"Could not load Helicopter texture";
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(rectFirstSprite);
    resetGame();
}

void Helicopter::update(sf::RenderWindow& window, float deltaTime){

    animation(deltaTime);

    spawnTimerMax = -200.0f / velocity.x; // slowest: 1.33s max. fastest: 0.5 second max.

    sf::Vector2f position = sprite.getPosition();

    if(position.x < -100){
        spawnTimer += deltaTime;
        if(spawnTimer > spawnTimerMax){
            randomProp();
            }
        }

    movement(deltaTime);
    window.draw(sprite);
    }

void Helicopter::movement(float deltaTime){ // Movement across screen
    heliTimer += deltaTime;
    sprite.move(velocity*deltaTime);
    sf::Vector2f position = sprite.getPosition();
    sprite.setPosition(position.x,200*sin(heliTimer) + initialyPos); // y-position = (movement range) * sin(time) + initial y-pos
    }                                                                // Gives off hovering effect


void Helicopter::randomProp(){ // Random properties between different helicopters

    sprite.setScale(sf::Vector2f(1,1));
    // First number is the random range 0 to x. The + shifts that range.
    float yPos = static_cast<float>((std::rand() % 620)+50);
    float scale = static_cast<float>((std::rand() % 1)*1.5 +0.5);
    sprite.scale(sf::Vector2f(scale,scale));

    sf::Vector2u textureSize = texture.getSize();
    sprite.setOrigin(textureSize.x/8,textureSize.y/2); // divided by 8 because of 4 frames

    sprite.setPosition(sf::Vector2f(1500,yPos));
    sprite.setRotation(20.0f);
    initialyPos = yPos;

    spawnTimer = (static_cast<float>(std::rand()) / RAND_MAX) * spawnTimerMax; // float between 0 and spawnTimerMax
    }

void Helicopter::increaseVel(float velRange){
    velocity.x -= velDif/velRange;
    }

void Helicopter::resetGame(){
    velocity = initialVel;
    randomProp();
    sprite.move({1200.0f,0.0f}); // Initial delay at start of game
    }

void Helicopter::animation(float deltaTime){
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

void Helicopter::testMode(sf::RenderWindow& window, float deltaTime){
    sprite.setPosition({300,300});
    animation(deltaTime);
    window.draw(sprite);
    }
