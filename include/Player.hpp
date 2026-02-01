#pragma once
#ifndef SOUL_LESS_PLAYER_HPP
#define SOUL_LESS_PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void update();
    void draw(sf::RenderWindow& window);

private:
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    sf::Vector2f playerSpritePos;
    float moveSpeed;
};

#endif // SOUL_LESS_PLAYER_HPPSOUL_LESS_PLAYER_HPP