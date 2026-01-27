#pragma once
#ifndef SOUL_LESS_PAUSE_HPP
#define SOUL_LESS_PAUSE_HPP

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

#endif