#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "menu.h"

Menu::Menu(int screenWidth, Score& score, Background& background, Plane& plane, Helicopter& helicopter, Player& player, Sounds& sound){
    if(!font.loadFromFile("sprites/Font.ttf")){
        std::cout << "Could not load Menu font";
    }
    if(!arrowTexture.loadFromFile("sprites/upArrow.png")){
        std::cout << "Could not load upArrow font";
    }
    sf::Sprite upArrow;

    readVolume(sound);
    menuSelect = 0; // Menu opens on play option
    playerSelect = player.Style; //CHANGE THIS TO OPEN AND READ FILE
    themeSelect = background.Style; // CHANGE THIS TO OPEN AND READ FILE

    resetSelection(score, background, plane, helicopter, player);

    selectTimer = 0; // Min time wait between changing menu option. Prevents endless fast scrolling.

    /// Var declarations
    // Scores required for unlocks
    playerPixelScore = 10;
    goldScore = 25;
    origamiScore = 50;
    kingScore = 1000;

    pixelScore = 10;
    sunsetScore = 25;
    apocScore = 50;
    spaceScore = 100;

    //Menu
    titleText.setOutlineColor(sf::Color{0,0,0,255});
    titleText.setOutlineThickness(10);

    titleText.setFont(font);
    playText.setFont(font);
    customiseText.setFont(font);
    settingsText.setFont(font);
    quitText.setFont(font);
    versionText.setFont(font);

    titleText.setString("PAPERGLIDE");
    playText.setString("Play"); // Words on menu screen
    customiseText.setString("Customise");
    settingsText.setString("Settings");
    quitText.setString("Quit");
    versionText.setString("v1.0");

    titleText.setCharacterSize(150);
    playText.setCharacterSize(90); // Word sizes
    customiseText.setCharacterSize(90);
    settingsText.setCharacterSize(90);
    quitText.setCharacterSize(90);
    versionText.setCharacterSize(90);

    sf::FloatRect titleTextBounds = titleText.getLocalBounds();
    sf::FloatRect playTextBounds = playText.getLocalBounds(); // Retrieve menu option bounds
    sf::FloatRect customiseTextBounds = customiseText.getLocalBounds();
    sf::FloatRect settingsTextBounds = settingsText.getLocalBounds();
    sf::FloatRect quitTextBounds = quitText.getLocalBounds();

    titleText.setPosition((screenWidth - titleTextBounds.width)/2, 20);
    playText.setPosition((screenWidth - playTextBounds.width) / 2, 240); // Centres text based on text and screen width
    customiseText.setPosition((screenWidth - customiseTextBounds.width)/2, 300);
    settingsText.setPosition((screenWidth - settingsTextBounds.width) / 2, 360);
    quitText.setPosition((screenWidth - quitTextBounds.width) / 2, 420);
    versionText.setPosition(1200,675);

    // Customisation
    playerText.setFont(font);
    themeText.setFont(font);
    unlockText.setFont(font);
    unlockText.setFillColor(sf::Color{255,0,0,255});
    playerText.setCharacterSize(90);
    themeText.setCharacterSize(90);
    unlockText.setCharacterSize(40);

    // Retry
    retryText.setFont(font);
    menuText.setFont(font);
    quit2Text.setFont(font);

    retryText.setString("Retry");
    menuText.setString("Menu");
    quit2Text.setString("Quit");

    retryText.setCharacterSize(90);
    menuText.setCharacterSize(90);
    quit2Text.setCharacterSize(90);

    sf::FloatRect retryBounds = retryText.getLocalBounds(); // Retrieve menu option bounds
    sf::FloatRect menuBounds = menuText.getLocalBounds();
    sf::FloatRect quit2Bounds = quit2Text.getLocalBounds();

    retryText.setPosition((screenWidth - retryBounds.width) / 2, 240); // Centres text based on text and screen width
    menuText.setPosition((screenWidth - menuBounds.width) / 2, 320);
    quit2Text.setPosition((screenWidth - quit2Bounds.width) / 2, 400);

    // Settings
    fullscreenText.setFont(font);
    volumeText.setFont(font);
    backText.setFont(font);

    backText.setString("Back");

    volumeText.setCharacterSize(90);
    backText.setCharacterSize(90);

    sf::FloatRect backTextBounds = backText.getLocalBounds();

    backText.setPosition((screenWidth - backTextBounds.width) / 2, 400);

    // Hold space
    holdSpaceText.setFont(font);
    holdSpaceText.setString("Hold Space");
    holdSpaceText.setCharacterSize(25);
    holdSpaceText.setFillColor(sf::Color{255,255,255,200});
    holdSpaceText.setOrigin(sf::Vector2f(0.0f,0.0f));

    // Up arrow
    upArrow.setTexture(arrowTexture);
    upArrow.setColor(sf::Color{255,255,255,200});

    // Error screen
    errorText.setFont(font);
    errorText.setCharacterSize(40);
    errorText.setFillColor(sf::Color(255,0,0,255));
    errorText.setString("ERROR: Missing game files. Please re-install the game.");
    sf::FloatRect errorTextBounds = errorText.getLocalBounds();
    errorText.setPosition((screenWidth - errorTextBounds.width) / 2 , 320);
    }


