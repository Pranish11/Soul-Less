#include "../include/Inventory.hpp"

Inventory::Inventory(int r, int c, float size, sf::Vector2f startPos)
    : rows(r), cols(c), slotSize(size), startPosition(startPos) {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sf::Vector2f pos(
                startPos.x + j * (size + 5.f),
                startPos.y + i * (size + 5.f)
            );
            slots.push_back(InventorySlot(pos, sf::Vector2f(size, size)));
        }
    }
}

void Inventory::registerItem(Item* item) {
    itemDatabase[item->name] = item;
}

bool Inventory::addItem(std::string itemName, int qty) {
    // Check if item exists in database
    if (itemDatabase.find(itemName) == itemDatabase.end()) {
        return false;
    }

    Item* itemType = itemDatabase[itemName];

    // Try to stack with existing items first
    for (auto& slot : slots) {
        if (!slot.isEmpty() && slot.itemName == itemName) {
            if (slot.quantity < itemType->stackSize) {
                slot.quantity += qty;
                return true;
            }
        }
    }

    // Find empty slot
    for (auto& slot : slots) {
        if (slot.isEmpty()) {
            slot.itemName = itemName;
            slot.quantity = qty;
            return true;
        }
    }
    return false;
}

void Inventory::draw(sf::RenderWindow& window) {
    for (auto& slot : slots) {
        window.draw(slot.background);

        if (!slot.isEmpty()) {
            Item* item = itemDatabase[slot.itemName];

            // Create a temporary sprite for this slot
            if (item->sprite && item->texture) {
                sf::Sprite tempSprite(*item->texture);
                tempSprite.setPosition(slot.position);

                // Scale to fit slot using texture size
                auto texSize = item->texture->getSize();
                tempSprite.setScale({
                    slotSize / texSize.x,
                    slotSize / texSize.y
                });

                window.draw(tempSprite);
            }
        }
    }
}
