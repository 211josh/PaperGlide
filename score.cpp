#include "score.h"

int Score::current_score = 0;
float Score::velRange = 180; // velRange = score for sprites to hit max velocities

Score::Score(){
if(!font.loadFromFile("sprites/Font.ttf")){
    std::cout << "Could not load Score font";
    }
    // Score display properties
    text.setFont(font);
    text.setCharacterSize(300);
    text.setColor(sf::Color{200,223,255,200}); // r g b occupancy/255
    text.setOrigin(sf::Vector2f(0.0f,0.0f));
    text.setString(std::to_string(current_score));
    }

void Score::update(sf::RenderWindow& window, int screenWidth, int screenHeight){
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition((screenWidth - textBounds.width) / 2, 100); // Centres text based on text and screen width
    window.draw(text);
    }


void Score::addScore(Sounds& sound, Background& background, Helicopter& helicopter, Plane& plane, Building& building){
    current_score += 1;
    text.setString(std::to_string(current_score));
        sound.pointSound(); // Play score point sound

    // Increase in score increases velocities of sprites
    if(current_score < velRange){
        background.increaseVel(velRange);
        helicopter.increaseVel(velRange);
        plane.increaseVel(velRange);
        building.increaseVel(velRange);
        }
    }
