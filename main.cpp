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

int screenWidth = 1280;
int screenHeight = 720;
int gameState = 0; // 0 = main menu, 1 = gameplay, 2 = settings and 3 = try again screen
float timePassed = 0; // TEMPORARY METHOD OF ADDING SCORE

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Random gen seed

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Paper Glide");
    sf::Clock clock;

    Sounds sounds;
    Background background;
    Player player;
    Building building;
    Plane plane;
    Helicopter helicopter;
    Score score;
    Menu menu;


    while (window.isOpen()) // Game loop
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds(); // Change in time since last frame

        window.clear(sf::Color{229,255,255,255}); // Background colour
        // Update all mechanics here

        // Menu state
        if(gameState == 0){
            background.update(window,deltaTime);
            player.menuUpdate(window,deltaTime);
            menu.menuUpdate(window, screenWidth, deltaTime, gameState, sounds);
            window.display();
        }

        // Play state
        if(gameState == 1){
            background.update(window, deltaTime);
            score.update(window,screenWidth,screenHeight);
            player.update(window, deltaTime); // Continuously update player sprite in game loop
            building.update(window, deltaTime);
            helicopter.update(window, deltaTime);
            plane.update(window, deltaTime); // Layers of graphics depends on order of update

            timePassed += deltaTime;
       //     std::cout << timePassed << std::endl;  // TEMPORARY METHOD OF ADDING SCORE
            if(timePassed > 1.0f){
                score.addScore(sounds, background, helicopter, plane, building); // TEMPORARY METHOD OF ADDING SCORE
                timePassed = 0.0f;
            }

            window.display();
        }
    }

    return 0;
}
