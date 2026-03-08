#include "../../include/inventory/InventoryManager.hpp"

#include "../../include/inventory/Inventory.hpp"

bool InventoryManager::registerItem(Inventory& inventory, const std::string& itemName, const std::string& texturePath, int maxStack)
{
    if (itemRegistry.contains(itemName)) {
        return false;
    }

    auto item = std::make_unique<Item>(itemName, texturePath, maxStack);
    if (!item->texture || item->texture->getSize().x == 0u || item->texture->getSize().y == 0u) {
        return false;
    }

    inventory.registerItem(item.get());
    itemRegistry.emplace(itemName, std::move(item));
    return true;
}

void InventoryManager::registerDefaultItems(Inventory& inventory)
{
    registerItem(inventory, "TestChair", "assets/ItemTextures/TestImage.png");
    registerItem(inventory, "Bed", "assets/ItemTextures/Bed.png");
    registerItem(inventory, "Table", "assets/ItemTextures/Table.png");
    registerItem(inventory, "Coke", "assets/ItemTextures/coke_table.png");
    registerItem(inventory, "Chemical", "assets/ItemTextures/chemical_table.png");
    registerItem(inventory, "B_Weed","assets/ItemTextures/Better_Weed.png");

}

bool InventoryManager::giveItem(Inventory& inventory, const std::string& itemName, int qty) const
{
    if (!hasItemDefinition(itemName)) {
        return false;
    }

    return inventory.addItem(itemName, qty);
}

bool InventoryManager::hasItemDefinition(const std::string& itemName) const
{
    return itemRegistry.contains(itemName);
}
