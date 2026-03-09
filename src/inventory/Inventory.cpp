#include "../../include/inventory/Inventory.hpp"

Inventory::Inventory(int r, int c, float size, sf::Vector2f startPos)
    : rows(r), cols(c), slotSize(size), startPosition(startPos)
{
    slots.reserve(rows * cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sf::Vector2f pos(startPos.x + j * (size + 5.f), startPos.y + i * (size + 5.f));
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

bool Inventory::removeSelectedItem(int qty)
{
    if (qty <= 0) {
        return false;
    }

    if (selectedSlotIndex < 0 || selectedSlotIndex >= static_cast<int>(slots.size())) {
        return false;
    }

    InventorySlot& selectedSlot = slots[selectedSlotIndex];
    if (selectedSlot.isEmpty() || selectedSlot.quantity < qty) {
        return false;
    }

    selectedSlot.quantity -= qty;
    if (selectedSlot.quantity <= 0) {
        selectedSlot.itemName.clear();
        selectedSlot.quantity = 0;
    }

    return true;
}

std::string Inventory::getSelectedItemName() const
{
    if (selectedSlotIndex < 0 || selectedSlotIndex >= static_cast<int>(slots.size())) {
        return "";
    }

    const InventorySlot& selectedSlot = slots[selectedSlotIndex];
    return selectedSlot.isEmpty() ? "" : selectedSlot.itemName;
}

const Item* Inventory::getItemData(const std::string& itemName) const
{
    auto it = itemDatabase.find(itemName);
    if (it == itemDatabase.end()) {
        return nullptr;
    }

    return it->second;
}

void Inventory::setStartPosition(const sf::Vector2f& newStartPos)
{
    startPosition = newStartPos;

    int slotIndex = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sf::Vector2f pos(
                startPosition.x + j * (slotSize + 5.f),
                startPosition.y + i * (slotSize + 5.f)
            );

            slots[slotIndex].position = pos;
            slots[slotIndex].background.setPosition(pos);
            ++slotIndex;
        }
    }
}

void Inventory::centerInWindow(const sf::Vector2u& windowSize)
{
    const float spacing = 5.f;
    const float totalWidth = cols * slotSize + (cols - 1) * spacing;
    const float totalHeight = rows * slotSize + (rows - 1) * spacing;

    const sf::Vector2f centeredStart(
        (static_cast<float>(windowSize.x) - totalWidth) * 0.5f,
        (static_cast<float>(windowSize.y) - totalHeight) * 0.5f
    );

    setStartPosition(centeredStart);
}

void Inventory::update(const sf::Vector2f& mouseWorld) {
    const bool leftMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    const bool isFreshLeftClick = leftMouseDown && !wasLeftMouseDown;

    if (isFreshLeftClick) {
        int clickedSlotIndex = -1;
        for (int i = 0; i < static_cast<int>(slots.size()); ++i) {
            if (slots[i].background.getGlobalBounds().contains(mouseWorld)) {
                clickedSlotIndex = i;
                break;
            }
        }

        selectedSlotIndex = clickedSlotIndex;
    }

    for (int i = 0; i < static_cast<int>(slots.size()); ++i) {
        if (i == selectedSlotIndex) {
            slots[i].background.setFillColor(sf::Color::White);
            slots[i].background.setOutlineColor(sf::Color::White);
        }
        else {
            slots[i].background.setFillColor(sf::Color(50, 50, 50));
            slots[i].background.setOutlineColor(sf::Color(90, 90, 90));
        }
    }

    wasLeftMouseDown = leftMouseDown;
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
                sprite.setScale(sf::Vector2f{ slotSize / texSize.x, slotSize / texSize.y });
                window.draw(sprite);
            }
        }
    }
}
