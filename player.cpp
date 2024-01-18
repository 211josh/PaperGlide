#include <cmath>

#include "player.h"

// Player sprite
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

void Player::update(sf::RenderWindow& window, float deltaTime) { // Continuously update the sprite inside the window
    handleInput(deltaTime);
    applyGravity(deltaTime);
    window.draw(sprite);
    }

float Player::playerTimer = 0;

void Player::menuUpdate(sf::RenderWindow& window, float deltaTime){
    playerTimer += deltaTime;
    menuFloating(deltaTime);
    window.draw(sprite);
    }

float Player::speed = -2500.0f; // Speed of movements. Works well at gravity x-2
float Player::gravity = speed * -0.5f; // Gravity strength
float Player::terminalVel = 1000.0f; // Terminal velocity
float Player::maxRotation = 70.0f; // Max rotation of sprite [-max,max]
sf::Vector2f Player::velocity{0.0f,0.0f}; // Initial velocity

void Player::handleInput(float deltaTime) { // Control player with WASD
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        velocity.y += speed * deltaTime;
    }
//   if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
//       sprite.move(sf::Vector2f{-speed/40000,0});
//   }
//   if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
//       sprite.move(sf::Vector2f{speed/40000,0});
//   }
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

