#ifndef SOUNDS_H_INCLUDED
#define SOUNDS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Sounds{
public:
    Sounds();
    void pointSound(); // Functions to play each sound
    void menuSound();
    void startSound();
    void hitSound();
    void gameOverSound();

    static int volume; // 1 to 10.

private:
    sf::Sound sound;
    sf::Sound gameOver;
    sf::Sound hit;

    sf::SoundBuffer point;
    sf::SoundBuffer menu;
    sf::SoundBuffer start;
    sf::SoundBuffer hitSoundFile;
    sf::SoundBuffer gameOverSoundFile; // A sound buffer for a sound is a texture for a sprite. The SoundBuffer is the actual sound file
};

#endif // SOUNDS_H_INCLUDED
