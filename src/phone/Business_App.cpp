#include <iostream>

#include "../../include/phone/Business_App.hpp"
#include "../../include//phone/phone.hpp"



BusinessApp::BusinessApp() : Business_App_Sprite(Business_App_Texture)
{
	if (!Business_App_Texture.loadFromFile("assets/textures/Business_Web.png"))
	{
		std::cerr << "Error: Failed to load Business_Web.png\n";
	}

	if (!Business_One_Texture.loadFromFile("assets/textures/Business_one.png"))
	{
		std::cerr << "Error: Failed to load Business_one.png\n";
	}

	if (!Business_One_Texture.loadFromFile("assets/textures/Business_two.png"))
	{
		std::cerr << "Error: Failed to load Business_two.png\n";
	}

	if (!Buy_Texture.loadFromFile("assets/textures/Buy.png"))
	{
		std::cerr << "Error: Failed to load Buy.png\n";
	}

	if (!Owned_Texture.loadFromFile("assets/textures/Owned.png"))
	{
		std::cerr << "Error: Failed to load Owned.png\n";
	}

	Business_App_Sprite.setTexture(Business_App_Texture, true);
	Business_App_Sprite.setPosition({ 360.f, 10.f });
	Business_App_Sprite.setScale({ 3.f,2.f });

	Business_App_Close.setPosition({ 1815.f, 10.f });
	Business_App_Close.setSize({ 70.f,55.f });
	Business_App_Close.setFillColor({ 0, 255, 0, 128 });
};






void BusinessApp::update(const sf::Vector2f& mouseWorld, phone& phoneInstance)
{
	if (Business_App_Close.getGlobalBounds().contains(mouseWorld))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			//is_Business_Application_open = false;
			phoneInstance.Business_App_Open = false;
			phoneInstance.isPhoneHidden = false;		// show the phone icons again
		}
	}

}






void BusinessApp::draw(sf::RenderWindow& window)
{
	window.draw(Business_App_Sprite);
	//window.draw(Business_App_Close);
}