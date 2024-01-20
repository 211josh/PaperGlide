#include "building.h"

sf::Vector2f Building::initialVel{-750.0f,0.0f}; // Initial velocity of building
sf::Vector2f Building::velocity = Building::initialVel;
sf::Vector2f Building::maxVel{-1500.0,0.0f}; // Max velocity it can reach
float Building::velDif = (velocity.x - maxVel.x); // Calculated for incremental increase of velocity based on score

// Velocity is included in the spawn interval because the velocity increases
float Building::spawnTimer = 0.0f; // Resets at spawnInterval, moving the building back to the right side of the screen
float Building::spawnInterval = -(1600.0f/(velocity.x)); // Time between building position reset. -1600 was found through trial and error

Building::Building(){ // This section of the class runs once - when a new instance of Building is created. In our case, it's Building building; in main.
    // Our game only has one building loaded at a time, i.e Building building;
    // If we wanted 2 instances of buildings, we could create a Building building2;
if(!texture.loadFromFile("sprites/Building.png")){
    std::cout << "Could not load Building texture";
    }

sprite.setTexture(texture);
}

// The update function runs once every game loop
void Building::update(sf::RenderWindow& window, float deltaTime){
    movement(deltaTime); // Function below which handles the movement of building across screen
    spawnTimer += deltaTime; // Decide if a building spawns based on time passed from last one
    if(spawnTimer >= spawnInterval){
        randomProp(); // Function below which spawns new building with different, randomly selected properties
    }
    window.draw(sprite);
}

void Building::movement(float deltaTime){
    sprite.move(velocity*deltaTime);
    } // deltaTime is the difference in time between each run of our game loop. distance travelled = velocity * time

void Building::randomProp(){ // Random properties between different buildings
    spawnTimer = 0.0f + (static_cast<float>(std::rand() % -(800))/velocity.x); // Resets spawn timer, with some randomness deducted
    sprite.setScale(sf::Vector2f(1,1));
    // First number is the random range 0 to x. The + shifts that range.
    float yPos = static_cast<float>((std::rand() % 180) + 400);
    float scale = static_cast<float>((std::rand() % 3) +7);

    sprite.scale(sf::Vector2f(scale,scale));
    sprite.setOrigin(0.0f, 0.0f);
    sprite.setPosition(sf::Vector2f(1280,yPos));

    spawnInterval = -(1600.0f/(velocity.x));
    }

void Building::increaseVel(float velRange){
    velocity.x -= velDif/velRange;
    }

void Building::resetGame(){
    velocity = initialVel;
    randomProp();
    }
