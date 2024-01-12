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

    float speed = -2500.0f; // Speed of movements. Works well at gravity x-2
    float gravity = speed * -0.5f; // Gravity strength
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

class Building { // Building sprite
public:
    Building(){ // This section of Class runs when a new instance of Building is created. In our case, it's Building building; in main.
    // If we wanted 2 instances of buildings, we could create a Building building2; and add building2.update in the game loop
    if(!texture.loadFromFile("sprites/Building.png")){
        std::cout << "Could not load Building texture";
        }

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    sprite.setTexture(texture);
    }

    // These are the functions which can be applied to our instance. They must be public to be directly called, or called by a public function,
    // as seen below
    void update(sf::RenderWindow& window, float deltaTime){
        movement(deltaTime);
        spawnTimer += deltaTime; // Decide if a building spawns based on time passed from last one
        if(spawnTimer >= spawnInterval){
            randomProp();
            spawnTimer = 0.0f; // Resets spawn timer
        }
        window.draw(sprite);
    }


private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity{-1000.0f,0.0f}; // Initial velocity

    // Movement speed will slowly increase, so spawn interval is based on speed, i.e how long it takes to cross the screen
    float spawnTimer = 0.0f; // Spawn  timer values
    float spawnInterval = -(1600.0f/(velocity.x)); // Time between building reset

    void movement(float deltaTime){ // Movement across screen

        sprite.move(velocity*deltaTime);
    }

    void randomProp(){ // Random properties between different buildings

        sprite.setScale(sf::Vector2f(1,1));
        // First number is the random range 0 to x. The + shifts that range.
        float yPos = static_cast<float>((std::rand() % 140) + 440); // In SFML, 0,0 is the top left, screenWidthxscreenHeight is the bottom right.
        float scale = static_cast<float>((std::rand() % 4) +4);
        sprite.scale(sf::Vector2f(scale,scale));
        sprite.setOrigin(0.0f, 0.0f);
        sprite.setPosition(sf::Vector2f(1280,yPos));

    }

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Paper Glide");
    sf::Clock clock;

    Player player;
    Building building;

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
        building.update(window, deltaTime);
        window.display();
    }

    return 0;
}
