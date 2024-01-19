#include "building.h"

sf::Texture texture;
sf::Sprite sprite;

sf::Vector2f Building::velocity{-750.0f,0.0f}; // Initial velocity
sf::Vector2f Building::maxVel{-1500.0,0.0f};
float Building::velDif = (velocity.x - maxVel.x);

// Movement speed will slowly increase, so spawn interval is based on speed, i.e how long it takes to cross the screen
float Building::spawnTimer = 0.0f; // Spawn  timer values
float Building::spawnInterval = -(1600.0f/(velocity.x)); // Time between building reset. -1600 was found through trial and error

Building::Building(){ // This section of Class runs ONCE when a new instance of Building is created. In our case, it's Building building; in main.
// If we wanted 2 instances of buildings, we could create a Building building2; and add building2.update in the game loop
if(!texture.loadFromFile("sprites/Building.png")){
    std::cout << "Could not load Building texture";
    }

sprite.setTexture(texture);
}

// These are the functions which can be applied to our instance.
// In particular, the update function contains what we wish to happen to our sprite in each game loop (i.e continuously applied)
void Building::update(sf::RenderWindow& window, float deltaTime){
    movement(deltaTime);
    spawnTimer += deltaTime; // Decide if a building spawns based on time passed from last one
    if(spawnTimer >= spawnInterval){
        randomProp();
        spawnTimer = 0.0f + (static_cast<float>(std::rand() % -(800))/velocity.x); // Resets spawn timer, with some randomness deducted
    }
    window.draw(sprite);
}

void Building::movement(float deltaTime){ // Movement across screen

    sprite.move(velocity*deltaTime);
    } // deltaTime is the difference in time between each run of our game loop. distance travelled = velocity * time

void Building::randomProp(){ // Random properties between different buildings
    sprite.setScale(sf::Vector2f(1,1));
    // First number is the random range 0 to x. The + shifts that range.
    float yPos = static_cast<float>((std::rand() % 180) + 400); // In SFML, 0,0 is the top left, screenWidthxscreenHeight is the bottom right.
    float scale = static_cast<float>((std::rand() % 3) +7);
    sprite.scale(sf::Vector2f(scale,scale));
    sprite.setOrigin(0.0f, 0.0f);
    sprite.setPosition(sf::Vector2f(1280,yPos));
    spawnInterval = -(1600.0f/(velocity.x));
    }

void Building::increaseVel(float velRange){
    velocity.x -= velDif/velRange;
 //   std::cout << velocity.x << std::endl;
    }
