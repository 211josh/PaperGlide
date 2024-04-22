#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>

#include "player.h"
#include "building.h"
#include "sounds.h"
#include "score.h"
#include "plane.h"
#include "helicopter.h"
#include "background.h"
#include "menu.h"

#include <fstream>

int screenWidth = 1280;
int screenHeight = 720;
int isFullscreen; // 0 for windowed, 1 for fullscreen
int gameState = 0; // 0 = main menu, 1 = gameplay, 2 = customisation, 3 = settings, 4 = try again, 5 = dev mode
int trailerMode = 0; // 0 to turn off trailer mode ( theme swapping )
float trailerTime = 0;
int trailerTheme = 0;

void trailer(float& trailerTime, float deltaTime, Player& player, Building& building, Background& background, Plane& plane, Helicopter& helicopter){
    trailerTime += deltaTime;
    std::cout << trailerTime << std::endl;
    if(trailerTime > 3){
        trailerTime = 0;
        trailerTheme = (trailerTheme + 1) % 6;
        switch(trailerTheme){
        case 0:
            player.themeNormal();
            building.themeNormal();
            background.themeNormal(plane, helicopter);
            break;
        case 1:
            background.trailerNight();
            break;
        case 2:
            player.themePixel();
            building.themeNormal();
            background.themePixel(plane, helicopter);
            break;
        case 3:
            player.themeGold();
            building.themeSunset();
            background.themeSunset(plane, helicopter); /// ADD NORMAL -> NIGHT -> PIXEL -> REST
            break;
        case 4:
            player.themeOrigami();
            building.themeApoc();
            background.themeApoc(plane, helicopter);
            break;
        case 5:
            player.themeKing();
            building.themeSpace();
            background.themeSpace(plane, helicopter);
            break;
        }
    }
}

void loadWindow(int screenWidth, int screenHeight, int& isFullscreen, sf::RenderWindow& window){

    std::ifstream readFullscreenFile;
    readFullscreenFile.open( "isFullscreen.txt" );
    if(readFullscreenFile.is_open()){
        std::string contents;
        while(!readFullscreenFile.eof()){ // while not at end of file
                readFullscreenFile >> contents; // 1 or 0
            }
        if(isWholeInteger(contents)){ // check isFullscreen.txt has an integer
            isFullscreen = std::stoi(contents);
            if(isFullscreen != 0 && isFullscreen != 1){ // check integer is valid
                std::cout << "isFullscreen does not equal 0 or 1. Setting to 0." << std::endl;
                isFullscreen = 0;
                }
            } else{
                std::cout << "isFullscreen.txt does not contain integer value. Setting to 0." << std::endl;
                isFullscreen = 0;
            }
        }
    readFullscreenFile.close();

    if (isFullscreen) {
        window.create(sf::VideoMode(screenWidth, screenHeight), "Paper Glide", sf::Style::Fullscreen);
    } else {
        window.create(sf::VideoMode(screenWidth, screenHeight), "Paper Glide");
        if(isFullscreen != 0){ // i.e fullscreen is not equal to 1 or 0
            std::cout << "Could not retrieve fullscreen setting. Setting to windowed." << std::endl;
            }
        }
    }

void setIcon(sf::RenderWindow& window, sf::Image icon){
    if(!icon.loadFromFile("sprites/icon.png")){
        std::cout << "Could not load icon texture" << std::endl;
        }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Random gen seed

    sf::RenderWindow window;
    loadWindow(screenWidth, screenHeight, isFullscreen, window);

    sf::Image icon;
    setIcon(window, icon);

    sf::Clock clock;

    Sounds sounds;
    Player player;
    Plane plane;
    Helicopter helicopter;
    Background background(plane, helicopter);
    Building building(background);
    Score score(background);
    Menu menu(screenWidth, score, background, plane, helicopter, player, sounds);

    while (window.isOpen()){ // Game loop
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
                }
            }
        window.setVerticalSyncEnabled(true);

        float deltaTime = clock.restart().asSeconds(); // clock starts and restarts in seconds
    //    std::cout << 1.f/deltaTime << std::endl; // FPS counter

        // Menu state
        if(gameState == 0){ // Order of update dictates layer
            background.update(window,deltaTime);
            menu.menuUpdate(window, screenWidth, deltaTime, gameState, sounds, background, player, building, helicopter, plane, score, isFullscreen, screenHeight);
            player.menuUpdate(window,deltaTime);
            score.displayHighScore(window, screenWidth);
            window.display();
        }

        // Play state
        if(gameState == 1){
            background.update(window,deltaTime);
            score.update(window,screenWidth, screenHeight, sounds, background, helicopter, plane, building, deltaTime);
            building.update(window, deltaTime, score);
            helicopter.update(window, deltaTime);
            plane.update(window, deltaTime); // Layers of graphics depends on order of update
            player.update(window, deltaTime, screenHeight, gameState, building, plane, helicopter, sounds);
            if(trailerMode == 1){
                trailer(trailerTime,deltaTime, player, building, background, plane, helicopter);
            }

            window.display();
        }

        if(gameState == 2){
            background.update(window,deltaTime);
            player.menuUpdate(window,deltaTime);
            score.displayHighScore(window, screenWidth);
            menu.customiseUpdate(window, screenWidth, deltaTime, gameState, sounds, background, player, building, helicopter, plane, score, isFullscreen, screenHeight);
            window.display();
        }

        // Settings state
        if(gameState == 3){
            background.update(window,deltaTime);
            player.menuUpdate(window,deltaTime);
            score.displayHighScore(window, screenWidth);
            menu.settingsUpdate(window, deltaTime, gameState, sounds, background, player, building, helicopter, plane, score, screenWidth, isFullscreen, screenHeight);
            window.display();
        }

        // Try again state
        if(gameState == 4){
            window.clear();
            background.update(window,deltaTime);
            building.update(window, deltaTime, score);
            plane.update(window,deltaTime);
            helicopter.update(window,deltaTime);
            score.tryUpdate(window,screenWidth,screenHeight);
            score.displayHighScore(window, screenWidth);
            menu.tryUpdate(window, screenWidth, deltaTime, gameState, sounds, background, player, building, helicopter, plane, score, isFullscreen, screenHeight);
            player.update(window, deltaTime, screenHeight, gameState, building, plane, helicopter, sounds);
            window.display();
        }

        if(gameState == 5){ // Developer mode for testing. Only entered manually
            background.update(window,deltaTime);
            player.testMode(window,deltaTime, helicopter, plane, building);
            helicopter.testMode(window, deltaTime);
            plane.testMode(window, deltaTime);
            building.testMode(window, deltaTime);
            window.display();
        }
        if(gameState == 6){ // Missing file mode telling user to re-install
            menu.errorScreen(window);
            window.display();
        }
    }
    return 0;
}

