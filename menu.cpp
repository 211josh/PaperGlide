#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "menu.h"

sf::Sprite Menu::upArrow;

// Scores required for unlocks
int origamiScore = 1;
int goldScore = 100;
int player4Score = 1;
int kingScore = 1;

int medivalScore = 25;
int sunsetScore = 50;
int apocScore = 75;
int spaceScore = 100;

Menu::Menu(int screenWidth, Score& score, Background& background){
    if(!font.loadFromFile("sprites/Font.ttf")){
        std::cout << "Could not load Menu font";
    }
    if(!arrowTexture.loadFromFile("sprites/upArrow.png")){
        std::cout << "Could not load upArrow font";
    }

    readVolume();

    menuSelect = 0; // Menu opens on play option
    playerSelect = Player::Style; //CHANGE THIS TO OPEN AND READ FILE
    themeSelect = Background::Style; // CHANGE THIS TO OPEN AND READ FILE

    resetSelection(score, background);

    selectTimer = 0; // Min time wait between changing menu option. Prevents endless fast scrolling.

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
    holdSpaceText.setColor(sf::Color{255,255,255,200});
    holdSpaceText.setOrigin(sf::Vector2f(0.0f,0.0f));

    // Up arrow
    upArrow.setTexture(arrowTexture);
    upArrow.setColor(sf::Color{255,255,255,200});
    }


