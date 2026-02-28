#include "../../include/phone/phone.hpp"
#include "../../include/Game.hpp"
#include <iostream>


phone::phone(): phoneSprite(phoneTexture) {
	if (!phoneTexture.loadFromFile("assets/textures/Phone.png"))
	{
		std::cerr << "Error: Failed to load Phone.png\n";
	}
	phoneSprite = sf::Sprite(phoneTexture);


	phoneSprite.setPosition({ 1500.f, 500.f });
	phoneSprite.setScale({ 4.f, 4.f });

}
void phone::update()
{

}

void phone::draw(sf::RenderWindow& window)
{
		window.draw(phoneSprite);
}