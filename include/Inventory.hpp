#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>

#include "InventorySlot.hpp"
#include "Item.hpp"

class Inventory {
private:
    std::vector<InventorySlot> slots;
    std::map<std::string, Item*> itemDatabase;

    int rows, cols;
    float slotSize;
    sf::Vector2f startPosition;

public:
    Inventory(int r, int c, float size, sf::Vector2f startPos);

    void registerItem(Item* item);
    bool addItem(const std::string& itemName, int qty = 1);

    void update(const sf::Vector2f& mouseWorld);
    void draw(sf::RenderWindow& window);
};