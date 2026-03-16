#include <iostream>
#include <string>

#include "../../include/phone/Bank_App.hpp"
#include "../../include/phone/phone.hpp"
#include "../../include/Money/Money.hpp"

// I am so fucking dumb, i should have made seprate texture for witdraw and others :(, i will not make this mistake again, so much time wasted on ts.

long long bank::Bank_Money = 0;

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

	Withdraw_Rect.setPosition					({790,750});
	Withdraw_Rect.setSize						({580,140});
	Withdraw_Rect.setFillColor					({ 0, 255, 0, 128 });	//green colour

	Deposite_Rect.setPosition					({450,580 });
	Deposite_Rect.setSize						({550,100 });
	Deposite_Rect.setFillColor					({ 0, 0, 255, 128 });	//Blue	 colour

	Donate_Rect.setPosition						({1150,580});
	Donate_Rect.setSize							({ 550,100 });
	Donate_Rect.setFillColor					({255 , 0, 0, 128});	// Red  colour

};


void bank::update(const sf::Vector2f& mouseWorld, phone& phoneInstance, money& moneyInstance)
{
	const bool leftMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	const bool isFreshLeftClick = leftMouseDown && !wasLeftMouseDown;

	if (showLowBalanceText && lowBalanceTextTimer.getElapsedTime().asSeconds() > 2.0f)
	{
		showLowBalanceText = false;
	}

	if (Close_Bank_App.getGlobalBounds().contains(mouseWorld))
	{
		if (isFreshLeftClick)
		{
			is_Bank_App_Open = false;
			phoneInstance.Bank_App_Open = false;		
			phoneInstance.isPhoneHidden = false;		// show the phone icons again
		}
	}

	if (Withdraw_Rect.getGlobalBounds().contains(mouseWorld))
	{
		if (isFreshLeftClick)
		{
			if (Bank_Money >= 10000)
			{
				Bank_Money = Bank_Money - 10000;
				moneyInstance.cash = moneyInstance.cash + 10000;
			}
			else
			{
				showLowBalanceText = true;
				lowBalanceTextTimer.restart();
			}
		}
	}

	if (Deposite_Rect.getGlobalBounds().contains(mouseWorld))
	{
		if (isFreshLeftClick)
		{
			Bank_Money = Bank_Money + moneyInstance.cash;
			moneyInstance.cash = moneyInstance.cash  - moneyInstance.cash;
		}
	}

	if (Donate_Rect.getGlobalBounds().contains(mouseWorld))
	{
		if (isFreshLeftClick)
		{
			Bank_Money = Bank_Money - Bank_Money;
		}
	}

	wasLeftMouseDown = leftMouseDown;
}

void bank::draw(sf::RenderWindow& window, const sf::Font& font)
{
	if (is_Bank_App_Open)
	{
		window.draw(Bank_App_Sprite);

		sf::Text bankMoneyText(font);
		bankMoneyText.setString("$" + std::to_string(Bank_Money));
		bankMoneyText.setCharacterSize(28);
		bankMoneyText.setFillColor(sf::Color::Black);

		const sf::FloatRect textBounds = bankMoneyText.getLocalBounds();
			bankMoneyText.setOrigin({
				textBounds.position.x + textBounds.size.x * 0.5f,
				textBounds.position.y + textBounds.size.y * 0.5f
			});
		const sf::Vector2f rectCenter = dollar_displaying_retangle.getPosition() + (dollar_displaying_retangle.getSize() * 0.5f);
		bankMoneyText.setPosition(rectCenter);

		window.draw(bankMoneyText);

		if (showLowBalanceText)
		{
			sf::Text lowBalanceText(font, "Too low balance to withdraw, Minimum amount needed to withdraw : 10K");
			lowBalanceText.setCharacterSize(26);
			lowBalanceText.setFillColor(sf::Color::Red);
			lowBalanceText.setPosition({ 570.f, 490.f });
			window.draw(lowBalanceText);
		}

		//window.draw(dollar_displaying_retangle);			// for testing, bar for money in bank app
		//window.draw(Close_Bank_App);						// for testing
		//window.draw(Withdraw_Rect);						
		//window.draw(Deposite_Rect);
		//window.draw(Donate_Rect);
	}
}
