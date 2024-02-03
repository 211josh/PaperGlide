#include <cmath>
#include <iostream>

#include "player.h"

Player::Player(){
    if(!texture.loadFromFile("sprites/Player.png")){
        std::cout << "Could not load Player texture" << std::endl;
        }
    if(!deathTexture.loadFromFile("sprites/Death.png")){
        std::cout << "Could not load Death screen texture" << std::endl;
        }
    if(!hitPlayer.loadFromFile("sprites/hitPlayer.png")){
        std::cout << "Could not load Death screen texture" << std::endl;
        }

    // Set texture, position and size of sprite
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(100,400));
    sprite.scale(sf::Vector2f(0.2,0.2));

    // Death screen sprite
    deathSprite.setTexture(deathTexture);
    deathSprite.setColor(sf::Color{255,255,255,50});

    // Set origin point to centre of sprite
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    }

void Player::update(sf::RenderWindow& window, float deltaTime, int screenHeight, int& gameState, Building& building, Plane& plane, Helicopter& helicopter, Sounds& sound) { // Continuously update the sprite inside the window
    handleInput(deltaTime, gameState);
    applyGravity(deltaTime);
    window.draw(sprite);
    deathCheck(gameState, screenHeight, sound);
    collision(gameState, building, plane, helicopter, window);
    hitSequence(deltaTime, window, sound, gameState);
    }

float Player::playerTimer = 0;
bool Player::collided = 0; // Prevents unlimited hit sequences
bool Player::hitSoundPlayed = 0; // Prevents unlimited hit sound
bool Player::gameOverPlayed = 0; // Prevents infinite game over sound
float Player::deathScreenTime = 0; // How long the hit screen / player texture change lasts

void Player::menuUpdate(sf::RenderWindow& window, float deltaTime){ // In menu state, player hovers on left of screen
    playerTimer += deltaTime;
    menuFloating(deltaTime);
    window.draw(sprite);
    }

float Player::speed = -2500.0f; // Speed of upwards movements
float Player::gravity = speed * -0.5f; // Gravity strength
float Player::terminalVel = 1000.0f; // Terminal vertical velocity
float Player::maxRotation = 70.0f; // Max rotation of sprite [-max,max]
sf::Vector2f Player::velocity{0.0f,0.0f}; // Initial velocity

void Player::handleInput(float deltaTime, int gameState) { // Control player with Space
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && collided == 0){
        velocity.y += speed * deltaTime;
        }
    }

void Player::applyGravity(float deltaTime) { // Gravity on player
    velocity.y += gravity * deltaTime;
    if(velocity.y > terminalVel){
        velocity.y = terminalVel;
        }
    if(velocity.y < -terminalVel){
        velocity.y = -terminalVel;
        }
    sprite.move(velocity*deltaTime);
    // Rotation
    sprite.setRotation((maxRotation * velocity.y)/terminalVel);
    }

void Player::menuFloating(float deltaTime){
    sprite.setTexture(texture);
    sprite.setPosition(100,150*sin(playerTimer) + 400);
    sprite.setRotation((maxRotation/4 * cos(playerTimer)));
    }

void Player::deathCheck(int& gameState, int screenHeight, Sounds& sound){
    sf::Vector2f currentPos = sprite.getPosition();
    if(currentPos.y > screenHeight){
        collided = 1;
        if(gameOverPlayed == 0){
            sound.gameOverSound();
            gameState = 3; // Try again screen
            gameOverPlayed = 1;
            }
        }
    if(currentPos.y < 0){
        collided = 1;
        }
    }


void Player::resetGame(int gameState){
    if(gameState == 3){
        sprite.setPosition(100,400);
        }
    velocity.y = 0;
    collided = 0;
    hitSoundPlayed = 0;
    deathScreenTime = 0;
    gameOverPlayed = 0;
    sprite.setTexture(texture);
    }

void Player::collision(int& gameState, Building& building, Plane& plane, Helicopter& helicopter, sf::RenderWindow& window){

    if(Collision::PixelPerfectTest(sprite, Building::sprite)){ // BUILDING COLLISION
        collided = 1;
        }

    if(Collision::PixelPerfectTest(sprite, Plane::sprite)){ // PLANE COLLISION
        collided = 1;
        }

    if(Collision::PixelPerfectTest(sprite, Helicopter::sprite)){ // HELICOPTER COLLISION
        collided = 1;
        }

    }

void Player::hitSequence(float deltaTime, sf::RenderWindow& window, Sounds& sound, int& gameState){ // Visualisation and audio of what happens when player collides w/ sprite
    if(collided == 1 && hitSoundPlayed == 0){
        sound.hitSound();
        hitSoundPlayed = 1;
        }
    if(collided == 1 && deathScreenTime < 0.3){ // How many seconds the red screen shows for
        deathScreenTime += deltaTime;
        window.draw(deathSprite);
        sprite.setTexture(hitPlayer);
        }
    if(deathScreenTime >= 0.3){
        sprite.setTexture(texture); // Reset texture to normal player
        }
    }


