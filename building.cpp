#include "building.h"

sf::Sprite Building::sprite;

sf::Vector2f Building::initialVel{-750.0f,0.0f}; // Initial velocity of building
sf::Vector2f Building::velocity = Building::initialVel;
sf::Vector2f Building::maxVel{-1500.0,0.0f}; // Max velocity it can reach
float Building::velDif = (velocity.x - maxVel.x); // Calculated for incremental increase of velocity based on score

// Velocity is included in the spawn interval because the velocity increases
float Building::spawnTimer = 0.0f; // Resets at spawnInterval, moving the building back to the right side of the screen
float Building::spawnInterval = -(1600.0f/(velocity.x)); // Time between building position reset. -1600 was found through trial and error

int Building::Style;

Building::Building(){ // This section of the class runs once - when a new instance of Building is created. In our case, it's Building building; in main.
    // Our game only has one building loaded at a time, i.e Building building;
    // If we wanted 2 instances of buildings, we could create a Building building2;

    Building::Style = Background::Style;

    if(!textureNormal.loadFromFile("sprites/Building.png")){
        std::cout << "Could not load Building (Normal) texture";
        }
    if(!textureMedival.loadFromFile("sprites/buildingMedival.png")){
        std::cout << "Could not load Building (Medival) texture";
        }
    if(!textureSunset.loadFromFile("sprites/buildingSunset.png")){
        std::cout << "Could not load Building (Sunset) texture";
        }
    if(!textureApoc.loadFromFile("sprites/buildingApoc.png")){
        std::cout << "Could not load Building (Apoc) texture";
        }

    if(Style == 0){
        themeNormal();
        }
    if(Style == 1){
        themeMedival();
        }
    if(Style == 2){
        themeSunset();
        }
    if(Style == 3){
        themeApoc();
        }
    if(Style == 4){
        themeNormal();
        }


}

// The update function runs once every game loop
void Building::update(sf::RenderWindow& window, float deltaTime, Score& score){
    movement(deltaTime); // Function below which handles the movement of building across screen
    spawnTimer += deltaTime; // Decide if a building spawns based on time passed from last one
    if(spawnTimer >= spawnInterval){
        randomProp(score); // Function below which spawns new building with different, randomly selected properties
    }
    window.draw(sprite);
}

void Building::movement(float deltaTime){
    sprite.move(velocity*deltaTime);
    } // deltaTime is the difference in time between each run of our game loop. distance travelled = velocity * time

void Building::randomProp(Score& score){ // Random properties between different buildings
    spawnTimer = 0.0f + (static_cast<float>(std::rand() % -(800))/velocity.x); // Resets spawn timer, with some randomness deducted
    sprite.setScale(sf::Vector2f(1,1));
    // First number is the random range 0 to x. The + shifts that range.
    float yPos = static_cast<float>((std::rand() % 180) + 400);
    float scale = static_cast<float>((std::rand() % 3) +7);

    sprite.scale(sf::Vector2f(scale,scale));
    sprite.setOrigin(0.0f, 0.0f);
    sprite.setPosition(sf::Vector2f(1280,yPos));

    spawnInterval = -(1600.0f/(velocity.x));

    score.pointAdded = 0; // Allows points to be given again
    }

void Building::increaseVel(float velRange){
    velocity.x -= velDif/velRange;
    }

void Building::resetGame(Score& score){
    velocity = initialVel;
    randomProp(score);
    }

sf::Vector2f Building::getPos(){
    return sprite.getPosition();
    }

void Building::themeNormal(){
    sprite.setTexture(textureNormal);
    }

void Building::themeMedival(){
    sprite.setTexture(textureMedival);
    }

void Building::themeSunset(){
    sprite.setTexture(textureSunset);
    }

void Building::themeApoc(){
    sprite.setTexture(textureApoc);
    }





