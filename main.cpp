#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>

int screenWidth = 1280;
int screenHeight = 720;

class Sounds { // Sound effects
public:
    Sounds(){
    if(!point.loadFromFile("sounds/point.ogg")){
        std::cout << "Could not load point sound file" << std::endl;
        }
    }

    void pointSound(){
        sound.setBuffer(point);
        sound.play();
        sound.setVolume(5);
        sound.setPitch(0.9f);
        }
private:
    sf::Sound sound;
    sf::SoundBuffer point; // Define point as sound
};

class Score { // Score
public:
    Score(){
    if(!font.loadFromFile("sprites/Font.ttf")){
        std::cout << "Could not load Score font";
        }
    text.setFont(font);
    text.setCharacterSize(300);
    text.setColor(sf::Color{255,255,255,200}); // r g b occupancy/255
    text.setOrigin(sf::Vector2f(0.0f,0.0f));
    text.setString(std::to_string(current_score));
    }
    void update(sf::RenderWindow& window){
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition((screenWidth - textBounds.width) / 2, 100); // Centres text based on text and screen width
        window.draw(text);
        }
    void addScore(Sounds& sound){
        current_score += 1;
        text.setString(std::to_string(current_score));
    //    sound.pointSound(); // Play score point sound
    }
private:
    sf::Font font;
    sf::Text text;
    int current_score = 0;

};

class Player { // Player sprite
public:
    Player(){
    if(!texture.loadFromFile("sprites/Player.png")){
        std::cout << "Could not load Player texture";
        }
    // Set texture, position and size of sprite
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(100,400));
    sprite.scale(sf::Vector2f(0.2,0.2));
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
     //   if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
     //       sprite.move(sf::Vector2f{-speed/40000,0});
     //   }
     //   if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
     //       sprite.move(sf::Vector2f{speed/40000,0});
     //   }
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
        sprite.setRotation((maxRotation * velocity.y)/terminalVel);
    }
};

class Plane { // Plane sprite
public:
    Plane(){
    if(!texture.loadFromFile("sprites/Plane.png")){
        std::cout << "Could not load Plane texture";
    }
    sprite.setTexture(texture);
    }

    void update(sf::RenderWindow& window, float deltaTime){
        if(spawnTimer >= spawnInterval){
            randomProp();
            spawnTimer = 0.0f + (static_cast<float>(std::rand() % -(800))/velocity.x); // Incorporate randomness into spawn interval
        }
        movement(deltaTime);
        spawnTimer += deltaTime;
        window.draw(sprite);
    }
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity{-1400.0f,0.0f}; // Initial velocity

    // Movement speed will slowly increase, so spawn interval is based on speed, i.e how long it takes to cross the screen
    float spawnTimer = 3.0f; // Spawn  timer values
    float spawnInterval = -(1700.0f/(velocity.x)); // Time between building reset

    void movement(float deltaTime){ // Movement across screen

        sprite.move(velocity*deltaTime);
    }

    void randomProp(){ // Random properties between different buildings
        sprite.setScale(sf::Vector2f(1,1));
        // First number is the random range 0 to x. The + shifts that range.
        float yPos = static_cast<float>(std::rand() % 400); // In SFML, 0,0 is the top left, screenWidth x screenHeight is the bottom right.
        float scale = static_cast<float>((std::rand() % 1) + 0.5f);
        sprite.scale(sf::Vector2f(scale,scale));
        sf::Vector2u textureSize = texture.getSize(); // Make origin centre of texture
        sprite.setOrigin(textureSize.x/2,textureSize.y/2);
        sprite.setPosition(sf::Vector2f(1280 + textureSize.x/2,yPos));

    }

};

class Helicopter { // Helicopter sprite
public:
    Helicopter() {
    if(!texture.loadFromFile("sprites/Helicopter.png")){
        std::cout <<"Could not load Helicopter texture";
        }

    sprite.setTexture(texture);
    sprite.setPosition(4000.0f,4000.0f);
    }

    void update(sf::RenderWindow& window, float deltaTime){
        if(spawnTimer >= spawnInterval){
            randomProp();
            spawnTimer = 0.0f + (static_cast<float>(std::rand() % -(800))/velocity.x); // Resets spawn timer, with some randomness deducted
        }
        movement(deltaTime);
        spawnTimer += deltaTime;
        window.draw(sprite);
    }
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity{-200.0f,0.0f};

    float spawnTimer = 0.0f;
    float spawnInterval = -(2000.0f/velocity.x);
    float heliTimer = 0;
    float initialyPos;

    void movement(float deltaTime){ // Movement across screen
        heliTimer += deltaTime;
        sprite.move(velocity*deltaTime);
        sf::Vector2f position = sprite.getPosition();
        sprite.setPosition(position.x,200*sin(heliTimer) + initialyPos); // y-position = (movement range) * sin(time) + initial y-pos
    }


    void randomProp(){ // Random properties between different helicopters
        sprite.setScale(sf::Vector2f(1,1));
        // First number is the random range 0 to x. The + shifts that range.
        float yPos = static_cast<float>((std::rand() % 720)); // In SFML, 0,0 is the top left, screenWidthxscreenHeight is the bottom right.
        float scale = static_cast<float>((std::rand() % 1)*1.5 +0.5);
        sprite.scale(sf::Vector2f(scale,scale));
        sf::Vector2u textureSize = texture.getSize();
        sprite.setOrigin(textureSize.x/2,textureSize.y/2);
        sprite.setPosition(sf::Vector2f(1280 + textureSize.x,yPos));
        sprite.setRotation(20.0f);
        initialyPos = yPos;

    }

};

class Building { // Building sprite
public:
    Building(){ // This section of Class runs when a new instance of Building is created. In our case, it's Building building; in main.
    // If we wanted 2 instances of buildings, we could create a Building building2; and add building2.update in the game loop
    if(!texture.loadFromFile("sprites/Building.png")){
        std::cout << "Could not load Building texture";
        }

    sprite.setTexture(texture);
    }

    // These are the functions which can be applied to our instance. They must be public to be directly called, or called by a public function,
    // as seen below
    void update(sf::RenderWindow& window, float deltaTime, Score& score, Sounds& sound){
        movement(deltaTime);
        spawnTimer += deltaTime; // Decide if a building spawns based on time passed from last one
        if(spawnTimer >= spawnInterval){
            randomProp();
            spawnTimer = 0.0f + (static_cast<float>(std::rand() % -(800))/velocity.x); // Resets spawn timer, with some randomness deducted
            score.addScore(sound); // Add score for every building (technically) passed
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
        float yPos = static_cast<float>((std::rand() % 180) + 400); // In SFML, 0,0 is the top left, screenWidthxscreenHeight is the bottom right.
        float scale = static_cast<float>((std::rand() % 3) +7);
        sprite.scale(sf::Vector2f(scale,scale));
        sprite.setOrigin(0.0f, 0.0f);
        sprite.setPosition(sf::Vector2f(1280,yPos));

    }

};

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
        score.update(window);
        player.update(window, deltaTime); // Continuously update player sprite in game loop
        building.update(window, deltaTime, score, sounds);
        helicopter.update(window, deltaTime);
        plane.update(window,deltaTime); // Layers of graphics depends on order of update
        window.display();
    }

    return 0;
}
