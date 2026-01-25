#pragma once
#ifndef SOUL_LESS_TILES_HPP
#define SOUL_LESS_TILES_HPP

#include <SFML/Graphics.hpp>

class Tiles {
public:
    Tiles();
    void draw(sf::RenderWindow& window);

private:
    sf::Texture Wall_Texture;
    sf::Texture Floor_Texture;
};

#endif