void Menu::menuUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, Score& score, int& isFullscreen, int screenHeight){

    holdSpaceDisplay(window, player);
    handleInput(window, deltaTime, gameState, sound, background, player, building, helicopter, plane, score, isFullscreen, screenWidth, screenHeight);
    selectTimer += deltaTime;

    if(menuSelect == 0){ // if on play
        playText.setFillColor(sf::Color{255,255,0,230});
        customiseText.setFillColor(sf::Color{255,255,255,230});
        settingsText.setFillColor(sf::Color{255,255,255,230});
        quitText.setFillColor(sf::Color{255,255,255,230});
        }

    if(menuSelect == 1){ // if on customise
        playText.setFillColor(sf::Color{255,255,255,230});
        customiseText.setFillColor(sf::Color{255,255,0,230});
        settingsText.setFillColor(sf::Color{255,255,255,230});
        quitText.setFillColor(sf::Color{255,255,255,230});

    }

    if(menuSelect == 2){ // if on settings
        playText.setFillColor(sf::Color{255,255,255,230});
        customiseText.setFillColor(sf::Color{255,255,255,230});
        settingsText.setFillColor(sf::Color{255,255,0,230});
        quitText.setFillColor(sf::Color{255,255,255,230});
        }

    if(menuSelect == 3){ // if on quit
        playText.setFillColor(sf::Color{255,255,255,230});
        customiseText.setFillColor(sf::Color{255,255,255,230});
        settingsText.setFillColor(sf::Color{255,255,255,230});
        quitText.setFillColor(sf::Color{255,255,0,230});
        }

    versionText.setFillColor(sf::Color{255,255,255,70});

    window.draw(titleText);
    window.draw(playText);
    window.draw(customiseText);
    window.draw(settingsText);
    window.draw(quitText);
    window.draw(versionText);
    }

