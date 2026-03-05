#include <vector>
#include <iostream>
#include <string>

#include "../../include/phone/Shopiee_App.hpp"
#include "../../include/Game.hpp"
#include "../../include/phone/phone.hpp"

Shop::Shop() : Shop_Sprite(Shop_Texture)
{
	if (!Shop_Texture.loadFromFile("assets/textures/Shoppiee_App.png"))
	{
		std::cerr << "ERROR: Failed to load Shoppiee_App.png \n";
	}

	Shop_Sprite.setTexture(Shop_Texture, true);
	Shop_Sprite.setPosition({ 230.f, 10.f });
	Shop_Sprite.setScale({ 6.5f, 4.f });

	//close rectangl e
	Shop_Close.setFillColor({ 255, 0, 0, 128 });
	Shop_Close.setSize({ 70.f,55.f });
	Shop_Close.setPosition({ 1810.f, 10.f });

}

void Shop::update(const sf::Vector2f& mouseWorld, phone& phoneInstance)
{
	if (Shop_Close.getGlobalBounds().contains(mouseWorld))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			isShopAppOpen = false;
			phoneInstance.Shop_App_Open = false;
			phoneInstance.isPhoneHidden = false;     // show the phone icons again
		}
	}
	
}

void Shop::draw(sf::RenderWindow& window)
{
	window.draw(Shop_Sprite);
	window.draw(Shop_Close);
}
