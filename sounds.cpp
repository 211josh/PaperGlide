#include "sounds.h"

int Sounds::volume = 10;

Sounds::Sounds(){
if(!point.loadFromFile("sounds/point.ogg")){
    std::cout << "Could not load point Sound file" << std::endl;
    }
if(!menu.loadFromFile("sounds/menu.ogg")){
    std::cout << "Could not load Menu sound file " << std::endl;
    }
if(!start.loadFromFile("sounds/start.ogg")){
    std::cout << "Could not load Start sound file" << std::endl;
    }
if(!hitSoundFile.loadFromFile("sounds/hit.ogg")){
    std::cout << "Could not load hit sound file" << std::endl;
    }
if(!gameOverSoundFile.loadFromFile("sounds/gameOver.ogg")){
    std::cout << "Could not load Game Over sound file" << std::endl;
    }

    gameOver.setBuffer(gameOverSoundFile);
    gameOver.setPitch(1.0f);

    hit.setBuffer(hitSoundFile);
    hit.setPitch(1.0f);
}

void Sounds::pointSound(){ // Sound when score point is given
    sound.setBuffer(point);
    sound.setVolume(0.75*volume);
    sound.setPitch(0.9f);
    sound.play();
    }

void Sounds::menuSound(){ // Sound for swapping options on menu
    sound.setBuffer(menu);
    sound.setVolume(2*volume);
    sound.setPitch(1.0f);
    sound.play();
    }

void Sounds::startSound(){ // Sound for starting game
    sound.setBuffer(start);
    sound.setVolume(4*volume);
    sound.setPitch(1.0f);
    sound.play();
    }

void Sounds::hitSound(){
    hit.setVolume(2*volume);
    hit.play();
    }

void Sounds::gameOverSound(){
    gameOver.setVolume(10*volume);
    gameOver.play();
    }
