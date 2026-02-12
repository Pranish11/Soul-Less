#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class InventorySlot {
public:
    std::string itemName;  
    int quantity;
    sf::RectangleShape background;
    sf::Vector2f position;

    InventorySlot(sf::Vector2f pos, sf::Vector2f size);
    bool isEmpty();
};