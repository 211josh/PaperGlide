#include <cmath>
#include <iostream>

#include "player.h"

int Player::Style;

Player::Player(){

    readTheme();

    if(!playerNormal.loadFromFile("sprites/playerNormal.png")){
        std::cout << "Could not load Player (Normal) texture" << std::endl;
        }
    if(!playerPixel.loadFromFile("sprites/playerPixel.png")){
        std::cout << "Could not load Player (Pixel) texture" << std::endl;
        }
    if(!playerOrigami.loadFromFile("sprites/playerOrigami.png")){
        std::cout << "Could not load Player (Origami) texture" << std::endl;
        }
    if(!playerGold.loadFromFile("sprites/playerGold.png")){
        std::cout << "Could not load Player (Gold) texture" << std::endl;
        }
    if(!playerKing.loadFromFile("sprites/playerKing.png")){
        std::cout << "Could not load Player (King) texture" << std::endl;
        }
    if(!deathTexture.loadFromFile("sprites/Death.png")){
        std::cout << "Could not load Death screen texture" << std::endl;
        }

    // Set texture, position and size of sprite
    if(Style == 0){
        sprite.setTexture(playerNormal);
        }
    if(Style == 1){
        sprite.setTexture(playerPixel);
    }

    if(Style == 2){
        sprite.setTexture(playerGold);
        }
    if(Style == 3){
        sprite.setTexture(playerOrigami);
        }
    if(Style == 4){
        sprite.setTexture(playerKing);
        }
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
    if(window.hasFocus()){
        handleInput(deltaTime, gameState);
        }
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
    sprite.setPosition(100,150*sin(playerTimer) + 400);
    sprite.setRotation((maxRotation/4 * cos(playerTimer)));
    }

void Player::deathCheck(int& gameState, int screenHeight, Sounds& sound){
    sf::Vector2f currentPos = sprite.getPosition();
    if(currentPos.y > screenHeight){
        collided = 1;
        if(gameOverPlayed == 0){
            sound.gameOverSound();
            gameState = 4; // Try again screen
            gameOverPlayed = 1;
            }
        }
    if(currentPos.y < 0){
        collided = 1;
        }
    }

void Player::resetGame(int gameState){
    if(gameState == 4){
        sprite.setPosition(100,400);
        }
    velocity.y = 0;
    collided = 0;
    hitSoundPlayed = 0;
    deathScreenTime = 0;
    gameOverPlayed = 0;
    sprite.setColor(sf::Color(255,255,255,255));
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
        sprite.setColor(sf::Color(255,100,100,255));
        }
    if(deathScreenTime >= 0.3){
        // Reset texture to normal player
        sprite.setColor(sf::Color(255,255,255,255));
        }
    }

void Player::testMode(sf::RenderWindow& window, float deltaTime){
    sf::Vector2f velocityX = {200,0};
    sf::Vector2f velocityY = {0,200};

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        sprite.move(velocityX*deltaTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        sprite.move(-velocityX*deltaTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        sprite.move(-velocityY*deltaTime);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        sprite.move(velocityY*deltaTime);
    }

    if(Collision::PixelPerfectTest(sprite, Helicopter::sprite)){ // BUILDING COLLISION
        std::cout << "HELI COLLISION" << std::endl;
        } else if (Collision::PixelPerfectTest(sprite, Plane::sprite)){ // BUILDING COLLISION
        std::cout << "PLANE COLLISION" << std::endl;
        } else if(Collision::PixelPerfectTest(sprite, Building::sprite)){ // BUILDING COLLISION
        std::cout << "BUILDING COLLISION" << std::endl;
        } else {
        std::cout << "NO COLLISION" << std::endl;
        }

    window.draw(sprite);
    }

void Player::themeNormal(){
    Style = 0;
    sprite.setTexture(playerNormal);
    }
void Player::themePixel(){
    Style = 1;
    sprite.setTexture(playerPixel);
}
void Player::themeGold(){
    Style = 2;
    sprite.setTexture(playerGold);
    }
void Player::themeOrigami(){
    Style = 3;
    sprite.setTexture(playerOrigami);
    }
void Player::themeKing(){
    Style = 4;
    sprite.setTexture(playerKing);
    }

void Player::readTheme(){
    std::ifstream readPlayerFile;
    std::string str;
    readPlayerFile.open( "playerData.txt" );
    if(readPlayerFile.is_open()){
        while(!readPlayerFile.eof()){
                readPlayerFile >> str;
                Style = decrypt(str);
            }
        } else{ // if can't access file
            std::cout << "Could not open playerData file. Setting to normal." << std::endl;
            Style = 0;
        }
    readPlayerFile.close();
}

void Player::writeTheme(){
    std::ofstream writePlayerFile("playerData.txt");
    if(writePlayerFile.is_open()){
        writePlayerFile << encrypt(Style);
        }
    writePlayerFile.close();
}
