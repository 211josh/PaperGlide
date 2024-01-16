#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "sounds.h"

class Score{
public:
    Score();
    void update(sf::RenderWindow& window, int screenWidth, int screenHeight);
    void addScore(Sounds& sound);

private:
    sf::Font font;
    sf::Text text;
    static int current_score;
};

#endif // SCORE_H_INCLUDED
