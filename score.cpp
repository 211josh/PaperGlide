#include "score.h"

int Score::current_score = 0;
float Score::score_timer = 0; // Makes sure only 1 score is added per building passed
float Score::velRange = 180; // velRange = score for sprites to hit max velocities

Score::Score(){
if(!font.loadFromFile("sprites/Font.ttf")){
    std::cout << "Could not load Score font";
    }
    // Score display properties
    text.setFont(font); // Score behind screen
    showScore.setFont(font); // Score on try again screen

    text.setCharacterSize(300);
    showScore.setCharacterSize(150);

    text.setColor(sf::Color{200,223,255,200}); // r g b occupancy/255
    showScore.setColor(sf::Color{200,223,255,200});

    text.setOrigin(sf::Vector2f(0.0f,0.0f));
    showScore.setOrigin(sf::Vector2f(0.0f,0.0f));

    text.setString(std::to_string(current_score));
    }

void Score::update(sf::RenderWindow& window, int screenWidth, int screenHeight, Sounds& sound, Background& background, Helicopter& helicopter, Plane& plane, Building& building, float deltaTime){
    text.setString(std::to_string(current_score));
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition((screenWidth - textBounds.width) / 2, 100); // Centres text based on text and screen width
    checkScore(sound, background, helicopter, plane, building, deltaTime);
    window.draw(text);
    }


void Score::addScore(Sounds& sound, Background& background, Helicopter& helicopter, Plane& plane, Building& building){
    current_score += 1;
    sound.pointSound(); // Play score point sound

    // Increase in score increases velocities of sprites
    if(current_score < velRange){
        background.increaseVel(velRange);
        helicopter.increaseVel(velRange);
        plane.increaseVel(velRange);
        building.increaseVel(velRange);
        }
    }

void Score::tryUpdate(sf::RenderWindow& window, int screenWidth, int screenHeight){

    showScore.setString("Score: " + std::to_string(current_score));
    sf::FloatRect showScoreBounds = showScore.getLocalBounds();
    showScore.setPosition((screenWidth - showScoreBounds.width) / 2, 100); // Centres text based on text and screen width
    window.draw(showScore);
    }

void Score::checkScore(Sounds& sound, Background& background, Helicopter& helicopter, Plane& plane, Building& building, float deltaTime){ // Check position of building to see if point can be added
    sf::Vector2f position = building.getPos();
    score_timer += deltaTime;
    if(position.x < 100 && score_timer > 2.0){
        addScore(sound,background,helicopter,plane,building);
        score_timer = 0;
        }
    }
