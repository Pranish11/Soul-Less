#pragma once
#include "SFML/Graphics.hpp"

class phone;

class ID
{
public:
    ID();
    void update(const sf::Vector2f& mouseWorld, phone& phoneInstance);
    void draw(sf::RenderWindow& window);
    bool is_ID_App_Open = false;

private:
    sf::Texture ID_Texture;
    sf::Sprite ID_Sprite;
    sf::RectangleShape ID_App_Close;
};