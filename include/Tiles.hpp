#pragma once
#ifndef SOUL_LESS_TILES_HPP
#define SOUL_LESS_TILES_HPP

#include <SFML/Graphics.hpp>

class Tiles {
public:
    Tiles();
    void draw(sf::RenderWindow& window);
    int getTileAt(int row, int col) const;
    static constexpr float TILE_SIZE = 64.f;
    static constexpr int Rows = 17;
    static constexpr int Cols = 30;
    int level[Rows][Cols];

private:
    sf::Texture Wall_Texture;
    sf::Texture Floor_Texture;
};

#endif
