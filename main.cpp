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

int screenWidth = 1280;
int screenHeight = 720;

int main()
{
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Paper Glide");
    sf::Clock clock;

    std::srand(static_cast<unsigned>(std::time(nullptr))); // Random gen seed

    Sounds sounds;
    Player player;
    Building building;
    Plane plane;
    Helicopter helicopter;
    Score score;
    Background background;


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
        background.update(window, deltaTime);
        score.update(window,screenWidth,screenHeight);
        player.update(window, deltaTime); // Continuously update player sprite in game loop
        building.update(window, deltaTime, score, sounds);
        helicopter.update(window, deltaTime);
        plane.update(window, deltaTime); // Layers of graphics depends on order of update
        window.display();
    }

    return 0;
}
