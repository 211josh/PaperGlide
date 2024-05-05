#include "menu.h"

Menu::Menu(Data& data) {
    if (!font.loadFromFile("sprites/Font.ttf")) {
        std::cout << "Could not load Menu font";
    }
    currentScore = 0;

    // Set fonts
    title.setFont(font);
    playScore.setFont(font);
    tryagainScore.setFont(font);
    option1.setFont(font);
    option2.setFont(font);
    option3.setFont(font);
    option4.setFont(font);
    highScore.setFont(font);
    unlockText.setFont(font);
    versionText.setFont(font);

    // Set size
    title.setCharacterSize(150);
    playScore.setCharacterSize(300);
    tryagainScore.setCharacterSize(150);
    option1.setCharacterSize(90);
    option2.setCharacterSize(90);
    option3.setCharacterSize(90);
    option4.setCharacterSize(90);
    highScore.setCharacterSize(100);
    unlockText.setCharacterSize(40);
    versionText.setCharacterSize(40);

    // Set text
    playScore.setString("0");
    title.setString("PAPERGLIDE");
    versionText.setString("V1.0");

    // Positioning
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setPosition((data.screenWidth - titleBounds.width) / 2, 20);
    versionText.setPosition({ 1195,665 });

    // Color
    title.setOutlineColor(sf::Color{ 0,0,0,255 });
    title.setOutlineThickness(10);
    playScore.setFillColor({ 255,255,255,230 });
    tryagainScore.setFillColor({255, 255, 255, 230});
    highScore.setFillColor({ 255,255,255,230 });
    unlockText.setFillColor(sf::Color{ 255,0,0,255 });
    versionText.setFillColor({ 255,255,255,100 });
    menuSelect = 0;
    playerTheme = data.playerTheme;
    theme = data.theme;

    selectTimer = 0;

    goMenu(data); // Game starts on menu
}

void Menu::update(sf::RenderWindow& window, Data& data, Sounds& sounds) {
    
    if (data.gameState != 4) {
        window.draw(title);
        window.draw(versionText);
    }
    else {
        window.draw(tryagainScore);
    }
    window.draw(option1);
    window.draw(option2);
    window.draw(option3);
    window.draw(highScore);
    
    
    if (data.gameState == 0) {
        window.draw(option4);
        
    }

    if (locked) {
        window.draw(unlockText);
    }

    handleInput(window, data, sounds);
}

void Menu::playUpdate(sf::RenderWindow& window, Data& data, Sounds& sounds) {
    if (data.dead == 1) { // if player dies
        sounds.gameoverSound(data);
        data.gameState = 4; // go to retry screen
        goRetry(data);
    }
    if (currentScore != data.currentScore) {
        currentScore = data.currentScore;
        sounds.pointSound(data);
        goPlay(data);
    }
    window.draw(playScore);
}

