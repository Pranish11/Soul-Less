#include "../include/InventorySlot.hpp"

InventorySlot::InventorySlot(sf::Vector2f pos, sf::Vector2f size)
    : itemName(""), quantity(0), position(pos) {
    background.setSize(size);
    background.setPosition(pos);
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineThickness(2.f);
    background.setOutlineColor(sf::Color::White);
}

bool InventorySlot::isEmpty() {
    return itemName.empty();
}