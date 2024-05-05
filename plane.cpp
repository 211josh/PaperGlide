#include "plane.h"

Plane::Plane(Data& data) {

	loadTextures();
	setTheme(data);

	respawn(data, sprite);

	initialVel = { -1050,0 };
	maximumVel = { -2000,0 };
	velDif = maximumVel - initialVel;

	respawnTrigger = -350;

	xLower = 1400;
	xOffset = 400;

	yLower = 0;
	yOffset = 400;

	initialScale = 1;
	scaleLower = 0.51;
	scaleOffset = 0.10;

	spriteSize = { 550,300 };
	rectFirstSprite = { 0,0, 550, 300 };
	spriteCount = 4;
	animationTimer = 0;
	animationInterval = 0.05;
}

void Plane::loadTextures() {
	if (!Collision::CreateTextureAndBitmask(tNormal, "sprites/planes/planeNormal.png")) {
		std::cout << "Could not load plane Normal texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tPixel, "sprites/planes/planePixel.png")) {
		std::cout << "Could not load plane Pixel texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tSunset, "sprites/planes/planeSunset.png")) {
		std::cout << "Could not load plane Sunset texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tApoc, "sprites/planes/planeApoc.png")) {
		std::cout << "Could not load plane Apoc texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tSpace, "sprites/planes/planeSpace.png")) {
		std::cout << "Could not load plane Space texture" << std::endl;
	}
}