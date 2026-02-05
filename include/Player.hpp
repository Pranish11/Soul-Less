#pragma once
#ifndef SOUL_LESS_PLAYER_HPP
#define SOUL_LESS_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>  // for optional

class Player {
public:
    Player();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
	std::vector<sf::Texture> playerWalkTextures;
    std::optional<sf::Sprite> playerSprite;
    sf::Vector2f playerSpritePos;
    float moveSpeed;
	sf::FloatRect Player_HitboxPos;
	sf::Vector2f Player_Hitbox;
    bool canMoveTo(sf::Vector2f position);

    float animationTimer;
    float frameDuration;
	int currentFrame = 0;
};

#endif // SOUL_LESS_PLAYER_HPPSOUL_LESS_PLAYER_HPP