void Menu::customiseUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, Score& score, int& isFullscreen, int screenHeight){
    window.draw(titleText);
    holdSpaceDisplay(window, player);
    handleInput(window, deltaTime, gameState, sound, background, player, building, helicopter, plane, score, isFullscreen, screenWidth, screenHeight);
    selectTimer += deltaTime;
    unlockText.setString("");

    // Menu navigation
    if(menuSelect == 0){ // if on player theme
        playerText.setFillColor(sf::Color{255,255,0,230});
        themeText.setFillColor(sf::Color{255,255,255,230});
        backText.setFillColor(sf::Color{255,255,255,230});
        }

    if(menuSelect == 1){ // if on theme
        playerText.setFillColor(sf::Color{255,255,255,230});
        themeText.setFillColor(sf::Color{255,255,0,230});
        backText.setFillColor(sf::Color{255,255,255,230});
    }

    if(menuSelect == 2){ // if on back
        playerText.setFillColor(sf::Color{255,255,255,230});
        themeText.setFillColor(sf::Color{255,255,255,230});
        backText.setFillColor(sf::Color{255,255,0,230});
        }

    // Changing player
    if(playerSelect == 0){
        playerText.setString("< Player: Normal >");
        }
    if(playerSelect == 1){
        playerText.setString("< Player: Pixel >");
        if(score.high_score < playerPixelScore){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(playerPixelScore) + " points to unlock!");
            playerText.setFillColor({255,0,0,230});
            }
        }

    if(playerSelect == 2){
        playerText.setString("< Player: Gold >");
        if(score.high_score < goldScore){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(goldScore) + " points to unlock!");
            playerText.setFillColor({255,0,0,230});
            }
        }

    if(playerSelect == 3){
        playerText.setString("< Player: Origami >");
        if(score.high_score < origamiScore){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(origamiScore) + " points to unlock!");
            playerText.setFillColor({255,0,0,230});
            }
        }
    if(playerSelect == 4){
        playerText.setString("< Player: King >");
        if(score.high_score < kingScore){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(kingScore) + " points to unlock!");
            playerText.setFillColor({255,0,0,230});
            }
        }

    // Changing theme
    if(themeSelect == 0){
        themeText.setString(" < Theme: Normal > ");
    }
    if(themeSelect == 1){
        themeText.setString(" < Theme: Pixel >");
        if(score.high_score < pixelScore){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(pixelScore) + " points to unlock!");
            themeText.setFillColor({255,0,0,230});
        }
    }
    if(themeSelect == 2){
        themeText.setString(" < Theme: Pink Sunset >");
        if(score.high_score < sunsetScore){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(sunsetScore) + " points to unlock!");
            themeText.setFillColor({255,0,0,230});
        }
    }
    if(themeSelect == 3){
        themeText.setString(" < Theme: Apocalypse >");
        if(score.high_score < apocScore){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(apocScore) + " points to unlock!");
            themeText.setFillColor({255,0,0,230});
        }
    }
    if(themeSelect == 4){
        themeText.setString(" < Theme: Space >");
        if(score.high_score < spaceScore){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(spaceScore) + " points to unlock!");
            themeText.setFillColor({255,0,0,230});
        }
    }

    sf::FloatRect playerBounds = playerText.getLocalBounds();
    sf::FloatRect themeBounds = themeText.getLocalBounds();
    sf::FloatRect unlockBounds = unlockText.getLocalBounds();

    playerText.setPosition((screenWidth - playerBounds.width)/2, 240);
    themeText.setPosition((screenWidth - themeBounds.width)/2, 320);
    unlockText.setPosition((screenWidth - unlockBounds.width)/2, 500);

    window.draw(playerText);
    window.draw(themeText);
    window.draw(backText);
    window.draw(unlockText);
    }

void Menu::settingsUpdate(sf::RenderWindow& window, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, Score& score, int screenWidth, int& isFullscreen, int screenHeight){

    // Fullscreen text
    if(isFullscreen == 1){
        fullscreenText.setString("Windowed");
        } else{
        fullscreenText.setString("Fullscreen");
        }
    fullscreenText.setCharacterSize(90);
    sf::FloatRect fullscreenBounds = fullscreenText.getLocalBounds(); // Retrieve menu option bounds
    fullscreenText.setPosition((screenWidth - fullscreenBounds.width) / 2, 240); // Centres text based on text and screen width

    volumeText.setString("< Volume: " + std::to_string(sound.volume) + " >");
    sf::FloatRect volumeTextBounds = volumeText.getLocalBounds();
    volumeText.setPosition((screenWidth - volumeTextBounds.width) / 2, 320);

    holdSpaceDisplay(window, player);
    handleInput(window, deltaTime, gameState, sound, background, player, building, helicopter, plane, score, isFullscreen, screenWidth, screenHeight);
    selectTimer += deltaTime;

    // Menu navigation
    if(menuSelect == 0){
        fullscreenText.setFillColor(sf::Color{255,255,0,230});
        volumeText.setFillColor(sf::Color{255,255,255,230});
        backText.setFillColor(sf::Color{255,255,255,230});
        }

    if(menuSelect == 1){
        fullscreenText.setFillColor(sf::Color{255,255,255,230});
        volumeText.setFillColor(sf::Color{255,255,0,230});
        backText.setFillColor(sf::Color{255,255,255,230});
        }

    if(menuSelect == 2){
        fullscreenText.setFillColor(sf::Color{255,255,255,230});
        volumeText.setFillColor(sf::Color{255,255,255,230});
        backText.setFillColor(sf::Color{255,255,0,230});
        }

    window.draw(titleText);
    window.draw(fullscreenText);
    window.draw(volumeText);
    window.draw(backText);
}

