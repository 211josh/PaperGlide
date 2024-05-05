#include "background.h"

Background::Background(Data& data) {
	isDay = 1;
	daynightComplete = 1;
	daynightInterval = 4;
	
	loadTextures();
	setTheme(data);

	initialVel = { -187,0 };
	maximumVel = { -800, 0 };
	velDif = maximumVel - initialVel;

	respawnTrigger = -5120;

	xLower = 0;
	xOffset = 0;

	yLower = 0;
	yOffset = 0;

	initialScale = 1;
	scaleLower = 1;
	scaleOffset = 0;

	sunShine.setTexture(tsunShine);
	sun.setPosition(sunInitialPos);
	sunShine.setOrigin(tsunShine.getSize().x / 2, tsunShine.getSize().y / 2);
}

void Background::update(sf::RenderWindow& window, Data& data) {
	sf::Vector2f skyPos = sky.getPosition();
	sf::Vector2f buildingsPos = buildings.getPosition();
	sf::Vector2f sunPos = sun.getPosition();

	if (data.theme == 4) {
		movement(data, sky, 0.5);
	} else {
		movement(data, sky, 1);
	}
	movement(data, buildings, 1);

	if (skyPos.x < respawnTrigger) {
		Obstacle::respawn(data, sky);
	}
	if (buildingsPos.x < respawnTrigger) {
		Obstacle::respawn(data, buildings);
	}
	
	movement(data, sun, 0.35);
	if (data.theme == 2) {
		if (sunPos.x < -550) {
			sun.setPosition(sunInitialPos);
		}
	} else { // if not theme sunset
		if (sunPos.x < -250) {
			sun.setPosition(sunInitialPos);
			if (data.theme == 0 || data.theme == 1) {
				isDay = !isDay;
				setTheme(data); // because of sun/moon
				daynightComplete = 0;
			}
			setTheme(data); // because of sun/moon
		}
	}
	sunShine.setPosition(sunPos);

	if (!daynightComplete) {
		dayNight(data);
	}

	window.draw(sky);
	window.draw(sunShine);
	window.draw(sun);
	window.draw(buildings);
}

void Background::dayNight(Data& data) {
	daynightTimer += data.deltaTime;
	if (daynightTimer < daynightInterval) {
		if (isDay) { // if it's becoming day time
			sf::Uint8 colorComponent = static_cast<sf::Uint8>(40 + (255 - 40) * (daynightTimer / daynightInterval));
			sky.setColor(sf::Color(colorComponent, colorComponent, colorComponent, 255));
		} else { // if it's becoming night time
			sf::Uint8 colorComponent = static_cast<sf::Uint8>(255 - (255 - 40) * (daynightTimer / daynightInterval));
			sky.setColor(sf::Color(colorComponent, colorComponent, colorComponent, 255));
		}
	} else {
		daynightComplete = 1;
		daynightTimer = 0;
		if (isDay) {
			sky.setColor(sf::Color({ 255,255,255,255 }));
		} else {
			sky.setColor(sf::Color({ 40,40,40,255 }));
		}
	}
}


void Background::setTheme(Data& data) {
	sf::Vector2f sunPos = sun.getPosition();
	switch (data.theme) {
	case 0:
		sky.setTexture(skyNormal);
		buildings.setTexture(buildingsNormal);
		buildings.setColor({ 255,255,255,100 });

		sunInitialPos = {1650,150};
		if (isDay) {
			sun.setTexture(sunNormal);
			sun.setColor(sf::Color({ 255,255,160,255 }));
		} else {
			sun.setTexture(moonNormal);
			sun.setColor(sf::Color({ 255,255,255,255 }));
		}
		sun.setScale({ 0.75,0.75 });

		sunShine.setColor({ 255,255,255,200 });
		sunShine.setScale({ 0.9,0.9 });
		sun.setOrigin(sunNormal.getSize().x / 2, sunNormal.getSize().y / 2);
		
		break;
	case 1:
		sky.setTexture(skyPixel);
		buildings.setTexture(buildingsPixel);
		buildings.setColor({ 255,255,255,100 });

		sunInitialPos = { 1650,150 };
		if (isDay) {
			sun.setTexture(sunPixel);
			sun.setColor(sf::Color({ 255,255,160,255 }));
		} else {
			sun.setTexture(moonPixel);
			sun.setColor(sf::Color({ 255,255,255,255 }));
		}
		
		sun.setScale({ 0.75,0.75 });

		sunShine.setColor({ 255,255,255,200 });
		sunShine.setScale({ 0.9,0.9 });
		sun.setOrigin(sunPixel.getSize().x / 2, sunPixel.getSize().y / 2);
		break;
	case 2:
		sky.setTexture(skySunset);
		sky.setColor(sf::Color{ 255,255,255,255 });
		daynightComplete = 1;
		isDay = 1;
		buildings.setTexture(buildingsSunset);
		buildings.setColor({ 255,255,255,255 });

		sun.setTexture(sunNormal);
		sunInitialPos = { 1800,650 };

		sun.setColor(sf::Color({ 255,0,255,255 }));
		sun.setScale({ 2.2, 2.2 });

		sunShine.setColor({ 255,255,255,200 });
		sunShine.setScale({ 0,0 });
		sun.setOrigin(sunNormal.getSize().x / 2, sunNormal.getSize().y / 2);
		break;
	case 3:
		sky.setTexture(skyApoc);
		sky.setColor(sf::Color{ 255,255,255,255 });
		daynightComplete = 1;
		isDay = 1;
		buildings.setTexture(buildingsApoc);
		buildings.setColor({ 135,0,0,100 });

		sun.setTexture(sunApoc);
		sunInitialPos = { 1600,150 };

		sun.setColor(sf::Color({ 255,255,255,255 }));
		sun.setScale({ 0.9,0.9 });

		sunShine.setColor({ 255,0,0,255 });
		sunShine.setScale({ 1,1 });
		sun.setOrigin(sunApoc.getSize().x / 2, sunApoc.getSize().y / 2);
		break;
	case 4:
		sky.setTexture(skySpace);
		sky.setColor(sf::Color{ 255,255,255,255 });
		daynightComplete = 1;
		isDay = 1;
		buildings.setTexture(buildingsSpace);
		buildings.setColor({ 255,255,255,255 });

		sun.setTexture(sunSpace);
		sunInitialPos = { 1600,360 };

		sun.setColor(sf::Color({ 255,255,255,255 }));
		sun.setScale({ 0.9,0.9 });

		sunShine.setColor({ 255,255,255,200 });
		sunShine.setScale({ 0.1,0.1 });
		sun.setOrigin(sunSpace.getSize().x / 2, sunSpace.getSize().y / 2);
		break;
	}

	sun.setPosition(sunPos.x, sunInitialPos.y);
}

