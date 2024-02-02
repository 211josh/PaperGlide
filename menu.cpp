#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "menu.h"

sf::Sprite Menu::upArrow;

Menu::Menu(){
    if(!font.loadFromFile("sprites/Font.ttf")){
        std::cout << "Could not load Menu font";
    }
    if(!arrowTexture.loadFromFile("sprites/upArrow.png")){
        std::cout << "Could not load upArrow font";
    }

    menuSelect = 0; // Menu opens on play option
    selectTimer = 0; // Min time wait between changing menu option. Prevents endless fast scrolling.

    playText.setFont(font); // Setting menu fonts to font
    settingsText.setFont(font);
    quitText.setFont(font);
    versionText.setFont(font);

    holdSpaceText.setFont(font);
    holdSpaceText.setString("Hold Space");
    holdSpaceText.setCharacterSize(25);
    holdSpaceText.setColor(sf::Color{255,255,255,200});
    holdSpaceText.setOrigin(sf::Vector2f(0.0f,0.0f));

    upArrow.setTexture(arrowTexture);
    upArrow.setColor(sf::Color{255,255,255,200});
    }


void Menu::menuUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, Score& score){

    holdSpaceDisplay(window, player);

    Menu::playText.setString("Play"); // Words on menu screen
    settingsText.setString("Settings");
    quitText.setString("Quit");
    versionText.setString("v1.0");

    playText.setCharacterSize(120); // Word sizes
    settingsText.setCharacterSize(120);
    quitText.setCharacterSize(120);
    versionText.setCharacterSize(30);

    sf::FloatRect playTextBounds = playText.getLocalBounds(); // Retrieve menu option bounds
    sf::FloatRect settingsTextBounds = settingsText.getLocalBounds();
    sf::FloatRect quitTextBounds = quitText.getLocalBounds();

    playText.setPosition((screenWidth - playTextBounds.width) / 2, 160); // Centres text based on text and screen width
    settingsText.setPosition((screenWidth - settingsTextBounds.width) / 2, 270);
    quitText.setPosition((screenWidth - quitTextBounds.width) / 2, 380);
    versionText.setPosition(1200,675);

    handleInput(window, deltaTime, gameState, sound, background, player, building, helicopter, plane, Score::current_score, score);
    selectTimer += deltaTime;

    if(menuSelect == 0){
        playText.setColor(sf::Color{255,255,0,200});
        settingsText.setColor(sf::Color{255,255,255,200});
        quitText.setColor(sf::Color{255,255,255,200});
        }

    if(menuSelect == 1){
        playText.setColor(sf::Color{255,255,255,200});
        settingsText.setColor(sf::Color{255,255,0,200});
        quitText.setColor(sf::Color{255,255,255,200});
        }

    if(menuSelect == 2){
        playText.setColor(sf::Color{255,255,255,200});
        settingsText.setColor(sf::Color{255,255,255,200});
        quitText.setColor(sf::Color{255,255,0,200});
        }

    versionText.setColor(sf::Color{255,255,255,70});

    window.draw(playText);
    window.draw(settingsText);
    window.draw(quitText);
    window.draw(versionText);
    }

void Menu::tryUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, int& current_score, Score& score){

    Menu::playText.setString("Retry"); // Words on menu screen
    settingsText.setString("Menu");
    quitText.setString("Quit");

    playText.setCharacterSize(90); // Word sizes
    settingsText.setCharacterSize(90);
    quitText.setCharacterSize(90);

    sf::FloatRect playTextBounds = playText.getLocalBounds(); // Retrieve menu option bounds
    sf::FloatRect settingsTextBounds = settingsText.getLocalBounds();
    sf::FloatRect quitTextBounds = quitText.getLocalBounds();

    playText.setPosition((screenWidth - playTextBounds.width) / 2, 250); // Centres text based on text and screen width
    settingsText.setPosition((screenWidth - settingsTextBounds.width) / 2, 350);
    quitText.setPosition((screenWidth - quitTextBounds.width) / 2, 450);
    versionText.setPosition(1200,675);

    handleInput(window, deltaTime, gameState, sound, background, player, building, helicopter, plane, current_score, score);
    selectTimer += deltaTime;

    if(menuSelect == 0){
        playText.setColor(sf::Color{255,255,0,200});
        settingsText.setColor(sf::Color{255,255,255,200});
        quitText.setColor(sf::Color{255,255,255,200});
        }

    if(menuSelect == 1){
        playText.setColor(sf::Color{255,255,255,200});
        settingsText.setColor(sf::Color{255,255,0,200});
        quitText.setColor(sf::Color{255,255,255,200});
        }

    if(menuSelect == 2){
        playText.setColor(sf::Color{255,255,255,200});
        settingsText.setColor(sf::Color{255,255,255,200});
        quitText.setColor(sf::Color{255,255,0,200});
        }

    versionText.setColor(sf::Color{255,255,255,70});

    window.draw(playText);
    window.draw(settingsText);
    window.draw(quitText);
    }

void Menu::handleInput(sf::RenderWindow& window, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, int& current_score, Score& score){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && selectTimer > 0.2f){
        menuSelect = ((menuSelect + 1)%3 + 3) % 3;
        selectTimer = 0.0f;
        sound.menuSound();
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && selectTimer > 0.2f){
        menuSelect = ((menuSelect - 1)%3 +3 ) % 3; // C++ modulo doesn't work w/ negative numbers, so made our own
        selectTimer = 0.0f;
        sound.menuSound();
        }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuSelect == 0){ // i.e game starts / retries
        background.resetGame();
        player.resetGame(gameState);
        building.resetGame(score);
        helicopter.resetGame();
        plane.resetGame();

        sound.startSound();
        gameState = 1;

        Score::current_score = 0;
        }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuSelect == 1){ // Option 2
        if(gameState==3){ // If on try again menu, i.e menu option
            player.resetGame(gameState);
            gameState = 0;
            }
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuSelect == 2){
        window.close();
        }
    }

void Menu::holdSpaceDisplay(sf::RenderWindow& window, Player& player){

    holdSpaceText.setPosition(30,150*sin(Player::playerTimer) + 440);
    upArrow.setPosition(180,150*sin(Player::playerTimer) + 440);

    window.draw(holdSpaceText);

    int spaceTimer = Player::playerTimer*1.2;
    if(spaceTimer % 2 == 0){
        window.draw(upArrow);
        }
    }
