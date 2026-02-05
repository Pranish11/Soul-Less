#include <SFML/Graphics.hpp>
#include "../include/Player.hpp"
#include <iostream>


Player::Player() : moveSpeed(0.5f), currentFrame(0), animationTimer(0.0f), frameDuration(0.15f)
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
    playerSprite->setOrigin({playerWalkTextures[0].getSize().x / 2.f, playerWalkTextures[0].getSize().y / 2.f });
    playerSprite->setScale({ 2.5f, 2.5f });
    playerSprite->setPosition({ 500.f, 300.f });
}

void Player::update(float deltaTime)
{   
	bool isMoving = false;

    // Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        playerSprite->move({ 0.f, -moveSpeed });
        playerSprite->setRotation(sf::degrees(270));
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        playerSprite->move({ 0.f, moveSpeed });
        playerSprite->setRotation(sf::degrees(90));
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        playerSprite->move({ -moveSpeed, 0.f });
		playerSprite->setRotation(sf::degrees(180));
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        playerSprite->move({ moveSpeed, 0.f });
		playerSprite->setRotation(sf::degrees(0));
        isMoving = true;
    }

    // Animation
    if (isMoving) {
        animationTimer += deltaTime;

        if (animationTimer >= frameDuration) {
            animationTimer = 0.0f;
            currentFrame = (currentFrame + 1) % 4;  
            playerSprite->setTexture(playerWalkTextures[currentFrame]);
        }
    }
    else {
        currentFrame = 0;
        animationTimer = 0.0f;
        playerSprite->setTexture(playerWalkTextures[0]);
    }

    playerSpritePos = playerSprite->getPosition();
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(*playerSprite);
}