void Menu::menuUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, Score& score, int& isFullscreen, int screenHeight){

    holdSpaceDisplay(window, player);
    handleInput(window, deltaTime, gameState, sound, background, player, building, helicopter, plane, Score::current_score, score, isFullscreen, screenWidth, screenHeight);
    selectTimer += deltaTime;

    if(menuSelect == 0){ // if on play
        playText.setColor(sf::Color{255,255,0,230});
        customiseText.setColor(sf::Color{255,255,255,230});
        settingsText.setColor(sf::Color{255,255,255,230});
        quitText.setColor(sf::Color{255,255,255,230});
        }

    if(menuSelect == 1){ // if on customise
        playText.setColor(sf::Color{255,255,255,230});
        customiseText.setColor(sf::Color{255,255,0,230});
        settingsText.setColor(sf::Color{255,255,255,230});
        quitText.setColor(sf::Color{255,255,255,230});

    }

    if(menuSelect == 2){ // if on settings
        playText.setColor(sf::Color{255,255,255,230});
        customiseText.setColor(sf::Color{255,255,255,230});
        settingsText.setColor(sf::Color{255,255,0,230});
        quitText.setColor(sf::Color{255,255,255,230});
        }

    if(menuSelect == 3){ // if on quit
        playText.setColor(sf::Color{255,255,255,230});
        customiseText.setColor(sf::Color{255,255,255,230});
        settingsText.setColor(sf::Color{255,255,255,230});
        quitText.setColor(sf::Color{255,255,0,230});
        }

    versionText.setColor(sf::Color{255,255,255,70});

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
    handleInput(window, deltaTime, gameState, sound, background, player, building, helicopter, plane, Score::current_score, score, isFullscreen, screenWidth, screenHeight);
    selectTimer += deltaTime;

    playerText.setCharacterSize(90);
    themeText.setCharacterSize(90);
    unlockText.setCharacterSize(40);

    sf::FloatRect playerBounds = playerText.getLocalBounds();
    sf::FloatRect themeBounds = themeText.getLocalBounds();
    sf::FloatRect unlockBounds = unlockText.getLocalBounds();

    playerText.setPosition((screenWidth - playerBounds.width)/2, 240);
    themeText.setPosition((screenWidth - themeBounds.width)/2, 320);
    unlockText.setPosition((screenWidth - unlockBounds.width)/2, 500);

    // Menu navigation
    if(menuSelect == 0){ // if on player theme
        playerText.setColor(sf::Color{255,255,0,230});
        themeText.setColor(sf::Color{255,255,255,230});
        backText.setColor(sf::Color{255,255,255,230});
        }

    if(menuSelect == 1){ // if on theme
        playerText.setColor(sf::Color{255,255,255,230});
        themeText.setColor(sf::Color{255,255,0,230});
        backText.setColor(sf::Color{255,255,255,230});
    }

    if(menuSelect == 2){ // if on back
        playerText.setColor(sf::Color{255,255,255,230});
        themeText.setColor(sf::Color{255,255,255,230});
        backText.setColor(sf::Color{255,255,0,230});
        }

    // Changing player
    if(playerSelect == 0){
        playerText.setString("< Player: Normal >");
        }
    if(playerSelect == 1){
        playerText.setString("< Player: Origami >");
        if(Score::high_score < origamiScore){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(origamiScore) + " points to unlock!");
            playerText.setColor({255,0,0,230});
            window.draw(unlockText);
            }
        }
    if(playerSelect == 2){
        playerText.setString("< Player: Gold >");
        if(Score::high_score < goldScore){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(goldScore) + " points to unlock!");
            playerText.setColor({255,0,0,230});
            window.draw(unlockText);
            }
        }
    if(playerSelect == 3){
        playerText.setString("< Player: 4 >");
        if(Score::high_score < player4Score){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(player4Score) + " points to unlock!");
            playerText.setColor({255,0,0,230});
            window.draw(unlockText);
            }
        }
    if(playerSelect == 4){
        playerText.setString("< Player: King >");
        if(Score::high_score < kingScore){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(kingScore) + " points to unlock!");
            playerText.setColor({255,0,0,230});
            window.draw(unlockText);
            }
        }

    // Changing theme
    if(themeSelect == 0){
        themeText.setString(" < Theme: Normal > ");
    }
    if(themeSelect == 1){
        themeText.setString(" < Theme: Medival >");
        if(Score::high_score < medivalScore){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(medivalScore) + " points to unlock!");
            themeText.setColor({255,0,0,230});
            window.draw(unlockText);
        }
    }
    if(themeSelect == 2){
        themeText.setString(" < Theme: Pink Sunset >");
        if(Score::high_score < sunsetScore){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(sunsetScore) + " points to unlock!");
            themeText.setColor({255,0,0,230});
            window.draw(unlockText);
        }
    }
    if(themeSelect == 3){
        themeText.setString(" < Theme: Apocalypse >");
        if(Score::high_score < apocScore){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(apocScore) + " points to unlock!");
            themeText.setColor({255,0,0,230});
            window.draw(unlockText);
        }
    }
    if(themeSelect == 4){
        themeText.setString(" < Theme: Space >");
        if(Score::high_score < spaceScore){ // i.e it's not unlocked
            unlockText.setString("Score " + std::to_string(spaceScore) + " points to unlock!");
            themeText.setColor({255,0,0,230});
            window.draw(unlockText);
        }
    }

    window.draw(playerText);
    window.draw(themeText);
    window.draw(backText);
    }

void Menu::settingsUpdate(sf::RenderWindow& window, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, int& current_score, Score& score, int screenWidth, int& isFullscreen, int screenHeight){

    // Fullscreen text
    if(isFullscreen == 1){
        fullscreenText.setString("Windowed");
        } else{
        fullscreenText.setString("Fullscreen");
        }
    fullscreenText.setCharacterSize(90);
    sf::FloatRect fullscreenBounds = fullscreenText.getLocalBounds(); // Retrieve menu option bounds
    fullscreenText.setPosition((screenWidth - fullscreenBounds.width) / 2, 240); // Centres text based on text and screen width

    volumeText.setString("< Volume: " + std::to_string(Sounds::volume) + " >");
    sf::FloatRect volumeTextBounds = volumeText.getLocalBounds();
    volumeText.setPosition((screenWidth - volumeTextBounds.width) / 2, 320);

    holdSpaceDisplay(window, player);
    handleInput(window, deltaTime, gameState, sound, background, player, building, helicopter, plane, current_score, score, isFullscreen, screenWidth, screenHeight);
    selectTimer += deltaTime;

    // Menu navigation
    if(menuSelect == 0){
        fullscreenText.setColor(sf::Color{255,255,0,230});
        volumeText.setColor(sf::Color{255,255,255,230});
        backText.setColor(sf::Color{255,255,255,230});
        }

    if(menuSelect == 1){
        fullscreenText.setColor(sf::Color{255,255,255,230});
        volumeText.setColor(sf::Color{255,255,0,230});
        backText.setColor(sf::Color{255,255,255,230});
        }

    if(menuSelect == 2){
        fullscreenText.setColor(sf::Color{255,255,255,230});
        volumeText.setColor(sf::Color{255,255,255,230});
        backText.setColor(sf::Color{255,255,0,230});
        }

    window.draw(titleText);
    window.draw(fullscreenText);
    window.draw(volumeText);
    window.draw(backText);
}

