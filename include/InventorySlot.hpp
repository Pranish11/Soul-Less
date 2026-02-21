#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class InventorySlot {
public:
    InventorySlot();
    InventorySlot(sf::Vector2f pos, sf::Vector2f size);

    void update(const sf::Vector2f& mouseWorld);
    bool isEmpty() const;

    std::string itemName;
    int quantity;
    sf::RectangleShape background;
    sf::Vector2f position;
};