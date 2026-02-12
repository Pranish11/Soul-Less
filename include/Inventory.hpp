#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "InventorySlot.hpp"
#include "Item.hpp"

class Inventory {
private:
    std::vector<InventorySlot> slots;
    std::map<std::string, Item*> itemDatabase;  // Reference to all item types
    int rows, cols;
    float slotSize;
    sf::Vector2f startPosition;

public:
    Inventory(int r, int c, float size, sf::Vector2f startPos);
    void registerItem(Item* item);  // Add item type to database
    bool addItem(std::string itemName, int qty = 1);
    void draw(sf::RenderWindow& window);
};