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

bool Inventory::addItem(Item* newItem, int qty) {
    // Try to stack with existing items first
    for (auto& slot : slots) {
        if (!slot.isEmpty() && slot.item->name == newItem->name) {
            if (slot.quantity < slot.item->stackSize) {
                slot.quantity += qty;
                return true;
            }
        }
    }

    // Find empty slot
    for (auto& slot : slots) {
        if (slot.isEmpty()) {
            slot.item = newItem;
            slot.quantity = qty;
            return true;
        }
    }
    return false;
}

void Inventory::draw(sf::RenderWindow& window) {
    for (auto& slot : slots) {
        window.draw(slot.slotShape);

        if (!slot.isEmpty() && slot.item->sprite && slot.item->texture) {
            slot.item->sprite->setPosition(slot.InvPosition);

            // Scale sprite to fit slot using texture size
            auto texSize = slot.item->texture->getSize();
            slot.item->sprite->setScale({
                slotSize / texSize.x,
                slotSize / texSize.y
            });
            window.draw(*slot.item->sprite);
        }
    }
}