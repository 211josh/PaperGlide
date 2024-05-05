#include "helicopter.h"

Helicopter::Helicopter(Data& data) {

	loadTextures();
	setTheme(data);
	sprite.setRotation(20.0f);

	respawn(data, sprite);

	initialVel = { -150,0 };
	maximumVel = { -400,0 };
	velDif = maximumVel - initialVel;

	respawnTrigger = -350;

	xLower = 1400;
	xOffset = 400;

	yLower = 50;
	yOffset = 490;

	initialScale = 1;
	scaleLower = 0.45;
	scaleOffset = 0.08;

	spriteSize = { 550,300 };
	rectFirstSprite = { 0,0, 550, 300 };
	spriteCount = 4;
	animationTimer = 0;
	animationInterval = 0.05;
}

void Helicopter::update(sf::RenderWindow& window, Data& data, Player& player) {
	movement(data, sprite, 1);
	sf::Vector2f pos = sprite.getPosition();
	heliTimer += data.deltaTime;

	sprite.setPosition(pos.x, 200 * sin(heliTimer) + initialyPos); // vertical movement

	if (pos.x < respawnTrigger) {
		respawn(data, sprite);
	}

	checkCollision(data, player.sprite);

	animation(data, sprite);

	window.draw(sprite);
}

void Helicopter::respawn(Data& data, sf::Sprite& sprite) {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> disX(0, xOffset);
	float x = xLower + disX(gen);

	std::uniform_real_distribution<float> disY(0, yOffset);
	float y = yLower + disY(gen);

	std::uniform_real_distribution<float> disScale(0, scaleOffset);
	float scale = scaleLower + disScale(gen);

	std::cout << scale << std::endl;

	sprite.setScale({ initialScale, initialScale });
	sprite.scale({ scale, scale });

	sprite.setPosition({ x,y });

	initialyPos = y;
}

void Helicopter::loadTextures() {
	if (!Collision::CreateTextureAndBitmask(tNormal, "sprites/helicopters/helicopterNormal.png")) {
		std::cout << "Could not load helicopter Normal texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tPixel, "sprites/helicopters/helicopterPixel.png")) {
		std::cout << "Could not load helicopter Pixel texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tSunset, "sprites/helicopters/helicopterSunset.png")) {
		std::cout << "Could not load helicopter Sunset texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tApoc, "sprites/helicopters/helicopterApoc.png")) {
		std::cout << "Could not load helicopter Apoc texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tSpace, "sprites/helicopters/helicopterSpace.png")) {
		std::cout << "Could not load helicopter Space texture" << std::endl;
	}
}