void Menu::tryUpdate(sf::RenderWindow& window, int screenWidth, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, int& current_score, Score& score, int& isFullscreen, int screenHeight){
    handleInput(window, deltaTime, gameState, sound, background, player, building, helicopter, plane, current_score, score, isFullscreen, screenWidth, screenHeight);
    selectTimer += deltaTime;

    // Menu navigation
    if(menuSelect == 0){
        retryText.setColor(sf::Color{255,255,0,230});
        menuText.setColor(sf::Color{255,255,255,230});
        quit2Text.setColor(sf::Color{255,255,255,230});
        }

    if(menuSelect == 1){
        retryText.setColor(sf::Color{255,255,255,230});
        menuText.setColor(sf::Color{255,255,0,230});
        quit2Text.setColor(sf::Color{255,255,255,230});
        }

    if(menuSelect == 2){
        retryText.setColor(sf::Color{255,255,255,230});
        menuText.setColor(sf::Color{255,255,255,230});
        quit2Text.setColor(sf::Color{255,255,0,230});
        }

    versionText.setColor(sf::Color{255,255,255,70});

    window.draw(retryText);
    window.draw(menuText);
    window.draw(quit2Text);
    }

void Menu::handleInput(sf::RenderWindow& window, float deltaTime, int& gameState, Sounds& sound, Background& background, Player& player, Building& building, Helicopter& helicopter, Plane& plane, int& current_score, Score& score, int& isFullscreen, int screenWidth, int screenHeight){
    if(window.hasFocus()){
    // UP AND DOWN CONTROLS

    // Down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && selectTimer > 0.2f){
        if(gameState == 0){
            menuSelect = ((menuSelect + 1)%4 + 4) % 4;
        } else{
            menuSelect = ((menuSelect + 1)%3 + 3) % 3;
            }

        resetSelection(score, background);
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
        resetSelection(score, background);
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

                Score::current_score = 0;
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
                themeChange(player, background, score, building);
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
                themeChange(player, background, score, building);
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
                    writeVolumeFile << Sounds::volume;
                    }
                writeVolumeFile.close();
                selectTimer = 0;
                }
            }
        if(menuSelect == 1){ // If we press left or right on Volume
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && selectTimer > 0.2f ){
                Sounds::volume = ((Sounds::volume - 1)%11 +11 ) % 11;
                sound.menuSound();
                selectTimer = 0;
                }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && selectTimer > 0.2f ){
                Sounds::volume = ((Sounds::volume + 1)%11 +11 ) % 11;
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

                Score::current_score = 0;
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
    holdSpaceText.setPosition(30,150*sin(Player::playerTimer) + 440);
    upArrow.setPosition(180,150*sin(Player::playerTimer) + 440);

    window.draw(holdSpaceText);

    int spaceTimer = Player::playerTimer*1.2;
    if(spaceTimer % 2 == 0){
        window.draw(upArrow);
        }
    }

