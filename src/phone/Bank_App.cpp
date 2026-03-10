#include <iostream>

#include "../../include/phone/Bank_App.hpp"
#include "../../include/phone/phone.hpp"

bank::bank() : Bank_App_Sprite(Bank_App_Texture)
{
	if (!Bank_App_Texture.loadFromFile("assets/textures/bank_App_page.png"))
	{
		std::cerr << "Error loading bank_App_page.png\n";
	}

	Bank_App_Sprite.setTexture		(Bank_App_Texture, true);
	Bank_App_Sprite.setPosition		({ 360.f, 10.f });
	Bank_App_Sprite.setScale		({ 3.f,2.f });


	dollar_displaying_retangle.setPosition		({ 465.f,430.f });
	dollar_displaying_retangle.setSize			({ 1100.f,50.f });
	dollar_displaying_retangle.setFillColor		({ 255, 0, 0, 128 });

	Close_Bank_App.setPosition					({ 1815.f, 10.f });
	Close_Bank_App.setSize						({ 70.f,55.f });
	Close_Bank_App.setFillColor					({ 0, 255, 0, 128 });
};


void bank::update(const sf::Vector2f& mouseWorld, phone& phoneInstance)
{
	if (Close_Bank_App.getGlobalBounds().contains(mouseWorld))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			is_Bank_App_Open = false;
			phoneInstance.Bank_App_Open = false;		// close the  ID app
			phoneInstance.isPhoneHidden = false;		// show the phone icons again
		}
	}
}

void bank::draw(sf::RenderWindow& window)
{
	if (is_Bank_App_Open)
	{
		window.draw(Bank_App_Sprite);
		//window.draw(dollar_displaying_retangle);			// for testing
		//window.draw(Close_Bank_App);						// for testing
	}
}