void Background::respawn(Data& data) {
	isDay = 1;
	sky.setColor({ 255,255,255,255 });
	daynightComplete = 1;

	setTheme(data);
	sun.setPosition(sunInitialPos);
}

void Background::loadTextures() {
	if (!skyNormal.loadFromFile("sprites/backgrounds/skyNormal.png")) {
		std::cout << "Failed to load skyNormal.png" << std::endl;
	}
	if (!skyPixel.loadFromFile("sprites/backgrounds/skyNormal.png")) {
		std::cout << "Failed to load skyNormal.png" << std::endl;
	}
	if (!skySunset.loadFromFile("sprites/backgrounds/skySunset.png")) {
		std::cout << "Failed to load skySunset.png" << std::endl;
	}
	if (!skyApoc.loadFromFile("sprites/backgrounds/skyApoc.png")) {
		std::cout << "Failed to load skyApoc.png" << std::endl;
	}
	if (!skySpace.loadFromFile("sprites/backgrounds/skySpace.png")) {
		std::cout << "Failed to load skySpace.png" << std::endl;
	}

	if (!buildingsNormal.loadFromFile("sprites/backgrounds/buildingsNormal.png")) {
		std::cout << "Failed to load buildingsNormal.png" << std::endl;
	}
	if (!buildingsPixel.loadFromFile("sprites/backgrounds/buildingsNormal.png")) {
		std::cout << "Failed to load buildingsNormal.png" << std::endl;
	}
	if (!buildingsSunset.loadFromFile("sprites/backgrounds/buildingsSunset.png")) {
		std::cout << "Failed to load buildingsSunset.png" << std::endl;
	}
	if (!buildingsApoc.loadFromFile("sprites/backgrounds/buildingsApoc.png")) {
		std::cout << "Failed to load buildingsApoc.png" << std::endl;
	}
	if (!buildingsSpace.loadFromFile("sprites/backgrounds/buildingsSpace.png")) {
		std::cout << "Failed to load buildingsSpace.png" << std::endl;
	}

	if (!sunNormal.loadFromFile("sprites/suns/sunNormal.png")) {
		std::cout << "Failed to load sunNormal.png." << std::endl;
	}
	if (!moonNormal.loadFromFile("sprites/suns/moonNormal.png")) {
		std::cout << "Failed to load moonNormal.png." << std::endl;
	}

	if (!sunPixel.loadFromFile("sprites/suns/sunPixel.png")) {
		std::cout << "Failed to load sunPixel.png." << std::endl;
	}
	if (!moonPixel.loadFromFile("sprites/suns/moonPixel.png")) {
		std::cout << "Failed to load moonPixel.png." << std::endl;
	}

	if (!sunApoc.loadFromFile("sprites/suns/sunApoc.png")) {
		std::cout << "Failed to load sunApoc.png." << std::endl;
	}

	if (!sunSpace.loadFromFile("sprites/suns/sunSpace.png")) {
		std::cout << "Failed to load sunSpace.png." << std::endl;
	}

	if (!tsunShine.loadFromFile("sprites/suns/sunShine.png")) {
		std::cout << "Failed to load sunShine.png." << std::endl;
	}
}	