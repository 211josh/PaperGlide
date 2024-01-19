#include "sounds.h"

Sounds::Sounds(){
if(!point.loadFromFile("sounds/point.ogg")){
    std::cout << "Could not load point sound file" << std::endl;
    }
if(!menu.loadFromFile("sounds/menu.ogg")){
    std::cout << "Could not load menu sound file " << std::endl;
    }
if(!start.loadFromFile("sounds/start.ogg")){
    std::cout << "Could not load start sound file" << std::endl;
    }
}

void Sounds::pointSound(){ // Sound when score point is given
    sound.setBuffer(point);
    sound.setVolume(5);
    sound.setPitch(0.9f);
    sound.play();
    }

void Sounds::menuSound(){ // Sound for swapping options on menu
    sound.setBuffer(menu);
    sound.setVolume(20);
    sound.setPitch(1.0f);
    sound.play();
    }

void Sounds::startSound(){ // Sound for starting game
    sound.setBuffer(start);
    sound.setVolume(20);
    sound.setPitch(1.0f);
    sound.play();
    }
