#pragma once
#ifndef PROJECT_2_GAME_HPP
#define PROJECT_2_GAME_HPP

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
};

#endif