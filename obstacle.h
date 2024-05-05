#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "Collision.hpp"
#include "data.h"
#include "player.h"

#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle {
public:
	virtual void update(sf::RenderWindow& window, Data& data, Player& player);
	virtual void setTheme(Data& data);
	virtual void respawn(Data& data, sf::Sprite& sprite);

	sf::Sprite sprite;

protected: // private to all except derived classes
	void movement(Data& data, sf::Sprite& sprite, float coefficient);
	void animation(Data& data, sf::Sprite& sprite);
	void checkCollision(Data& data, sf::Sprite& sprite);

	sf::Texture tNormal;
	sf::Texture tPixel;
	sf::Texture tSunset;
	sf::Texture tApoc;
	sf::Texture tSpace;

	sf::Vector2f initialVel;
	sf::Vector2f maximumVel;
	sf::Vector2f velDif;

	float respawnTrigger;

	float xLower;
	float xOffset;

	float yLower;
	float yOffset;

	float initialScale;
	float scaleLower;
	float scaleOffset;

	// Animation
	sf::Vector2f spriteSize;
	sf::IntRect rectFirstSprite;
	int spriteCount;
	float animationTimer;
	float animationInterval;
};

#endif