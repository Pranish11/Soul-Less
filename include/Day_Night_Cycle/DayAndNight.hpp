#pragma once
#include "SFML/Graphics.hpp"

class DayAndNight {
public:
    DayAndNight();
    void update();
    void draw(sf::RenderWindow& window);

private:
    sf::Clock dayNightClock;
    float progress;
    float daylenght;
    std::uint8_t alpha;

    sf::Texture dayTexture;
    sf::Texture nightTexture;

    sf::Sprite daySprite;
    sf::Sprite nightSprite;

    sf::RectangleShape nightOverlay;
};