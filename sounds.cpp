#include "sounds.h"

Sounds::Sounds(){
if(!point.loadFromFile("sounds/point.ogg")){
    std::cout << "Could not load point sound file" << std::endl;
    }
}

void Sounds::pointSound(){
    sound.setBuffer(point);
    sound.play();
    sound.setVolume(5);
    sound.setPitch(0.9f);
    }
