#include "../../include/inventory/InventorySlot.hpp"

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
    if (background.getGlobalBounds().contains(mouseWorld)&& isClicked == false && holdClick==false) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            background.setFillColor(sf::Color(100, 100, 100));
            background.setOutlineColor(sf::Color::Blue);
            isClicked = true;
			holdClick = true;
        }
    }
    else if (isClicked == false) {
        if (holdClick == false){
            background.setOutlineColor(sf::Color::White);
            background.setFillColor(sf::Color(50, 50, 50));
        }
    }
}