void Menu::playerChange(Player& player, Background& background, Score& score){ // event-based theme changer in settings
    if(playerSelect == 0){
        player.themeNormal();
        }
    if(playerSelect == 1 && Score::high_score >= origamiScore){
        player.themeOrigami();
        }

    if(playerSelect == 2 && Score::high_score >= goldScore){
        player.themeGold();
        }

    if(playerSelect == 4 && Score::high_score >= kingScore){
        player.themeKing();
        }
    }

void Menu::themeChange(Player& player, Background& background, Score& score, Building& building){
    if(themeSelect == 0 && Background::Style != 0){ // the double condition prevents the sun resetting when themes aren't unlocked
        background.themeNormal();
        score.themeUpdate();
        building.themeNormal();
        }
    if(themeSelect == 1 && Score::high_score >= medivalScore && Background::Style != 1){
        background.themeMedival();
        score.themeUpdate();
        building.themeMedival();
        }
    if(themeSelect == 2 && Score::high_score >= sunsetScore && Background::Style != 2){
        background.themeSunset();
        score.themeUpdate();
        building.themeSunset();
        }
    if(themeSelect == 3 && Score::high_score >= apocScore && Background::Style != 3){
        background.themeApoc();
        score.themeUpdate();
        building.themeApoc();
        }
    if(themeSelect == 4 && Score::high_score >= spaceScore && Background::Style != 4){
        background.themeSpace();
        score.themeUpdate();
        }

    }

void Menu::resetSelection(Score& score, Background& background){ // Resets player and theme selection if they are not unlocked
    if(playerSelect == 1 && Score::high_score < origamiScore){ // prevents double stacking "score to unlock" text
        playerSelect = 0;
        Player::Style = 0;
        }
    if(playerSelect == 2 && Score::high_score < goldScore){ // prevents double stacking "score to unlock" text
        playerSelect = 0;
        Player::Style = 0;
        }
    if(playerSelect == 3 && Score::high_score < player4Score){ // prevents double stacking "score to unlock" text
        playerSelect = 0;
        Player::Style = 0;
        }
    if(playerSelect == 4 && Score::high_score < kingScore){ // prevents double stacking "score to unlock" text
        playerSelect = 0;
        Player::Style = 0;
        }

    if(themeSelect == 1 && Score::high_score < medivalScore){
        themeSelect = 0;
        Background::Style = 0;
        background.themeNormal();
        }
    if(themeSelect == 2 && Score::high_score < sunsetScore){
        themeSelect = 0;
        Background::Style = 0;
        background.themeNormal();
        }
    if(themeSelect == 3 && Score::high_score < apocScore){
        themeSelect = 0;
        Background::Style = 0;
        background.themeNormal();
        }
    if(themeSelect == 4 && Score::high_score < spaceScore){
        themeSelect = 0;
        Background::Style = 0;
        background.themeNormal();
        }
}

void Menu::writeFullscreen(int& isFullscreen){
    std::ofstream writeFullscreenFile("isFullscreen.txt");
    if(writeFullscreenFile.is_open()){
        writeFullscreenFile << isFullscreen;
        }
    writeFullscreenFile.close();
}

void Menu::readVolume(){
    std::ifstream readVolumeFile;
    readVolumeFile.open( "Volume.txt" );
    if(readVolumeFile.is_open()){
        std::string contents;
        while(!readVolumeFile.eof()){ // while not at end of file
                readVolumeFile >> contents;
   //             readVolumeFile >> Sounds::volume; // high score is equal to the contents of the file
            }
        if(isWholeInteger(contents)){ // check isFullscreen.txt has an integer
            Sounds::volume = std::stoi(contents);
            if(Sounds::volume < 0 || Sounds::volume > 10){ // check integer is valid
                std::cout << "Volume.txt does not equal a integer within range. Setting to 10." << std::endl;
                Sounds::volume = 10;
                }
            } else{
                std::cout << "Volume.txt does not contain integer value. Setting to 10." << std::endl;
                Sounds::volume = 10;
            }
        }
    readVolumeFile.close();
}
