#include "../include/Tiles.hpp"
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

}

void Tiles::draw(sf::RenderWindow& window)
{
    constexpr float Tile_Size = 32.f;   
    constexpr int Rows = 10;
    constexpr int Cols = 10;

    int level[Rows][Cols] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,1,1,0,1,0,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,0,0,1,1,1,1}
    };

    sf::Sprite wallSprite(Wall_Texture);
    sf::Sprite floorSprite(Floor_Texture);

    for (int i = 0; i < Rows; ++i)
    {
        for (int j = 0; j < Cols; ++j)
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
