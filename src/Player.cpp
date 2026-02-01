#include <SFML/Graphics.hpp>
#include "../include/Player.hpp"
#include <iostream>

Player::Player() : moveSpeed(1.5f), playerSprite(playerTexture)
{
    // Load texture first
    if (!playerTexture.loadFromFile("assets/textures/BLOB_Forward1.png"))
    {
        std::cerr << "Failed to load player texture\n";
    }

    // Set up sprite properties
    playerSprite.setScale({ 1.5f, 1.5f });
    playerSprite.setPosition({ 100.f, 100.f });
}

void Player::update()
{
    // Get current position
    playerSpritePos = playerSprite.getPosition();

    // Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        playerSprite.setPosition({ playerSpritePos.x, playerSpritePos.y - moveSpeed });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        playerSprite.setPosition({ playerSpritePos.x, playerSpritePos.y + moveSpeed });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        playerSprite.setPosition({ playerSpritePos.x - moveSpeed, playerSpritePos.y });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        playerSprite.setPosition({ playerSpritePos.x + moveSpeed, playerSpritePos.y });
    }
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(playerSprite);
}