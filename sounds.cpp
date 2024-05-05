#include "sounds.h"

Sounds::Sounds() {
    if (!menuBuffer.loadFromFile("sounds/menu.ogg")) {
        std::cout << "Could not load Menu sound file " << std::endl;
    }
    if (!startBuffer.loadFromFile("sounds/start.ogg")) {
        std::cout << "Could not load Start sound file" << std::endl;
    }
    if (!pointBuffer.loadFromFile("sounds/point.ogg")) {
        std::cout << "Could not load point Sound file" << std::endl;
    }
    if (!hitBuffer.loadFromFile("sounds/hit.ogg")) {
        std::cout << "Could not load hit sound file" << std::endl;
    }
    if (!gameoverBuffer.loadFromFile("sounds/gameover.ogg")) {
        std::cout << "Could not load Game Over sound file" << std::endl;
    }
    // Buffer
    menu.setBuffer(menuBuffer);
    start.setBuffer(startBuffer);
    point.setBuffer(pointBuffer);
    hit.setBuffer(hitBuffer);
    gameover.setBuffer(gameoverBuffer);

    // Pitch
    menu.setPitch(1);
    start.setPitch(1);
    point.setPitch(0.9);
    hit.setPitch(1);
    gameover.setPitch(1);
}

void Sounds::menuSound(Data& data) {
    menu.setVolume(2 * data.volume);
    menu.play();
}

void Sounds::startSound(Data& data) {
    start.setVolume(4 * data.volume);
    start.play();
}

void Sounds::pointSound(Data& data) {
    point.setVolume(0.75 * data.volume);
    point.play();
}

void Sounds::hitSound(Data& data) {
    hit.setVolume(2 * data.volume);
    hit.play();
}

void Sounds::gameoverSound(Data& data) {
    gameover.setVolume(10 * data.volume);
    gameover.play();
}