void Menu::tryUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, Score& score, int& isFullscreen, int screenHeight){
    handleInput(window, deltaTime, gameState, sound, background, player, building, helicopter, plane, score, isFullscreen, screenWidth, screenHeight);
    selectTimer += deltaTime;

    // Menu navigation
    if(menuSelect == 0){
        retryText.setFillColor(sf::Color{255,255,0,230});
        menuText.setFillColor(sf::Color{255,255,255,230});
        quit2Text.setFillColor(sf::Color{255,255,255,230});
        }

    if(menuSelect == 1){
        retryText.setFillColor(sf::Color{255,255,255,230});
        menuText.setFillColor(sf::Color{255,255,0,230});
        quit2Text.setFillColor(sf::Color{255,255,255,230});
        }

    if(menuSelect == 2){
        retryText.setFillColor(sf::Color{255,255,255,230});
        menuText.setFillColor(sf::Color{255,255,255,230});
        quit2Text.setFillColor(sf::Color{255,255,0,230});
        }

    versionText.setFillColor(sf::Color{255,255,255,70});

    window.draw(retryText);
    window.draw(menuText);
    window.draw(quit2Text);
    }

void Menu::handleInput(sf::RenderWindow& window, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, Score& score, int& isFullscreen, int screenWidth, int screenHeight){
    if(window.hasFocus()){
    // UP AND DOWN CONTROLS

    // Down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && selectTimer > 0.2f){
        if(gameState == 0){
            menuSelect = ((menuSelect + 1)%4 + 4) % 4;
        } else{
            menuSelect = ((menuSelect + 1)%3 + 3) % 3;
            }

        resetSelection(score, background, plane, helicopter, player);
        selectTimer = 0.0f;
        sound.menuSound();
        }

    // Up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && selectTimer > 0.2f){
        if(gameState == 0){
            menuSelect = ((menuSelect - 1)%4 + 4) % 4;
        } else{
            menuSelect = ((menuSelect - 1)%3 + 3 ) % 3; // C++ modulo doesn't work w/ negative numbers, so made our own
            }

        selectTimer = 0.0f;
        sound.menuSound();
        resetSelection(score, background, plane, helicopter, player);
        }

    // ALL MENU SELECTION - pressing enter

    // On menu
    if(gameState == 0){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && selectTimer > 0.2f){ // If Enter is pressed
            if(menuSelect == 0){ // if we press enter on play
                background.resetGame();
                player.resetGame(gameState);
                building.resetGame(score);
                helicopter.resetGame();
                plane.resetGame();
                sound.startSound();
                gameState = 1;

                score.current_score = 0;
            }

            if(menuSelect == 1){ // if we press enter on customise
                sound.menuSound();
                gameState = 2;
                menuSelect = 0;
                selectTimer = 0;
            }


            if(menuSelect == 2){ // if we press settings
                sound.menuSound();
                gameState = 3;
                menuSelect = 0;
                selectTimer = 0;
            }

            if(menuSelect == 3){ // if we press quit
                window.close();
            }
        }
    }

    // On customisation
    if(gameState == 2 ){

        // CHANGING PLAYER AND THEME
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && selectTimer > 0.2f){ // If press left
            if(menuSelect == 0){ // On player
                playerSelect = ((playerSelect + 1)%5 + 5) % 5;
                selectTimer = 0;
                playerChange(player, background, score);
                sound.menuSound();
                }
            if(menuSelect == 1){
                themeSelect = ((themeSelect + 1)%5 + 5) % 5;
                selectTimer = 0;
                themeChange(player, background, score, building, plane, helicopter);
                sound.menuSound();
                }
            }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && selectTimer > 0.2f){ // If press right
            if(menuSelect == 0){ // On theme
                playerSelect = ((playerSelect - 1)%5 + 5) % 5;
                selectTimer = 0;
                playerChange(player, background, score);
                sound.menuSound();
                }
            if(menuSelect == 1){
                themeSelect = ((themeSelect - 1)%5 + 5) % 5;
                selectTimer = 0;
                themeChange(player, background, score, building, plane, helicopter);
                sound.menuSound();
                }
            }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && selectTimer > 0.2f){ // Press Enter
            if(menuSelect == 2){ // On back
                sound.menuSound();
                menuSelect = 0;
                gameState = 0;
                selectTimer = 0;
                background.writeTheme(); // Update theme text file
                player.writeTheme(); // Update player theme text file
                }
            }
        }

    //On settings
    if(gameState == 3){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && selectTimer > 0.2f){ // have to be separate because of selectTimer > 0.2
            if(menuSelect == 0){ // if we press Enter on  Fullscreen
                if(isFullscreen == 0){
                isFullscreen = 1;
                selectTimer = 0;
                } else{
                if(isFullscreen == 1){
                    isFullscreen = 0;
                    selectTimer = 0;
                    }
                }

                writeFullscreen(isFullscreen);

                window.close(); // restart window
                loadWindow(screenWidth, screenHeight, isFullscreen, window);
                }

            if(menuSelect == 2){ // if we press Enter on Back
                sound.menuSound();
                menuSelect = 0;
                gameState = 0;
              //  volumeWrite();
                std::ofstream writeVolumeFile("Volume.txt"); // Update high score text file
                if(writeVolumeFile.is_open()){
                    writeVolumeFile << sound.volume;
                    }
                writeVolumeFile.close();
                selectTimer = 0;
                }
            }
        if(menuSelect == 1){ // If we press left or right on Volume
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && selectTimer > 0.2f ){
                sound.volume = ((sound.volume - 1)%11 +11 ) % 11;
                sound.menuSound();
                selectTimer = 0;
                }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && selectTimer > 0.2f ){
                sound.volume = ((sound.volume + 1)%11 +11 ) % 11;
                sound.menuSound();
                selectTimer = 0;
                }
            }
    }

    if(gameState == 4){ // IF ON TRY AGAIN MENU. OUR CHOICES ARE RETRY, MENU, QUIT
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && selectTimer > 0.2f){
            if(menuSelect == 0){ // if we press Enter on Retry
                background.resetGame();
                player.resetGame(gameState);
                building.resetGame(score);
                helicopter.resetGame();
                plane.resetGame();

                sound.startSound();
                gameState = 1;

                score.current_score = 0;
            }
            if(menuSelect == 1){ // if we press Enter on Menu
                sound.menuSound();
                gameState = 0;
                menuSelect = 0;
                selectTimer = 0.0f;

            }
            if(menuSelect == 2){ // if we press Enter on Quit
                window.close();
            }
        }
    }
    } // window.hasFocus() close bracket
}

