#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <optional>

class Item {
public:
    std::string name;
    std::unique_ptr<sf::Texture> texture;
    std::optional<sf::Sprite> sprite;
    int stackSize;

    Item(const std::string& n, const std::string& texturePath, int maxStack = 1);

    // idk wtf is down here ???, do i even need this ?
    Item(const Item&) = delete;
    Item& operator=(const Item&) = delete;
    Item(Item&&) noexcept = default;
    Item& operator=(Item&&) noexcept = default;
};

