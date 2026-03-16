#include <iostream>

#include "../../include/phone/Business_App.hpp"
#include "../../include//phone/phone.hpp"
#include "../../include/game.hpp"
#include "../../include/phone/Bank_App.hpp"
#include <cmath>

BusinessApp::BusinessApp(const sf::Font& font) : Business_App_Sprite(Business_App_Texture), Pixelfont(font),	Business_One_Text(font),
																												Business_Two_Text(font),
																												Business_One_Price_Text(font),
																												Business_Two_Price_Text(font),
																												Business_One_Description_Text(font),
																												Business_Two_Description_Text(font)
{
	if (!Business_App_Texture.loadFromFile("assets/textures/Business_Web.png"))
	{
		std::cerr << "Error: Failed to load Business_Web.png\n";
	}

	if (!Business_One_Texture.loadFromFile("assets/textures/Business_one.png"))
	{
		std::cerr << "Error: Failed to load Business_one.png\n";
	}

	if (!Business_Two_Texture.loadFromFile("assets/textures/Business_two.png"))
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

	First_Business.setPosition({ 500.f,200.f });
	First_Business.setSize({ 350.f,350.f });
	//First_Business.setFillColor({ 0, 255, 0, 128 });
	First_Business.setTexture(&Business_One_Texture);


	Second_Business.setPosition({ 1300.f,200.f });
	Second_Business.setSize({ 350.f,350.f });
	//Second_Business.setFillColor({ 0, 255, 0, 128 });
	Second_Business.setTexture(&Business_Two_Texture);

	First_Business_Buy.setPosition({ 500.f,700.f });
	First_Business_Buy.setSize({ 150.f,50.f });
	First_Business_Buy.setScale({ 1.f,1.f });
	//First_Business_Buy.setFillColor({ 255, 0, 0, 128 });
	First_Business_Buy.setTexture(&Buy_Texture);

	Second_Business_Buy.setPosition({ 1300.f,700.f });
	Second_Business_Buy.setSize({ 150.f,50.f });
	Second_Business_Buy.setScale({ 1.f,1.f });
	//Second_Business_Buy.setFillColor({ 255, 0, 0, 128 });
	Second_Business_Buy.setTexture(&Buy_Texture);


	/// Text

	Business_One_Text.setFont(Pixelfont);
	Business_One_Text.setString("Tech Startup");
	Business_One_Text.setCharacterSize(20);
	Business_One_Text.setPosition({ 500.f,150.f });
	Business_One_Text.setFillColor({ sf::Color::Black });

	Business_One_Price_Text.setFont(Pixelfont);
	Business_One_Price_Text.setString("Price : $150M");
	Business_One_Price_Text.setCharacterSize(20);
	Business_One_Price_Text.setPosition({ 500.f,600.f });
	Business_One_Price_Text.setFillColor({ sf::Color::Black });

	Business_Two_Text.setFont(Pixelfont);
	Business_Two_Text.setString("SiliconCore Semiconductor Manufacturing Company Limited");
	Business_Two_Text.setCharacterSize(20);
	Business_Two_Text.setPosition({ 1100.f,150.f });
	Business_Two_Text.setFillColor({ sf::Color::Black });

	Business_Two_Price_Text.setFont(Pixelfont);
	Business_Two_Price_Text.setString("Price : $3.5B");
	Business_Two_Price_Text.setCharacterSize(20);
	Business_Two_Price_Text.setPosition({ 1300.f,600.f });
	Business_Two_Price_Text.setFillColor({ sf::Color::Black });

	Business_One_Description_Text.setFont(Pixelfont);
	Business_One_Description_Text.setString("Generates $ 50K per sec in cash");
	Business_One_Description_Text.setCharacterSize(16);
	Business_One_Description_Text.setPosition({ 500.f,550.f });
	Business_One_Description_Text.setFillColor({ sf::Color::Black });

	Business_Two_Description_Text.setFont(Pixelfont);
	Business_Two_Description_Text.setString("Generates $ 120K per sec in cash");
	Business_Two_Description_Text.setCharacterSize(16);
	Business_Two_Description_Text.setPosition({ 1300.f,550.f });
	Business_Two_Description_Text.setFillColor({ sf::Color::Black });
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

	//hover effect

	if (First_Business_Buy.getGlobalBounds().contains(mouseWorld))
	{
		First_Business_Buy.setScale({ 1.2f,1.2f });
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && Bank_Buy.Bank_Money >= 150000000)
		{
			Bank_Buy.Bank_Money = Bank_Buy.Bank_Money - 150000000;
			First_Business_Bought = true;
			if (First_Business_Bought)
			{
				First_Business_Buy.setTexture(&Owned_Texture);
			}
		}
	}
	else
	{
		First_Business_Buy.setScale({ 1.f,1.f });
	}

	//hover effect

	if (Second_Business_Buy.getGlobalBounds().contains(mouseWorld))
	{
		Second_Business_Buy.setScale({ 1.2f,1.2f });
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && Bank_Buy.Bank_Money >= 3500000000)
		{
			Bank_Buy.Bank_Money = Bank_Buy.Bank_Money - 3500000000;
			Second_Business_Bought = true;
			if (Second_Business_Bought)
			{
				Second_Business_Buy.setTexture(&Owned_Texture);
			}
		}
	}
	else
	{
		Second_Business_Buy.setScale({ 1.f,1.f });
	}

}






void BusinessApp::draw(sf::RenderWindow& window)
{
	window.draw(Business_App_Sprite);
	//window.draw(Business_App_Close);
	window.draw(First_Business);
	window.draw(Second_Business);
	window.draw(First_Business_Buy);
	window.draw(Second_Business_Buy); 

	/// Text draw
	window.draw(Business_One_Text);
	window.draw(Business_One_Price_Text);
	window.draw(Business_Two_Text);
	window.draw(Business_Two_Price_Text);
	window.draw(Business_One_Description_Text);
	window.draw(Business_Two_Description_Text);
}

// after Business bought in business app
void BusinessApp::generateCash(money& moneyInstance, float deltaTime)
{
	if (deltaTime <= 0.f) {
		return;
	}

	const int incomePerSecond =
		(First_Business_Bought ? 50000 : 0) +
		(Second_Business_Bought ? 120000 : 0);

	if (incomePerSecond <= 0) {
		return;
	}

	const float earned = (static_cast<float>(incomePerSecond) * deltaTime) + businessCashRemainder;
	const int wholeDollars = static_cast<int>(std::floor(earned));
	businessCashRemainder = earned - static_cast<float>(wholeDollars);

	if (wholeDollars > 0) {
		moneyInstance.cash += wholeDollars;
	}
}
