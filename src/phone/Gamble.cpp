#include "../../include/phone/Gamble.hpp"
#include "../../include/phone/phone.hpp"
#include "../../include/phone/Bank_App.hpp"

static int RamdomNumber()
{
	static std::mt19937 rng(std::random_device{}()); // Mersenne Twister engine
	std::uniform_int_distribution<int> dist(1, 10);
	int randomNum = dist(rng);
	std::cout << "Random number between 1 and 10: " << randomNum << std::endl;
	return randomNum;
}


gamble::gamble() : Gamble_App_Sprite(Gamble_App_Texture)
{
	if (!Gamble_App_Texture.loadFromFile("assets/textures/Gamble_App.png"))
	{
		std::cerr << "Error loading Gamble_App.png\n";
	}
	if (!Odd_Texture.loadFromFile("assets/textures/Odd.png"))
	{
		std::cerr << "Error loading Odd.png\n";
	}
	if (!Even_Texture.loadFromFile("assets/textures/Even.png"))
	{
		std::cerr << "Error loading Even.png\n";
	}
	if (!Play_Texture.loadFromFile("assets/textures/Play.png"))
	{
		std::cerr << "Error loading Play.png\n";
	}
	Gamble_App_Sprite.setTexture(Gamble_App_Texture,true);
	Gamble_App_Sprite.setPosition({ 360.f, 10.f });
	Gamble_App_Sprite.setScale({ 3.f,2.f });

	Close_Gamble_App.setPosition({ 1860.f, 10.f });
	Close_Gamble_App.setSize({ 25.f,25.f });
	Close_Gamble_App.setFillColor({ 0, 255, 0, 128 });

	Odd.setTexture(&Odd_Texture);
	Odd.setPosition({ 700.f,850.f });
	Odd.setSize({ 150.f,50.f });
	Odd.setScale({ 1.f,1.f });


	Even.setTexture(&Even_Texture);
	Even.setPosition({ 1300.f,850.f });
	Even.setSize({ 150.f,50.f });
	Even.setScale({ 1.f,1.f });

	Play.setTexture(&Play_Texture);
	Play.setPosition({ 1000.f,950.f });
	Play.setSize({ 150.f,50.f });
	Play.setScale({ 1.f,1.f });
};



void gamble::update(const sf::Vector2f& mouseWorld, phone& phoneInstance)
{
	const bool leftMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	const bool isFreshLeftClick = leftMouseDown && !wasLeftMouseDown;

	if (Close_Gamble_App.getGlobalBounds().contains(mouseWorld))
	{
		if (isFreshLeftClick)
		{
			phoneInstance.Gamble_App_Open = false;
			phoneInstance.isPhoneHidden = false;		// show the phone icons again
		}
	}

	if (Play.getGlobalBounds().contains(mouseWorld))
	{
		if (isFreshLeftClick)
		{
			was_Play_Clicked = true;
			Guessed_Number = RamdomNumber();
		}
	}

	if (Odd.getGlobalBounds().contains(mouseWorld))
	{
		if (isFreshLeftClick && was_Play_Clicked && bank_money.Bank_Money >= 100000)
		{
			was_Odd_Button_Pressed = true;
			std::cout << "odd was clicked \n";
			if (Guessed_Number % 2 != 0)
			{
				bank_money.Bank_Money += 100000;
				was_Play_Clicked = false;
			}
			else
			{
				bank_money.Bank_Money -= 100000;
				was_Play_Clicked = false;
			}
		}
	}

	if (Even.getGlobalBounds().contains(mouseWorld))
	{
		if (isFreshLeftClick && was_Play_Clicked && bank_money.Bank_Money >= 100000)
		{
			was_Even_Button_Pressed = true;
			std::cout << "Even was clicked \n";
			if (Guessed_Number % 2 == 0)
			{
				bank_money.Bank_Money += 100000;
				was_Play_Clicked = false;
			}
			else
			{
				bank_money.Bank_Money -= 100000;
				was_Play_Clicked = false;
			}
		}
	}
}


void gamble::draw(sf::RenderWindow& window)
{
	window.draw(Gamble_App_Sprite);
	//window.draw(Close_Gamble_App);
	window.draw(Odd);
	window.draw(Even);
	window.draw(Play);
}