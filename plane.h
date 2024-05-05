#ifndef PLANE_H
#define PLANE_H

#include "obstacle.h"

class Plane : public Obstacle {
public:
    Plane(Data& data);
    
private:
    void loadTextures();
};

#endif
