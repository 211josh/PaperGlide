#ifndef BUILDING_H
#define BUILDING_H

#include "obstacle.h"
#include "sounds.h"


class Building : public Obstacle {
public:
    Building(Data& data);
    void update(sf::RenderWindow& window, Data& data, Player& player, Sounds& sounds);
    void respawn(Data& data, sf::Sprite& sprite) override;
private:
    void loadTextures();

    bool scoreIncreased; // 1 if score has been increased since building has respawned
};

#endif
