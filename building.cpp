#include "building.h"

Building::Building(Background& background){ // This section of the class runs once - when a new instance of Building is created. In our case, it's Building building; in main.
    // Our game only has one building loaded at a time, i.e Building building;
    // If we wanted 2 instances of buildings, we could create a Building building2;

    // Variable declarations
    initialVel = {-750.0f,0.0f}; // Initial velocity of building
    velocity = initialVel;
    maxVel = {-1500.0,0.0f}; // Max velocity it can reach
    velDif = (velocity.x - maxVel.x); // Calculated for incremental increase of velocity based on score

    // Velocity is included in the spawn interval because the velocity increases
    spawnTimer = 0.0f; // Resets at spawnInterval, moving the building back to the right side of the screen
    spawnInterval = -(1600.0f/(velocity.x)); // Time between building position reset. -1600 was found through trial and error

    rectFirstSprite = {0,0,512,2048}; // For animation. First texture is (0,0) to (550,300)

    Style = background.Style;

    //

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
    if(!textureSpace.loadFromFile("sprites/buildingSpace.png")){
        std::cout << "Could not load Building (Space) texture";
        }

    if(Style == 0){
        themeNormal();
        }
    if(Style == 1){
        themeNormal();
        }
    if(Style == 2){
        themeSunset();
        }
    if(Style == 3){
        themeApoc();
        }
    if(Style == 4){
        themeSpace();
        }
}

// The update function runs once every game loop
void Building::update(sf::RenderWindow& window, float deltaTime, Score& score){
    movement(deltaTime); // Function below which handles the movement of building across screen
    spawnTimer += deltaTime; // Decide if a building spawns based on time passed from last one
    if(spawnTimer >= spawnInterval){
        randomProp(score); // Function below which spawns new building with different, randomly selected properties
    }
    animation(deltaTime);
    window.draw(sprite);
}

void Building::movement(float deltaTime){
    sprite.move(velocity*deltaTime);
    } // deltaTime is the difference in time between each run of our game loop. distance travelled = velocity * time

void Building::randomProp(Score& score){ // Random properties between different buildings
    spawnTimer = 0.0f + (static_cast<float>(std::rand() % -(800))/velocity.x); // Resets spawn timer, with some randomness deducted

    if(Style == 4){
        sprite.setScale(sf::Vector2f(0.08,0.08));
    } else{
        sprite.setScale(sf::Vector2f(0.0625,0.0625));
    }

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
    Style = 0;
    }

void Building::themeSunset(){
    sprite.setTexture(textureSunset);
    Style = 2;
    std::cout << "TEST" << std::endl;
    }

void Building::themeApoc(){
    sprite.setTexture(textureApoc);
    Style = 3;
    }

void Building::themeSpace(){
    sprite.setTexture(textureSpace);
    Style = 4;
}

void Building::animation(float deltaTime){
    animationTimer += deltaTime;
    if(animationTimer > 0.1){
        if(rectFirstSprite.left == 1536){ // if it's on the last one, reset to beginning
            rectFirstSprite.left = 0;
        } else{
        rectFirstSprite.left += 512; // Sprite texture shifts 300 to the right
        }
    sprite.setTextureRect(rectFirstSprite);
    animationTimer = 0;
    }
    }

void Building::testMode(sf::RenderWindow& window, float deltaTime){
    sprite.setPosition({500,300});
    animation(deltaTime);
    window.draw(sprite);
    }
