#pragma once

#include <SFML/Graphics.hpp>

class Pause {
public:
    Pause(const sf::Font& f);
    void PauseDraw(sf::RenderWindow& window);
    bool isPaused = false;

private:
    const sf::Font& Pixelfont;
    sf::RectangleShape Continue;
    sf::RectangleShape Save;
    sf::RectangleShape Exit;
};
