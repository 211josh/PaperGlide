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

        // Menu state
        if(gameState == 0){ // Order of update dictates layer
            background.update(window,deltaTime);
            menu.menuUpdate(window, screenWidth, deltaTime, gameState, sounds, background, player, building, helicopter, plane, score);
            player.menuUpdate(window,deltaTime);
            window.display();
        }

        // Play state
        if(gameState == 1){
            background.update(window, deltaTime);
            score.update(window,screenWidth, screenHeight, sounds, background, helicopter, plane, building, deltaTime);
            building.update(window, deltaTime, score);
            helicopter.update(window, deltaTime);
            plane.update(window, deltaTime); // Layers of graphics depends on order of update
            player.update(window, deltaTime, screenHeight, gameState, building, plane, helicopter, sounds);
            window.display();
        }

        // Try again state
        if(gameState == 3){
            window.clear();
            background.update(window, deltaTime);
            building.update(window, deltaTime, score);
            plane.update(window,deltaTime);
            helicopter.update(window,deltaTime);
            score.tryUpdate(window,screenWidth,screenHeight);
            menu.tryUpdate(window, screenWidth, deltaTime, gameState, sounds, background, player, building, helicopter, plane, Score::current_score, score);
            player.update(window, deltaTime, screenHeight, gameState, building, plane, helicopter, sounds);
            window.display();
        }
    }
    return 0;
}
