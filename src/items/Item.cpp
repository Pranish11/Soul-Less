#include "../../include/items/Item.hpp"
#include <iostream>

Item::Item(const std::string& n, const std::string& texturePath, int maxStack)
    : name(n), texture(std::make_unique<sf::Texture>()), stackSize(maxStack)
{
    if (!texture->loadFromFile(texturePath)) {
        std::cerr << "Item: failed to load texture: " << texturePath << '\n';
    } else {
        sprite.emplace(*texture);
    }
}