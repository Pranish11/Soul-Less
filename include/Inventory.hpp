#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "InventorySlot.hpp"

class Inventory {
public:
	Inventory(int r, int c, float size, sf::Vector2f StartPos);
	void draw(sf::RenderWindow& window);
	bool addItem(Item* item, int quantity);

private :
	std::vector<InventorySlot> slots;
	int rows, cols;
	float slotSize;
	sf::Vector2f startPosition;
};