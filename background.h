#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

class Background{
public:
    Background();
    void update(sf::RenderWindow& window, float deltaTime);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    static sf::Vector2f velocity; // Initial velocity

    void movement(float deltaTime);
    void resetPos();
};

#endif // BACKGROUND_H_INCLUDED
