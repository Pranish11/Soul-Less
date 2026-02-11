#pragma once
#ifndef SOUL_LESS_GAME_HPP
#define SOUL_LESS_GAME_HPP

#include <SFML/Graphics.hpp>
#include "Inventory.hpp"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Font Pixelfont;
    Inventory inventory;
    bool inventoryOpen = false;
};

#endif