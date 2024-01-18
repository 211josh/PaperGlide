#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

// Need several update functions. e.g. if in other state than main menu state, move all text off screen.

class Menu{
public:
    Menu();
    void menuUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState);
    void nonMenuUpdate(sf::RenderWindow& window);

    int menuSelect; // determines which option to select. 0 for play, 1 for settings, 2 for quit.
    float selectTimer; // Prevents fast menu scrolling

private:
    sf::Font font;
    sf::Text playText;
    sf::Text settingsText;
    sf::Text quitText;

    void handleInput(sf::RenderWindow& window, float deltaTime, int& gameState);
};

#endif // MENU_H_INCLUDED
