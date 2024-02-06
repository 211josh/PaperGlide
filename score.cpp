#include "score.h"

int Score::current_score = 0;
int Score::high_score = 0;
bool Score::pointAdded = 0;
float Score::velRange = 100; // velRange = score for sprites to hit max velocities

Score::Score(){
if(!font.loadFromFile("sprites/Font.ttf")){
    std::cout << "Could not load Score font";
    }
    // Play state Score display properties
    playScore.setFont(font); // Score behind screen
    playScore.setCharacterSize(300);
    playScore.setColor(sf::Color{200,223,255,200}); // r g b occupancy/255
    playScore.setOrigin(sf::Vector2f(0.0f,0.0f));
    playScore.setString(std::to_string(current_score));

    // Try again state Score display properties
    tryScore.setFont(font); // Score on try again screen
    tryScore.setCharacterSize(150);
    tryScore.setColor(sf::Color{200,223,255,200});
    tryScore.setOrigin(sf::Vector2f(0.0f,0.0f));

    // High Score display
    highScore.setFont(font);
    highScore.setCharacterSize(100);
    highScore.setColor(sf::Color{200,223,255,200});
    highScore.setOrigin(sf::Vector2f(0.0f,0.0f));

    std::ifstream readFile;
    readFile.open( "Highscore.txt" );
    if(readFile.is_open()){
        while(!readFile.eof()){ // while not at end of file
                readFile >> high_score; // high score is equal to the contents of the file
            }
        }
    readFile.close();
    }

void Score::update(sf::RenderWindow& window, int screenWidth, int screenHeight, Sounds& sound, Background& background, Helicopter& helicopter, Plane& plane, Building& building, float deltaTime){
    displayPlayScore(window, screenWidth);
    checkScore(sound, background, helicopter, plane, building, deltaTime);
    }

void Score::tryUpdate(sf::RenderWindow& window, int screenWidth, int screenHeight){
    displayTryScore(window, screenWidth);
    }

void Score::addScore(Sounds& sound, Background& background, Helicopter& helicopter, Plane& plane, Building& building){
    current_score += 1;
    sound.pointSound(); // Play score point sound

    // Increase in score increases velocities of sprites
    if(current_score < velRange){
        background.increaseVel(velRange);
        helicopter.increaseVel(velRange);
        plane.increaseVel(velRange);
        building.increaseVel(velRange);
        }
    }

void Score::checkScore(Sounds& sound, Background& background, Helicopter& helicopter, Plane& plane, Building& building, float deltaTime){ // Check position of building to see if point can be added
    sf::Vector2f position = building.getPos();
    if(position.x < 100 && pointAdded == 0){
        addScore(sound,background,helicopter,plane,building);
        pointAdded = 1;
        }
    }

void Score::displayPlayScore(sf::RenderWindow& window, int screenWidth){
    sf::FloatRect textBounds = playScore.getLocalBounds(); // Position is continuously updated as the text width changes
    playScore.setString(std::to_string(current_score));
    playScore.setPosition((screenWidth - textBounds.width) / 2, 100); // Centres text based on text and screen width
    window.draw(playScore);
    }

void Score::displayTryScore(sf::RenderWindow& window, int screenWidth){
    tryScore.setString("Score: " + std::to_string(current_score));
    sf::FloatRect tryScoreBounds = tryScore.getLocalBounds();
    tryScore.setPosition((screenWidth - tryScoreBounds.width) / 2, 100); // Centres text based on text and screen width
    window.draw(tryScore);
    }

void Score::displayHighScore(sf::RenderWindow& window, int screenWidth){
    if(current_score > high_score){
        high_score = current_score;

        std::ofstream writeFile("Highscore.txt"); // Update high score text file
        if(writeFile.is_open()){
            writeFile << high_score;
            }
        writeFile.close();

        }

    highScore.setString("High Score: " + std::to_string(high_score));
    sf::FloatRect highScoreBounds = highScore.getLocalBounds();
    highScore.setPosition((screenWidth - highScoreBounds.width) / 2, 25); // Centres text based on text and screen width
    window.draw(highScore);
    }
