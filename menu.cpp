#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "menu.h"

sf::Sprite Menu::upArrow;

Menu::Menu(int screenWidth){
    if(!font.loadFromFile("sprites/Font.ttf")){
        std::cout << "Could not load Menu font";
    }
    if(!arrowTexture.loadFromFile("sprites/upArrow.png")){
        std::cout << "Could not load upArrow font";
    }

    menuSelect = 0; // Menu opens on play option
    selectTimer = 0; // Min time wait between changing menu option. Prevents endless fast scrolling.

    //Menu
    playText.setFont(font);
    settingsText.setFont(font);
    quitText.setFont(font);
    versionText.setFont(font);

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

    // Retry
    retryText.setFont(font);
    menuText.setFont(font);
    quit2Text.setFont(font);

    retryText.setString("Retry");
    menuText.setString("Menu");
    quit2Text.setString("Quit");

    retryText.setCharacterSize(90);
    menuText.setCharacterSize(90);
    quit2Text.setCharacterSize(90);

    sf::FloatRect retryBounds = retryText.getLocalBounds(); // Retrieve menu option bounds
    sf::FloatRect menuBounds = menuText.getLocalBounds();
    sf::FloatRect quit2Bounds = quit2Text.getLocalBounds();

    retryText.setPosition((screenWidth - retryBounds.width) / 2, 250); // Centres text based on text and screen width
    menuText.setPosition((screenWidth - menuBounds.width) / 2, 350);
    quit2Text.setPosition((screenWidth - quit2Bounds.width) / 2, 450);

    // Settings
    fullscreenText.setFont(font);
    volumeText.setFont(font);
    backText.setFont(font);

    fullscreenText.setString("Fullscreen");
    volumeText.setString("Volume:");
    backText.setString("Back");

    fullscreenText.setCharacterSize(90);
    volumeText.setCharacterSize(90);
    backText.setCharacterSize(90);


    sf::FloatRect fullscreenBounds = fullscreenText.getLocalBounds(); // Retrieve menu option bounds
    sf::FloatRect volumeTextBounds = volumeText.getLocalBounds();
    sf::FloatRect backTextBounds = backText.getLocalBounds();

    fullscreenText.setPosition((screenWidth - fullscreenBounds.width) / 2, 200); // Centres text based on text and screen width
    volumeText.setPosition((screenWidth - volumeTextBounds.width) / 2, 300);
    backText.setPosition((screenWidth - backTextBounds.width) / 2, 400);

    // Hold space
    holdSpaceText.setFont(font);
    holdSpaceText.setString("Hold Space");
    holdSpaceText.setCharacterSize(25);
    holdSpaceText.setColor(sf::Color{255,255,255,200});
    holdSpaceText.setOrigin(sf::Vector2f(0.0f,0.0f));

    // Up arrow
    upArrow.setTexture(arrowTexture);
    upArrow.setColor(sf::Color{255,255,255,200});
    }


void Menu::menuUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, Score& score){

    holdSpaceDisplay(window, player);
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

void Menu::settingsUpdate(sf::RenderWindow& window, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, int& current_score, Score& score){

    holdSpaceDisplay(window, player);

    handleInput(window, deltaTime, gameState, sound, background, player, building, helicopter, plane, current_score, score);
    selectTimer += deltaTime;

    if(menuSelect == 0){
        fullscreenText.setColor(sf::Color{255,255,0,200});
        volumeText.setColor(sf::Color{255,255,255,200});
        backText.setColor(sf::Color{255,255,255,200});
        }

    if(menuSelect == 1){
        fullscreenText.setColor(sf::Color{255,255,255,200});
        volumeText.setColor(sf::Color{255,255,0,200});
        backText.setColor(sf::Color{255,255,255,200});
        }

    if(menuSelect == 2){
        fullscreenText.setColor(sf::Color{255,255,255,200});
        volumeText.setColor(sf::Color{255,255,255,200});
        backText.setColor(sf::Color{255,255,0,200});
        }

    window.draw(fullscreenText);
    window.draw(volumeText);
    window.draw(backText);
}

void Menu::tryUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, int& current_score, Score& score){

    handleInput(window, deltaTime, gameState, sound, background, player, building, helicopter, plane, current_score, score);
    selectTimer += deltaTime;

    if(menuSelect == 0){
        retryText.setColor(sf::Color{255,255,0,200});
        menuText.setColor(sf::Color{255,255,255,200});
        quit2Text.setColor(sf::Color{255,255,255,200});
        }

    if(menuSelect == 1){
        retryText.setColor(sf::Color{255,255,255,200});
        menuText.setColor(sf::Color{255,255,0,200});
        quit2Text.setColor(sf::Color{255,255,255,200});
        }

    if(menuSelect == 2){
        retryText.setColor(sf::Color{255,255,255,200});
        menuText.setColor(sf::Color{255,255,255,200});
        quit2Text.setColor(sf::Color{255,255,0,200});
        }

    versionText.setColor(sf::Color{255,255,255,70});

    window.draw(retryText);
    window.draw(menuText);
    window.draw(quit2Text);
    }

void Menu::handleInput(sf::RenderWindow& window, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, int& current_score, Score& score){
    // CONTROLS
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

    // MENU SELECTION

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && selectTimer > 0.2f){ // If Enter is pressed
        selectTimer = 0.0f;

        if(gameState == 0){ // IF ON THE MENU. OUR CHOICES ARE: PLAY, SETTINGS, QUIT
            if(menuSelect == 0){ // if we press play
                background.resetGame();
                player.resetGame(gameState);
                building.resetGame(score);
                helicopter.resetGame();
                plane.resetGame();

                sound.startSound();
                gameState = 1;

                Score::current_score = 0;
            }
            if(menuSelect == 1){ // if we press settings
                gameState = 2;
                menuSelect = 0;
            }

            if(menuSelect == 2){ // if we press quit
                window.close();
            }
        }

        if(gameState == 2){ // IF ON SETTINGS. OUR CHOICES ARE FULLSCREEN, VOLUME, BACK
            if(menuSelect == 0){ // if we press Fullscreen

                }
            if(menuSelect == 1){ // if we press Volume

                }
            if(menuSelect == 2){ // if we press Back
                menuSelect = 0;
                gameState = 0;
                }
        }

        if(gameState == 3){ // IF ON TRY AGAIN MENU. OUR CHOICES ARE RETRY, MENU, QUIT
            if(menuSelect == 0){ // if we press Play
                background.resetGame();
                player.resetGame(gameState);
                building.resetGame(score);
                helicopter.resetGame();
                plane.resetGame();

                sound.startSound();
                gameState = 1;

                Score::current_score = 0;
            }
            if(menuSelect == 1){ // if we press Menu
                gameState = 0;

            }
            if(menuSelect == 2){ // if we press Quit
                window.close();
            }
        }
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
