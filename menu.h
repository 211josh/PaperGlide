#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

#include "data.h"
#include "sounds.h"

#ifndef MENU_H
#define MENU_H

class Menu {
public:
	Menu(Data& data);
	void update(sf::RenderWindow& window, Data& data, Sounds& sounds);
	void playUpdate(sf::RenderWindow& window, Data& data, Sounds& sounds); // checks for change in gamestate during play

private:
	void handleInput(sf::RenderWindow& window, Data& data, Sounds& sounds); // all other functions are called by events in handleInput

	void goPlay(Data& data);
	void goMenu(Data& data);
	void goCustomise(Data& data);
	void goSettings(Data& data);
	void goRetry(Data& data);

	void positionText(Data& data);
	void colorText(Data& data);

	int menuSelect;

	int currentScore;

	int playerTheme;
	int theme;

	bool locked;

	float selectTimer;
	int menuOptions;

	sf::Font font;
	
	sf::Text title;
	sf::Text playScore;
	sf::Text tryagainScore;
	sf::Text option1;
	sf::Text option2;
	sf::Text option3;
	sf::Text option4;
	sf::Text highScore;
	sf::Text unlockText;
	sf::Text versionText;
};

#endif 