void Menu::handleInput(sf::RenderWindow& window, Data& data, Sounds& sounds) {
    selectTimer += data.deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && selectTimer > 0.2) {
        if (data.gameState == 0) { // if enter is pressed on MENU
            switch (menuSelect) {
            case 0: // if on play

                goPlay(data);
                sounds.startSound(data);
                menuSelect = 0;
                data.gameState = 1;
                break;
            case 1: // if on customise
                sounds.menuSound(data);
                menuSelect = 0;
                goCustomise(data);
                data.gameState = 2;
                break;
            case 2: // if on settings
                selectTimer = 0;
                sounds.menuSound(data);
                menuSelect = 0;
                goSettings(data);
                data.gameState = 3;
                break;
            case 3: // on quit
                window.close();
                break;
            }
        }
        if (data.gameState == 2 && selectTimer > 0.2) { // if enter is pressed on CUSTOMISE
            if (menuSelect == 2) { // if on back
                selectTimer = 0;
                sounds.menuSound(data);
                data.writeDataTxt();
                menuSelect = 1;
                goMenu(data);
                data.gameState = 0;
            }
        }
        if (data.gameState == 3 && selectTimer > 0.2) { // if enter is pressed on SETTINGS
            if (menuSelect == 0) { // on fullscreen/windowed
                selectTimer = 0;
                if (!data.isFullscreen) {
                    data.changeFullscreen(window, 1);
                    goSettings(data);
                } else {
                    data.changeFullscreen(window, 0);
                    goSettings(data);
                }
            }


            if (menuSelect == 2) { // if on back
                selectTimer = 0;
                sounds.menuSound(data);
                data.writeDataTxt();
                goMenu(data);
                data.gameState = 0;
            }
        }
        if (data.gameState == 4) { // if enter is pressed on TRY AGAIN SCREEN
            if (menuSelect == 0) { // on retry
                data.currentScore = 0;
                currentScore = 0;
                goPlay(data);
                data.gameReset = 1;
                data.gameState = 1;
                sounds.startSound(data);
                menuSelect = 0;
            }
            if (menuSelect == 1) { // on menu
                data.currentScore = 0;
                currentScore = 0;
                goPlay(data);
                selectTimer = 0;
                sounds.menuSound(data);
                menuSelect = 0;
                data.gameState = 0;
                goMenu(data);
                data.gameReset = 1;
            }
            if (menuSelect == 2) {
                window.close();
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && selectTimer > 0.2f) {
        if (data.gameState == 2) {
            if (data.highScore < data.playerThemeMap[playerTheme].second) { // if not enough score for the selected player theme
                playerTheme = 0;
            }
            if (data.highScore < data.themeMap[theme].second) { // if not enough score for the selected theme
                theme = 0;
            }
            goCustomise(data);
        }

        sounds.menuSound(data);
        selectTimer = 0;
        menuSelect = (menuSelect - 1 + menuOptions) % menuOptions;
        colorText(data);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && selectTimer > 0.2f) {
        if (data.gameState == 2) {
            if (data.highScore < data.playerThemeMap[playerTheme].second) { // if not enough score for the selected player theme
                playerTheme = 0;
            }
            if (data.highScore < data.themeMap[theme].second) { // if not enough score for the selected theme
                theme = 0;
            }
            goCustomise(data);
        }

        sounds.menuSound(data);
        selectTimer = 0;
        menuSelect = (menuSelect + 1) % menuOptions;
        colorText(data);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && selectTimer > 0.2f) {
        selectTimer = 0;
        if (data.gameState == 2) { // if on CUSTOMISE
            if (menuSelect == 0) { // on playerTheme
                sounds.menuSound(data);
                playerTheme = (playerTheme + 1) % 5;
            }
            if (menuSelect == 1) { // on Theme
                sounds.menuSound(data);
                theme = (theme + 1) % 5;
            }
            goCustomise(data);
        }
        if (data.gameState == 3) { // if on SETTINGS
            if (menuSelect == 1) { // if on volume
                data.volume = (data.volume + 1) % 11;
                sounds.menuSound(data);
            }
            goSettings(data);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && selectTimer > 0.2f) {
        selectTimer = 0;
        if (data.gameState == 2) { // if on CUSTOMISE
            if (menuSelect == 0) { // on playerTheme
                sounds.menuSound(data);
                playerTheme = (playerTheme - 1 + 5) % 5;
            }
            if (menuSelect == 1) { // on Theme
                sounds.menuSound(data);
                theme = (theme - 1 + 5) % 5;
            }
            goCustomise(data);
        }
        if (data.gameState == 3) { // if on SETTINGS
            if (menuSelect == 1) { // if on volume
                data.volume = (data.volume - 1 + 11) % 11;
                sounds.menuSound(data);
            }
            goSettings(data);
        }
    }
}

void Menu::goPlay(Data& data) {
    playScore.setString(std::to_string(currentScore));

    positionText(data);
}

void Menu::goMenu(Data& data) {
    tryagainScore.setString("Score: " + std::to_string(data.currentScore));
    option1.setString("Play");
    option2.setString("Customise");
    option3.setString("Settings");
    option4.setString("Quit");
    highScore.setString("Highscore: " + std::to_string(data.highScore));

    menuOptions = 4;

    positionText(data);
    colorText(data);
}

void Menu::goCustomise(Data& data) {
    colorText(data);

    option1.setString("< Player: " + data.playerThemeMap[playerTheme].first + " >");
    option2.setString("< Theme: " + data.themeMap[theme].first + " >");
    option3.setString("Back");

    locked = 0;

    if (data.highScore < data.playerThemeMap[playerTheme].second) { // if not enough score for the selected player theme
        unlockText.setString("SCORE " + std::to_string(data.playerThemeMap[playerTheme].second) + " POINTS TO UNLOCK!");
        locked = 1;
        option1.setFillColor({ 255,0,0,255 });
    } else {
        data.playerTheme = playerTheme;
    }
    if (data.highScore < data.themeMap[theme].second) { // if not enough score for the selected theme
        unlockText.setString("SCORE " + std::to_string(data.themeMap[theme].second) + " POINTS TO UNLOCK!");
        locked = 1;
        option2.setFillColor({ 255,0,0,255 });
    } else {
        data.theme = theme;
    }
    sf::FloatRect unlockTextBounds = unlockText.getLocalBounds();
    unlockText.setPosition((data.screenWidth - unlockTextBounds.width) / 2, 500);

    menuOptions = 3;

    positionText(data);
}

void Menu::goSettings(Data& data) {
    if (data.isFullscreen) {
        option1.setString("Windowed");
    } else {
        option1.setString("Fullscreen");
    }
    option2.setString("< Volume: " + std::to_string(data.volume) + " >");
    option3.setString("Back");

    menuOptions = 3;

    positionText(data);
    colorText(data);
}

void Menu::goRetry(Data& data) {
    tryagainScore.setString("Score: " + std::to_string(data.currentScore));
    option1.setString("Retry");
    option2.setString("Menu");
    option3.setString("Quit");
    highScore.setString("Highscore: " + std::to_string(data.highScore));

    menuOptions = 3;

    positionText(data);
    colorText(data);
}

void Menu::positionText(Data& data) {
    sf::FloatRect playscoreBounds = playScore.getLocalBounds();
    sf::FloatRect tryagainBounds = tryagainScore.getLocalBounds();
    sf::FloatRect option1Bounds = option1.getLocalBounds();
    sf::FloatRect option2Bounds = option2.getLocalBounds();
    sf::FloatRect option3Bounds = option3.getLocalBounds();
    sf::FloatRect option4Bounds = option4.getLocalBounds();
    sf::FloatRect highscoreBounds = highScore.getLocalBounds();

    playScore.setPosition((data.screenWidth - playscoreBounds.width) / 2, 100);
    tryagainScore.setPosition((data.screenWidth - tryagainBounds.width) / 2, 100);
    option1.setPosition((data.screenWidth - option1Bounds.width) / 2, 240);
    option2.setPosition((data.screenWidth - option2Bounds.width) / 2, 300);
    option3.setPosition((data.screenWidth - option3Bounds.width) / 2, 360);
    option4.setPosition((data.screenWidth - option4Bounds.width) / 2, 420);
    highScore.setPosition((data.screenWidth - highscoreBounds.width) / 2, 600);
}

void Menu::colorText(Data& data) {
    option1.setFillColor({ 255,255,255,230 });
    option2.setFillColor({ 255,255,255,230 });
    option3.setFillColor({ 255,255,255,230 });
    option4.setFillColor({ 255,255,255,230 });
    switch (menuSelect) {
    case 0:
        option1.setFillColor({ 255,255,0,230 });
        break;
    case 1:
        option2.setFillColor({ 255,255,0,230 });
        break;
    case 2:
        option3.setFillColor({ 255,255,0,230 });
        break;
    case 3:
        option4.setFillColor({ 255,255,0,230 });
        break;
    }
}

