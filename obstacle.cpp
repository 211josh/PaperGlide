#include "obstacle.h"

void Obstacle::update(sf::RenderWindow& window, Data& data, Player& player) {
	sf::Vector2f pos = sprite.getPosition();

	movement(data, sprite, 1);

	if (pos.x < respawnTrigger) {
		respawn(data, sprite);
	}

	checkCollision(data, player.sprite);

	animation(data, sprite);

	window.draw(sprite);
}

void Obstacle::movement(Data& data, sf::Sprite& sprite, float coefficient) {
	sf::Vector2f pos = sprite.getPosition();

	float increase;
	if (data.currentScore > data.velRange) {
		increase = data.velRange;
	} else {
		increase = data.currentScore;
	}
	sf::Vector2f velocity = coefficient*(initialVel + (increase * (velDif/data.velRange))); // velocity is increased by score while score < velRange uniformly
	sprite.move(velocity * data.deltaTime);
}

void Obstacle::respawn(Data& data, sf::Sprite& sprite) {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<float> disX(0, xOffset);
	float x = xLower + disX(gen);

	std::uniform_real_distribution<float> disY(0, yOffset);
	float y = yLower + disY(gen);

	std::uniform_real_distribution<float> disScale(0, scaleOffset);
	float scale = scaleLower + disScale(gen);

	sprite.setScale({ initialScale, initialScale });
	sprite.scale({ scale, scale });

	sprite.setPosition({ x,y });
}

void Obstacle::animation(Data& data, sf::Sprite& sprite) {
	animationTimer += data.deltaTime;
	if (animationTimer > animationInterval) {
		animationTimer = 0;
		if (rectFirstSprite.left == spriteSize.x * (spriteCount - 1)) {
			rectFirstSprite.left = 0;
		} else {
			rectFirstSprite.left += spriteSize.x;
		}
		sprite.setTextureRect(rectFirstSprite);
	}
}

void Obstacle::checkCollision(Data& data, sf::Sprite& sprite) {
	if (Collision::PixelPerfectTest(this->sprite, sprite)) {
		data.collided = 1;
	}
}

void Obstacle::setTheme(Data& data) {
	switch (data.theme) {
	case 0:
		sprite.setTexture(tNormal);
		break;
	case 1:
		sprite.setTexture(tPixel);
		break;
	case 2:
		sprite.setTexture(tSunset);
		break;
	case 3:
		sprite.setTexture(tApoc);
		break;
	case 4:
		sprite.setTexture(tSpace);
		break;
	}
}