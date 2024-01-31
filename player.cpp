#include <cmath>
#include <iostream>

#include "player.h"

Player::Player(){
    if(!texture.loadFromFile("sprites/Player.png")){
        std::cout << "Could not load Player texture";
        }
    // Set texture, position and size of sprite
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(100,400));
    sprite.scale(sf::Vector2f(0.2,0.2));

    // Set origin point to centre of sprite
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    }

void Player::update(sf::RenderWindow& window, float deltaTime, int screenHeight, int& gameState, Building& building, Plane& plane, Helicopter& helicopter) { // Continuously update the sprite inside the window
    handleInput(deltaTime);
    applyGravity(deltaTime);
    window.draw(sprite);
    deathCheck(gameState, screenHeight);
    collision(gameState, building, plane, helicopter);
    }

float Player::playerTimer = 0;

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

void Player::handleInput(float deltaTime) { // Control player with Space
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
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
    sprite.setPosition(100,150*sin(playerTimer) + 400);
    sprite.setRotation((maxRotation/4 * cos(playerTimer)));
    }

void Player::deathCheck(int& gameState, int screenHeight){
    sf::Vector2f currentPos = sprite.getPosition();
    if(currentPos.y < 0 || currentPos.y > screenHeight){
        gameState = 3; // Try again screen
        }
    }

void Player::resetGame(int gameState){
    if(gameState == 3){
        sprite.setPosition(100,400);
        }
    velocity.y = 0;
    }

void Player::collision(int& gameState, Building& building, Plane& plane, Helicopter& helicopter){
    sf::FloatRect playerHitbox = sprite.getGlobalBounds();
    sf::FloatRect buildHitbox = building.getHitbox();

    if(playerHitbox.intersects(buildHitbox)){
        gameState = 3;
        }
    }

