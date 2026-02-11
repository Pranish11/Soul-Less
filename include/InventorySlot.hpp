#pragma once
#include <SFML/Graphics.hpp>
#include "Item.hpp"
class InventorySlot {
public:
	int quantity;
	sf::RectangleShape slotShape;
	sf::Vector2f InvPosition;
	Item* item;

	InventorySlot(sf::Vector2f IvPos, sf::Vector2f size);
	bool isEmpty();

};