void Menu::holdSpaceDisplay(sf::RenderWindow& window, Player& player){ // Animation "Press space" next to player on menu screen
    holdSpaceText.setPosition(30,150*sin(player.playerTimer) + 440);
    upArrow.setPosition(180,150*sin(player.playerTimer) + 440);

    window.draw(holdSpaceText);

    int spaceTimer = player.playerTimer*1.2;
    if(spaceTimer % 2 == 0){
        window.draw(upArrow);
        }
    }

void Menu::playerChange(Player& player, Background& background, Score& score){ // event-based theme changer in settings
    if(playerSelect == 0){
        player.themeNormal();
        }
    if(playerSelect == 1 && score.high_score >= playerPixelScore){
        player.themePixel();
        }

    if(playerSelect == 2 && score.high_score >= goldScore){
        player.themeGold();
        }
    if(playerSelect == 3 && score.high_score >= origamiScore){
        player.themeOrigami();
        }

    if(playerSelect == 4 && score.high_score >= kingScore){
        player.themeKing();
        }
    }

void Menu::themeChange(Player& player, Background& background, Score& score, Building& building, Plane& plane, Helicopter& helicopter){
    if(themeSelect == 0 && background.Style != 0){ // the double condition prevents the sun resetting when themes aren't unlocked
        background.themeNormal(plane, helicopter);
        score.themeUpdate(background);
        building.themeNormal();
        }
    if(themeSelect == 1 && score.high_score >= pixelScore && background.Style != 1){
        background.themePixel(plane, helicopter);
        score.themeUpdate(background);
        building.themeNormal();
        }
    if(themeSelect == 2 && score.high_score >= sunsetScore && background.Style != 2){
        background.themeSunset(plane, helicopter);
        score.themeUpdate(background);
        building.themeSunset();
        }
    if(themeSelect == 3 && score.high_score >= apocScore && background.Style != 3){
        background.themeApoc(plane, helicopter);
        score.themeUpdate(background);
        building.themeApoc();
        }
    if(themeSelect == 4 && score.high_score >= spaceScore && background.Style != 4){
        background.themeSpace(plane, helicopter);
        score.themeUpdate(background);
        building.themeSpace();
        }

    }

