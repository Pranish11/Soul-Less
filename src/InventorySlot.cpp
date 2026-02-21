#include "../include/InventorySlot.hpp"

InventorySlot::InventorySlot()
    : itemName(""), quantity(0), position(0.f, 0.f)
{
    background.setSize({ 64.f, 64.f });
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineThickness(2.f);
    background.setOutlineColor(sf::Color::White);
}

InventorySlot::InventorySlot(sf::Vector2f pos, sf::Vector2f size)
    : itemName(""), quantity(0), position(pos)
{
    background.setSize(size);
    background.setPosition(pos);
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineThickness(2.f);
    background.setOutlineColor(sf::Color::White);
}

bool InventorySlot::isEmpty() const {
    return itemName.empty();
}

void InventorySlot::update(const sf::Vector2f& mouseWorld)
{
    if (background.getGlobalBounds().contains(mouseWorld)) {
        background.setOutlineColor(sf::Color::Blue);
    }
    else {
        background.setOutlineColor(sf::Color::White);
    }
}