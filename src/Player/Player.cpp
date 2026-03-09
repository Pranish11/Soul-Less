#include <SFML/Graphics.hpp>
#include "../../include/player/Player.hpp"
#include "../../include/level/Tiles.hpp"
#include "../../include/items/Item.hpp" 
#include <iostream>

Player::Player() : moveSpeed(1.f), currentFrame(0), animationTimer(0.0f), frameDuration(0.15f)
{
    playerWalkTextures.resize(4);

    if (!playerWalkTextures[0].loadFromFile("assets/textures/BLOB_Forward1.png") ||
        !playerWalkTextures[1].loadFromFile("assets/textures/BLOB_Forward2.png") ||
        !playerWalkTextures[2].loadFromFile("assets/textures/BLOB_Forward3.png") ||
        !playerWalkTextures[3].loadFromFile("assets/textures/BLOB_Forward4.png"))
    {
        std::cerr << "Failed to load player animation frames\n";
    }

    playerSprite.emplace(playerWalkTextures[0]);
    playerSprite->setOrigin({ playerWalkTextures[0].getSize().x / 2.f, playerWalkTextures[0].getSize().y / 2.f });
    playerSprite->setScale({ 2.5f, 2.5f });
    playerSprite->setPosition({ 350.f, 250.f });
}

void Player::update(float deltaTime, const Tiles& tilemap)
{   
	bool isMoving = false;
    sf::Vector2f currentPos = playerSprite->getPosition();
    sf::Vector2f newPosition = currentPos;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        newPosition.y -= moveSpeed;
        playerSprite->setRotation(sf::degrees(270));
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        newPosition.y += moveSpeed;
        playerSprite->setRotation(sf::degrees(90));
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        newPosition.x -= moveSpeed;
        playerSprite->setRotation(sf::degrees(180));
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        newPosition.x += moveSpeed;
        playerSprite->setRotation(sf::degrees(0));
        isMoving = true;
    }

    // Apply movement only if destination is valid
    if (isMoving && canMoveTo(newPosition, tilemap)) {
        playerSprite->setPosition(newPosition);
    }

    // Animation
    if (isMoving) {
        animationTimer += deltaTime;

        if (animationTimer >= frameDuration) {
            animationTimer = 0.0f;
            currentFrame = (currentFrame + 1) % 4;  
            playerSprite->setTexture(playerWalkTextures[currentFrame]);
            // recenter origin in case frames differ
            playerSprite->setOrigin({
                playerWalkTextures[currentFrame].getSize().x / 2.f,
                playerWalkTextures[currentFrame].getSize().y / 2.f
            });
        }
    }
    else {
        currentFrame = 0;
        animationTimer = 0.0f;
        playerSprite->setTexture(playerWalkTextures[0]);
        playerSprite->setOrigin({
            playerWalkTextures[0].getSize().x / 2.f,
            playerWalkTextures[0].getSize().y / 2.f
        });
    }

    playerSpritePos = playerSprite->getPosition();
}

bool Player::canMoveTo(sf::Vector2f newPosition, const Tiles& tilemap)
{
	const float tileSize = Tiles::TILE_SIZE;
	int tileX = static_cast<int>(newPosition.x / tileSize);
	int tileY = static_cast<int>(newPosition.y / tileSize);
    return tilemap.getTileAt(tileY, tileX) == 0;
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(*playerSprite);
}
