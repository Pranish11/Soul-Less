#include <SFML/Graphics.hpp>
#include "../include/Player.hpp"
#include <iostream>

Player::Player() : moveSpeed(1.5f), playerTexture(), playerSprite(playerTexture)
{
    if (!playerTexture.loadFromFile("assets/textures/BLOB_Forward1.png"))
    {
        std::cerr << "Failed to load player texture at: assets/textures/BLOB_Forward1.png\n";
        return;
    }

    playerSprite = sf::Sprite(playerTexture);
    playerSprite.setTexture(playerTexture);
    playerSprite.setScale({ 2.5f, 2.5f });
    playerSprite.setPosition({ 500.f, 300.f });
    playerSprite.setOrigin({ playerTexture.getSize().x / 2.f, playerTexture.getSize().y / 2.f });
    playerSprite.setColor(sf::Color::White);
}

void Player::update()
{   
    // Get current position
    playerSpritePos = playerSprite.getPosition();

    // Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        playerSprite.setPosition({ playerSpritePos.x, playerSpritePos.y - moveSpeed });
        playerSprite.setRotation(sf::degrees(270));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        playerSprite.setPosition({ playerSpritePos.x, playerSpritePos.y + moveSpeed });
        playerSprite.setRotation(sf::degrees(90));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        playerSprite.setPosition({ playerSpritePos.x - moveSpeed, playerSpritePos.y });
		playerSprite.setRotation(sf::degrees(180));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        playerSprite.setPosition({ playerSpritePos.x + moveSpeed, playerSpritePos.y });
		playerSprite.setRotation(sf::degrees(0));
    }   
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(playerSprite);
}