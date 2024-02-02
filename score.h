#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "sounds.h"
#include "background.h"
#include "helicopter.h"
#include "plane.h"
#include "building.h"

class Building; // Forward declaration of Building class to prevent circular dependency

class Score{
public:
    Score();
    void update(sf::RenderWindow& window, int screenWidth, int screenHeight, Sounds& sound, Background& background, Helicopter& helicopter, Plane& plane, Building& building, float deltaTime);
    void tryUpdate(sf::RenderWindow& window, int screenWidth, int screenHeight);

    void addScore(Sounds& sound, Background& background, Helicopter& helicopter, Plane& plane, Building& building);
    void checkScore(Sounds& sound, Background& background, Helicopter& helicopter, Plane& plane, Building& building, float deltaTime);

    static int current_score;
    static bool pointAdded;
    static float velRange; // The current score determines the velocity of sprites. The range depicts what score you must reach for their max vels


private:
    sf::Font font;
    sf::Text text;
    sf::Text showScore;
};

#endif // SCORE_H_INCLUDED
