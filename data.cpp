#include "data.h"

Data::Data() {
    gameState = 0; // 0 = menu, 1 = play, 2 = customisation, 3 = settings, 4 = try again menu

    gameReset = 0;
    collided = 0;
    dead = 0;

    currentScore = 0;

    screenWidth = 1280;
    screenHeight = 720;

    playerPixelScore = 10;
    playerGoldScore = 20;
    playerOrigamiScore = 30;
    playerKingScore = 40;

    themePixelScore = 10;
    themeSunsetScore = 20;
    themeApocScore = 30;
    themeSpaceScore = 40;

    velRange = 100; // the score higher range for which obstacle velocities increase

    // theme names
    playerThemeMap[0].first = "Normal";
    playerThemeMap[1].first = "Pixel";
    playerThemeMap[2].first = "Gold";
    playerThemeMap[3].first = "Origami";
    playerThemeMap[4].first = "King";

    themeMap[0].first = "Normal";
    themeMap[1].first = "Pixel";
    themeMap[2].first = "Sunset";
    themeMap[3].first = "Apocalypse";
    themeMap[4].first = "Space";

    // theme score requirements
    playerThemeMap[0].second = 0;
    playerThemeMap[1].second = playerPixelScore;
    playerThemeMap[2].second = playerGoldScore;
    playerThemeMap[3].second = playerOrigamiScore;
    playerThemeMap[4].second = playerKingScore;

    themeMap[0].second = 0;
    themeMap[1].second = themePixelScore;
    themeMap[2].second = themeSunsetScore;
    themeMap[3].second = themeApocScore;
    themeMap[4].second = themeSpaceScore;

    volume = 5; // backup if Data.txt is deleted

    readDataTxt();
}

void Data::readDataTxt() {
    int count = 0;
    std::string line;
    std::ifstream fin;
    fin.open("Data.txt");
    if (!fin) {
        std::cout << "Error opening Data.txt (readDataTxt). " << std::endl;
    }
    while (std::getline(fin, line)) {
        switch (count) {
        case 0: // isFullscreen
            if (isWholeInteger(line)) {
                if (std::stoi(line) == 1) {
                    isFullscreen = 1; // if 1, equals 1. If anything else (including invalid), equals 0.
                } else {
                    isFullscreen = 0;
                }
            } else {
                isFullscreen = 0;
                std::cout << "Invalid isFullscreen. Setting to 0." << std::endl;
            }
            break;
        case 1: // volume
            if (isWholeInteger(line)) {
                if (std::stoi(line) > 0 && std::stoi(line) <= 10) {
                    volume = std::stoi(line);
                } else {
                    volume = 5;
                    std::cout << "Invalid volume. Setting to 5." << std::endl;
                }
            } else {
                volume = 5;
                std::cout << "Invalid volume. Setting to 5." << std::endl;
            }
            break;
        case 2: // highscore (encrypted - returns 0 if invalid encryption automatically);
            highScore = decrypt(line);
            break;
        case 3: // playerTheme (encrypted)
            playerTheme = decrypt(line);
            if (highScore < playerThemeMap[playerTheme].second) {
                std::cout << "High score does not match selected playerTheme. Setting to 0." << std::endl;
                playerTheme = 0;
            }
            break;
        case 4: // theme (encrypted)
            theme = decrypt(line);
            if (highScore < themeMap[theme].second) {
                std::cout << "High score does not match selected theme. Setting to 0." << std::endl;
                theme = 0;
            }
            break;
        }
        count++;
    }

    std::cout << isFullscreen << std::endl;
    std::cout << volume << std::endl;
    std::cout << highScore << std::endl;
    std::cout << playerTheme << std::endl;
    std::cout << theme << std::endl;

    fin.close();
}

void Data::changeFullscreen(sf::RenderWindow& window, bool isFullscreen) {
    window.close();

    if (isFullscreen == 1) {
        this->isFullscreen = 1;
        window.create(sf::VideoMode(screenWidth, screenHeight), "Paper Glide", sf::Style::Fullscreen);
    } else {
        this->isFullscreen = 0;
        window.create(sf::VideoMode(screenWidth, screenHeight), "Paper Glide");
    }
}

void Data::writeDataTxt() {
    std::ofstream fout;
    fout.open("Data.txt");
    if (!fout) {
        std::cout << "Error opening Data.txt (writeDataTxt). " << std::endl;
    }
    fout << std::to_string(isFullscreen) << std::endl;
    fout << std::to_string(volume) << std::endl;
    fout << encrypt(highScore) << std::endl;
    fout << encrypt(playerTheme) << std::endl;
    fout << encrypt(theme) << std::endl;

    fout.close();
}