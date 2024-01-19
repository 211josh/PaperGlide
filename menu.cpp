#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "menu.h"

Menu::Menu(){
    if(!font.loadFromFile("sprites/Font.ttf")){
    std::cout << "Could not load Menu font";
    }

    menuSelect = 0; // Menu opens on play option
    selectTimer = 0; // Min time wait between changing menu option. Prevents endless fast scrolling.

    playText.setFont(font); // Setting menu fonts to font
    settingsText.setFont(font);
    quitText.setFont(font);

    Menu::playText.setString("Play"); // Words on menu screen
    settingsText.setString("Settings");
    quitText.setString("Quit");

    playText.setCharacterSize(170); // Word sizes
    settingsText.setCharacterSize(170);
    quitText.setCharacterSize(170);
    }


void Menu::menuUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState, Sounds& sound){

    sf::FloatRect playTextBounds = playText.getLocalBounds(); // Retrieve menu option bounds
    sf::FloatRect settingsTextBounds = settingsText.getLocalBounds();
    sf::FloatRect quitTextBounds = quitText.getLocalBounds();

    playText.setPosition((screenWidth - playTextBounds.width) / 2, 50); // Centres text based on text and screen width
    settingsText.setPosition((screenWidth - settingsTextBounds.width) / 2, 250);
    quitText.setPosition((screenWidth - quitTextBounds.width) / 2, 450);

    handleInput(window, deltaTime, gameState, sound);
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

    window.draw(playText);
    window.draw(settingsText);
    window.draw(quitText);
    }

void Menu::handleInput(sf::RenderWindow& window, float deltaTime, int& gameState, Sounds& sound){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && selectTimer > 0.2f){
        menuSelect = ((menuSelect + 1)%3 + 3) % 3;
        selectTimer = 0.0f;
        sound.menuSound();
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && selectTimer > 0.2f){
        menuSelect = ((menuSelect - 1)%3 +3 ) % 3; // C++ modulo doesn't work w/ negative numbers, so made our own
        selectTimer = 0.0f;
        sound.menuSound();
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && menuSelect == 0){
        gameState = 1;
        sound.startSound();
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && menuSelect == 2){
        window.close();
        }
    }
