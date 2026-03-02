#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "inventory/Inventory.hpp"

class Game {
public:
    Game();
    void run();

    const sf::Vector2f& getMouseWorld() const;
private:
    sf::RenderWindow window;
    sf::Font Pixelfont;
    Inventory inventory;
    bool inventoryOpen = false;
    sf::Vector2f mouseWorld;
    std::string selectedInventoryItem;
};
