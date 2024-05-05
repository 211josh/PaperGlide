#ifndef HELICOPTER_H
#define HELICOPTER_H

#include "obstacle.h"

class Helicopter : public Obstacle {
public:
    Helicopter(Data& data);
    void update(sf::RenderWindow& window, Data& data, Player& player) override;
    void respawn(Data& data, sf::Sprite& sprite) override;

private:
    void loadTextures();
    float heliTimer;
    float initialyPos;
};

#endif
