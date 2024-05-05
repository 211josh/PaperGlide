#include <SFML/Graphics.hpp>
#include <iostream>
#include "Collision.hpp"

#include "data.h"
#include "sounds.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
	Player(Data& data);
	void update(sf::RenderWindow& window, Data& data, Sounds& sounds);
	void menuFloat(sf::RenderWindow& window, Data& data);
	void respawn();
	void setTheme(Data& data);

	sf::Sprite sprite;

private:
	void handleInput(Data& data);

	void loadTextures();

	float playerTimer;
	bool hitsoundPlayed;

	float speed = -2500;
	sf::Vector2f velocity;
	float gravity;
	float terminalVel;
	float maxRotation;

	sf::Sprite deathScreen;
	sf::Sprite upArrow;

	sf::Texture tNormal;
	sf::Texture tPixel;
	sf::Texture tGold;
	sf::Texture tOrigami;
	sf::Texture tKing;
	sf::Texture tdeathScreen;

	sf::Texture tupArrow;

	sf::Font font;
	sf::Text holdSpace;
};

#endif 