#include <SFML/Graphics.hpp>

#include "data.h"
#include "menu.h"
#include "background.h"
#include "obstacle.h"
#include "player.h"
#include "building.h"
#include "plane.h"
#include "helicopter.h"

int main()
{
    sf::Clock clock;
    Data data;
    sf::RenderWindow window;
    data.changeFullscreen(window, data.isFullscreen); // load window

    Menu menu(data);
    Background background(data);
    Sounds sounds;
    Player player(data);
    Building building(data);
    Plane plane(data);
    Helicopter helicopter(data);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.setVerticalSyncEnabled(true);

        sf::Image icon;
        if (!icon.loadFromFile("sprites/icon.png")) {
            std::cout << "Could not load icon texture" << std::endl;
        }
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        data.deltaTime = clock.restart().asSeconds();

        window.clear();

        switch (data.gameState) {
        case 0: // menu
            background.update(window, data);
            player.menuFloat(window, data);
            menu.update(window, data, sounds);
            break;
        case 1: // play
            background.update(window, data);
            building.update(window, data, player, sounds);
            helicopter.update(window, data, player);
            plane.update(window, data, player);
            menu.playUpdate(window, data, sounds);
            player.update(window, data, sounds);
            break;
        case 2: // customise
            background.update(window, data);
            player.menuFloat(window, data);
            menu.update(window, data, sounds);

            player.setTheme(data);
            background.setTheme(data);
            building.setTheme(data);
            helicopter.setTheme(data);
            plane.setTheme(data);

            break;
        case 3: // settings
            background.update(window, data);
            player.menuFloat(window, data);
            menu.update(window, data, sounds);
            break;
        case 4: // try again menu
            background.update(window, data);
            building.update(window, data, player, sounds);
            helicopter.update(window, data, player);
            plane.update(window, data, player);
            menu.update(window, data, sounds);
            player.update(window, data, sounds); // otherwise it dissapears
            break;
        }

        if (data.gameReset) { // set to true when press 'Retry' or 'Menu' on Try Again screen

            player.respawn();
            background.respawn(data); // resets sun & day
            helicopter.respawn(data, helicopter.sprite);
            building.respawn(data, building.sprite);
            plane.respawn(data, plane.sprite);

            data.collided = 0;
            data.dead = 0;
            data.gameReset = 0;
            data.currentScore = 0;
        }
        
        window.display();
    }

    return 0;
}