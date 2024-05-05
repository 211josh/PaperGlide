#include "player.h"

Player::Player(Data& data) {
	loadTextures();
	setTheme(data);

	speed = -2500;
	gravity = speed * -0.5;
	terminalVel = 1000;
	velocity = { 0,0 };
	maxRotation = 70;

	// Set origin point to centre of sprite
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

	sprite.setPosition(sf::Vector2f(100, 400));
	sprite.scale(sf::Vector2f(0.2, 0.2));

	// Death screen
	deathScreen.setTexture(tdeathScreen);
	deathScreen.setColor({ 255,255,255,50 });


	// Hold space
	holdSpace.setFont(font);
	holdSpace.setString("Hold Space");
	holdSpace.setCharacterSize(25);
	holdSpace.setFillColor(sf::Color{ 255,255,255,200 });
	upArrow.setTexture(tupArrow);
	upArrow.setColor({ 255,255,255,200 });

}

void Player::update(sf::RenderWindow& window, Data& data, Sounds& sounds) {
	playerTimer += data.deltaTime;
	if (window.hasFocus()) {
		handleInput(data);
	}
	velocity.y += gravity * data.deltaTime;
	if (velocity.y > terminalVel) {
		velocity.y = terminalVel;
	}
	if (velocity.y < -terminalVel) {
		velocity.y = -terminalVel;
	}
	sprite.move(velocity * data.deltaTime);
	sprite.setRotation((maxRotation * velocity.y) / terminalVel);

	sf::Vector2f pos = sprite.getPosition();
	if (pos.y > data.screenHeight && !data.dead) {
		data.collided = 1;
		data.dead = 1;

		if (data.currentScore > data.highScore) {
			data.highScore = data.currentScore;
			data.writeDataTxt();
		}
	}
	if (pos.y < 0 && !data.collided) {
		data.collided = 1;
	}

	if (data.collided) {
		if (!hitsoundPlayed) {
			hitsoundPlayed = 1;
			sounds.hitSound(data);
			playerTimer = 0;
		}
		if (playerTimer < 0.3) {
			sprite.setColor({ 255,100,100,255 });
			window.draw(deathScreen);
		}
		else {
			sprite.setColor({ 255,255,255,255 });
		}
	}

	window.draw(sprite);
}

void Player::menuFloat(sf::RenderWindow& window, Data& data) {
	sf::Vector2f pos = sprite.getPosition();

	playerTimer += data.deltaTime;
	sprite.setPosition(100, 150 * sin(playerTimer) + 400);
	sprite.setRotation((maxRotation / 4 * cos(playerTimer)));
	window.draw(sprite);

	pos = sprite.getPosition();

	holdSpace.setPosition({ pos.x - 65, pos.y + 40 });
	upArrow.setPosition({ pos.x + 90, pos.y + 43 });
	window.draw(holdSpace);

	if ( fmod(playerTimer, 2) < 1) {
		window.draw(upArrow);
	}
}

void Player::handleInput(Data& data) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !data.collided) {
		velocity.y += speed * data.deltaTime;
	}
}

void Player::respawn() {
	sprite.setPosition(100, 400);
	velocity = { 0, 0 };
	hitsoundPlayed = 0;
	sprite.setColor({ 255,255,255,255 });

}

void Player::setTheme(Data& data) {
	switch (data.playerTheme) {
	case 0:
		sprite.setTexture(tNormal);
		break;
	case 1:
		sprite.setTexture(tPixel);
		break;
	case 2:
		sprite.setTexture(tGold);
		break;
	case 3:
		sprite.setTexture(tOrigami);
		break;
	case 4:
		sprite.setTexture(tKing);
		break;
	}
}

void Player::loadTextures() {
	if (!font.loadFromFile("sprites/Font.ttf")) {
		std::cout << "Could not load player font";
	}

	if (!Collision::CreateTextureAndBitmask(tNormal, "sprites/players/playerNormal.png")) {
		std::cout << "Could not load player Normal texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tPixel, "sprites/players/playerPixel.png")) {
		std::cout << "Could not load player Pixel texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tGold, "sprites/players/playerGold.png")) {
		std::cout << "Could not load player Gold texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tOrigami, "sprites/players/playerOrigami.png")) {
		std::cout << "Could not load player Origami texture" << std::endl;
	}
	if (!Collision::CreateTextureAndBitmask(tKing, "sprites/players/playerKing.png")) {
		std::cout << "Could not load player King texture" << std::endl;
	}

	if (!tdeathScreen.loadFromFile("sprites/players/deathScreen.png")) {
		std::cout << "Could not load death screen texture." << std::endl;
	}

	if (!tupArrow.loadFromFile("sprites/upArrow.png")) {
		std::cout << "Could not load up arrow texture." << std::endl;
	}
}