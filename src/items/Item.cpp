#include "../../include/items/Item.hpp"
#include <iostream>

Item::Item(const std::string& n, const std::string& texturePath, int maxStack)
    : name(n), texture(std::make_unique<sf::Texture>()), stackSize(maxStack)
{
    sf::Image image;
    if (!image.loadFromFile(texturePath)) {
        std::cerr << "Item: failed to load texture: " << texturePath << '\n';
    } else {
        // Make the flat background transparent using the top-left pixel color.
        const sf::Color backgroundColor = image.getPixel({ 0u, 0u });
        image.createMaskFromColor(backgroundColor);

        if (!texture->loadFromImage(image)) {
            std::cerr << "Item: failed to create texture from image: " << texturePath << '\n';
        } else {
            sprite.emplace(*texture);
        }
    }
}
