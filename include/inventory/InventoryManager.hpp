#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "../items/Item.hpp"

class Inventory;

class InventoryManager {
public:
    bool registerItem(Inventory& inventory, const std::string& itemName, const std::string& texturePath, int maxStack = 1);
    void registerDefaultItems(Inventory& inventory);
    bool giveItem(Inventory& inventory, const std::string& itemName, int qty = 1) const;
    bool hasItemDefinition(const std::string& itemName) const;

private:
    std::unordered_map<std::string, std::unique_ptr<Item>> itemRegistry;
};
