#include "../include/Inventory.hpp"

Inventory::Inventory(int r, int c, float size, sf::Vector2f startPos): rows(r), cols(c), slotSize(size), startPosition(startPos)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sf::Vector2f pos(startPos.x + j * (size + 5.f),startPos.y + i * (size + 5.f));
            slots.emplace_back(pos, sf::Vector2f(size, size));
        }
    }
}

void Inventory::registerItem(Item* item) {
    itemDatabase[item->name] = item;
}

bool Inventory::addItem(const std::string& itemName, int qty) {
    if (itemDatabase.find(itemName) == itemDatabase.end())
        return false;

    Item* itemType = itemDatabase[itemName];

    for (auto& slot : slots) {
        if (!slot.isEmpty() && slot.itemName == itemName) {
            if (slot.quantity + qty <= itemType->stackSize) {
                slot.quantity += qty;
                return true;
            }
        }
    }
    
    for (auto& slot : slots) {
        if (slot.isEmpty()) {
            slot.itemName = itemName;
            slot.quantity = qty;
            return true;
        }
    }
    return false;
}

void Inventory::update(const sf::Vector2f& mouseWorld) {
    for (auto& slot : slots) {
        slot.update(mouseWorld);
    }
}

void Inventory::draw(sf::RenderWindow& window) {
    for (auto& slot : slots) {
        window.draw(slot.background);

        if (!slot.isEmpty()) {
            Item* item = itemDatabase[slot.itemName];
            if (item && item->texture) {
                sf::Sprite sprite(*item->texture);
                sprite.setPosition(slot.position);

                auto texSize = item->texture->getSize();
                sprite.setScale(sf::Vector2f{ slotSize / texSize.x,slotSize / texSize.y });
                window.draw(sprite);
            }
        }
    }
}