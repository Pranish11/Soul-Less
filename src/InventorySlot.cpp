#include "../include/InventorySlot.hpp"

InventorySlot::InventorySlot(sf::Vector2f IvPos, sf::Vector2f size)
	: quantity(0), InvPosition(IvPos), item(nullptr)
{
	slotShape.setSize(size);
	slotShape.setFillColor(sf::Color(100, 100, 100)); // Gray color for empty slot
	slotShape.setOutlineColor(sf::Color::Black);
	slotShape.setOutlineThickness(2.f);
	slotShape.setPosition(InvPosition);
}

bool InventorySlot::isEmpty() {
	return item == nullptr;
}