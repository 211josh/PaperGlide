#ifndef SOUNDS_H
#define SOUNDS_H

#include <SFML/Audio.hpp>
#include <iostream>
#include "data.h"

class Sounds {
public:
	Sounds();

	void menuSound(Data& data);
	void startSound(Data& data);
	void pointSound(Data& data);
	void hitSound(Data& data);
	void gameoverSound(Data& data);
	
private:
	sf::Sound menu;
	sf::Sound start;
	sf::Sound point;
	sf::Sound hit;
	sf::Sound gameover;

	sf::SoundBuffer menuBuffer;
	sf::SoundBuffer startBuffer;
	sf::SoundBuffer pointBuffer;
	sf::SoundBuffer hitBuffer;
	sf::SoundBuffer gameoverBuffer;


};

#endif
