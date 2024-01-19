#ifndef SOUNDS_H_INCLUDED
#define SOUNDS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Sounds{
public:
    Sounds();
    void pointSound();
    void menuSound();
    void startSound();

private:
    sf::Sound sound;
    sf::SoundBuffer point;
    sf::SoundBuffer menu;
    sf::SoundBuffer start;
};

#endif // SOUNDS_H_INCLUDED
