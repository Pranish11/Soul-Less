#pragma once


#include <SFML/Graphics.hpp>

class phone;

class bank
{
public:
	bank();
	void update(const sf::Vector2f& mouseWorld, phone& phoneInstance);
	void draw(sf::RenderWindow& window);

	bool is_Bank_App_Open = false;


private:
	sf::Texture		Bank_App_Texture;
	sf::Sprite		Bank_App_Sprite;

	sf::RectangleShape dollar_displaying_retangle;
	sf::RectangleShape Close_Bank_App;

	sf::RectangleShape Withdraw_Rect;
	sf::RectangleShape Deposite_Rect;
	sf::RectangleShape Donate_Rect;

};