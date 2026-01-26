#pragma once
#ifndef SOUL_LESS_GAME_HPP
#define SOUL_LESS_GAME_HPP


#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();
    sf::Font PixelFont;

private:
    sf::RenderWindow window;
};

#endif