void Menu::resetSelection(Score& score, Background& background, Plane& plane, Helicopter& helicopter, Player& player){ // Resets player and theme selection if they are not unlocked
    if(playerSelect == 1 && score.high_score < playerPixelScore){ // prevents double stacking "score to unlock" text
        playerSelect = 0;
        player.Style = 0;
        }

    if(playerSelect == 2 && score.high_score < goldScore){ // prevents double stacking "score to unlock" text
        playerSelect = 0;
        player.Style = 0;
        }

    if(playerSelect == 3 && score.high_score < origamiScore){ // prevents double stacking "score to unlock" text
        playerSelect = 0;
        player.Style = 0;
        }
    if(playerSelect == 4 && score.high_score < kingScore){ // prevents double stacking "score to unlock" text
        playerSelect = 0;
        player.Style = 0;
        }

    if(themeSelect == 1 && score.high_score < pixelScore){
        themeSelect = 0;
        if(background.Style != 0){
            background.themeNormal(plane, helicopter);
        }
        background.Style = 0;
        }
    if(themeSelect == 2 && score.high_score < sunsetScore){
        themeSelect = 0;
        if(background.Style != 0){
            background.themeNormal(plane, helicopter);
        }
        background.Style = 0;
        }
    if(themeSelect == 3 && score.high_score < apocScore){
        themeSelect = 0;
        if(background.Style != 0){
            background.themeNormal(plane, helicopter);
        }
        background.Style = 0;
        }
    if(themeSelect == 4 && score.high_score < spaceScore){
        themeSelect = 0;
        if(background.Style != 0){
            background.themeNormal(plane, helicopter);
        }
        background.Style = 0;
        }
}

void Menu::writeFullscreen(int& isFullscreen){
    std::ofstream writeFullscreenFile("isFullscreen.txt");
    if(writeFullscreenFile.is_open()){
        writeFullscreenFile << isFullscreen;
        }
    writeFullscreenFile.close();
}

void Menu::readVolume(Sounds& sound){
    std::ifstream readVolumeFile;
    readVolumeFile.open( "Volume.txt" );
    if(readVolumeFile.is_open()){
        std::string contents;
        while(!readVolumeFile.eof()){ // while not at end of file
                readVolumeFile >> contents;
            }
        if(isWholeInteger(contents)){ // check isFullscreen.txt has an integer
            sound.volume = std::stoi(contents);
            if(sound.volume < 0 || sound.volume > 10){ // check integer is valid
                std::cout << "Volume.txt does not equal a integer within range. Setting to 10." << std::endl;
                sound.volume = 10;
                }
            } else{
                std::cout << "Volume.txt does not contain integer value. Setting to 10." << std::endl;
                sound.volume = 10;
            }
        }
    readVolumeFile.close();
}

void Menu::errorScreen(sf::RenderWindow& window){
    window.clear(sf::Color(178,215,255,255));
    window.draw(errorText);
}
