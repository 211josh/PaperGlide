#include "building.h"

Building::Building(Data& data) {

	loadTextures();
	setTheme(data);

	respawn(data, sprite);

	initialVel = { -750,0 };
	maximumVel = { -1500,0 };
	velDif = maximumVel - initialVel;

	respawnTrigger = -350;

	xLower = 1400;
	xOffset = 400;

	yLower = 400;
	yOffset = 180;

	initialScale = 0.0625;
	scaleLower = 7;
	scaleOffset = 3;

	spriteSize = { 512,2048 };
	rectFirstSprite = { 0,0, 512, 2048 };
	spriteCount = 4;
	animationTimer = 0;
	animationInterval = 0.05;

	// For building
	scoreIncreased = 1;
}


void Building::update(sf::RenderWindow& window, Data& data, Player& player, Sounds& sounds) {
	sf::Vector2f pos = sprite.getPosition();

	if (!scoreIncreased) {
		if (pos.x < 100 && !data.dead) {
			data.currentScore++;
			sounds.pointSound(data);
			scoreIncreased = 1;
		}
	}

	movement(data, sprite, 1);

	if (pos.x < respawnTrigger) {
		respawn(data, sprite);
	}

	checkCollision(data, player.sprite);

	animation(data, sprite);

	window.draw(sprite);
}

void Building::respawn(Data& data, sf::Sprite& sprite) {
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

	scoreIncreased = 0;
}

void Building::loadTextures() {
	if (!Collision::CreateTextureAndBitmask(tNormal, "sprites/buildings/buildingNormal.png")) {
		std::cout << "Could not load building Normal texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tPixel, "sprites/buildings/buildingPixel.png")) {
		std::cout << "Could not load building Pixel texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tSunset, "sprites/buildings/buildingSunset.png")) {
		std::cout << "Could not load building Sunset texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tApoc, "sprites/buildings/buildingApoc.png")) {
		std::cout << "Could not load building Apoc texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tSpace, "sprites/buildings/buildingSpace.png")) {
		std::cout << "Could not load building Space texture" << std::endl;
	}
}