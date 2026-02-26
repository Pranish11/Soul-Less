#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>

class Tiles;

class Player {
public:
    Player();
    void update(float deltaTime, const Tiles& tilemap);
    void draw(sf::RenderWindow& window);

private:
    std::vector<sf::Texture> playerWalkTextures;
    std::optional<sf::Sprite> playerSprite;
    sf::Vector2f playerSpritePos;
    float moveSpeed;
    sf::FloatRect Player_HitboxPos;
    sf::Vector2f Player_Hitbox;
    bool canMoveTo(sf::Vector2f position, const Tiles& tilemap);

    float animationTimer;
    float frameDuration;
    int currentFrame = 0;
};
