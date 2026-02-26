#include "../../include/level/Tiles.hpp"
#include "../../include/game.hpp"
#include <iostream>

Tiles::Tiles()
{
    if (!Wall_Texture.loadFromFile("assets/textures/Wall.png"))
    {
        std::cerr << "Warning: Failed to load Wall.png\n";
    }

    if (!Floor_Texture.loadFromFile("assets/textures/Floor.png"))
    {
        std::cerr << "Warning: Failed to load Floor.png\n";
    }


    // Initialize the member 'level' from a local initializer then copy it into the member array.
    int initLevel[Rows][Cols] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    // copy into member level
    for (int i = 0; i < Rows; ++i) {
        for (int j = 0; j < Cols; ++j) {
            level[i][j] = initLevel[i][j];
        }
    }
}

void Tiles::draw(sf::RenderWindow& window)
{
    constexpr float Tile_Size = 64.f;   

    sf::Sprite wallSprite(Wall_Texture);
    wallSprite.setScale({2.f,2.f});
    sf::Sprite floorSprite(Floor_Texture);
    floorSprite.setScale({ 2.f,2.f });

    for (int i = 0; i < Rows; ++i) // Assumes Rows and Cols are members of Tiles class
    {
        for (int j = 0; j < Cols; ++j) // Assumes Rows and Cols are members of Tiles class
        {
            sf::Vector2f pos(j * Tile_Size, i * Tile_Size);

            if (level[i][j] == 1)
            {
                wallSprite.setPosition(pos);
                window.draw(wallSprite);
            }
            else
            {
                floorSprite.setPosition(pos);
                window.draw(floorSprite);
            }
        }
    }
}

int Tiles::getTileAt(int row, int col) const
{
    if (row >= 0 && row < Rows && col >= 0 && col < Cols) {
        return level[row][col];
    }
    return 1; // Return wall if out of bounds
}
