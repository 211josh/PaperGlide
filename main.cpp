#include <SFML/Graphics.hpp>
#include <iostream>

class Player { // Player sprite
public:
    Player(){
    if(!texture.loadFromFile("sprites/Player.png")){
        std::cout << "Could not load Player texture";
        }
    // Set texture, position and size of sprite
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(100,400));
    sprite.scale(sf::Vector2f(2,2));
    // Set origin point to centre of sprite
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    }

    void update(sf::RenderWindow& window, float deltaTime) { // Continuously update the sprite inside the window
        handleInput(deltaTime);
        applyGravity(deltaTime);
        window.draw(sprite);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;

    float speed = -2000.0f; // Speed of movements
    float gravity = 1000.0f; // Gravity strength
    float terminalVel = 1000.0f; // Terminal velocity
    float maxRotation = 70.0f; // Max rotation of sprite [-max,max]

    sf::Vector2f velocity{0.0f,0.0f}; // Initial velocity

    void handleInput(float deltaTime) { // Control player with WASD
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            velocity.y += speed * deltaTime;
        }
    }

    void applyGravity(float deltaTime) { // Gravity on player
        velocity.y += gravity * deltaTime;
        if(velocity.y > terminalVel){
            velocity.y = terminalVel;
        }
        if(velocity.y < -terminalVel){
            velocity.y = -terminalVel;
        }
        sprite.move(velocity*deltaTime);
        // Rotation
        sprite.setRotation(((maxRotation * velocity.y)/terminalVel)+3.0f);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Minigame");
    sf::Clock clock;

    Player player;

    while (window.isOpen()) // Game loop
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds(); // Change in time since last frame

        window.clear();
        // Update all mechanics here
        player.update(window, deltaTime); // Continuously update player sprite in game loop

        window.display();
    }

    return 0;
}
