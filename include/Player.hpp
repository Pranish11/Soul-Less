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

    float animationTimer;
    float frameDuration;
	int currentFrame = 0;
};

#endif // SOUL_LESS_PLAYER_HPPSOUL_LESS_PLAYER_HPP