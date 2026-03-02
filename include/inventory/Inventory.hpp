#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>

#include "InventorySlot.hpp"
#include "../items/item.hpp"

class Inventory {
private:
    std::vector<InventorySlot> slots;
    std::map<std::string, Item*> itemDatabase;

    int rows, cols;
    float slotSize;
    sf::Vector2f startPosition;
    int selectedSlotIndex = -1;
    bool wasLeftMouseDown = false;

public:
    Inventory(int r, int c, float size, sf::Vector2f startPos);

    void registerItem(Item* item);
    bool addItem(const std::string& itemName, int qty = 1);
    std::string getSelectedItemName() const;

    void setStartPosition(const sf::Vector2f& newStartPos);
    void centerInWindow(const sf::Vector2u& windowSize);

    void update(const sf::Vector2f& mouseWorld);
    void draw(sf::RenderWindow& window);
};
