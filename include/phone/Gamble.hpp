#pragma once

#include <iostream>
#include <ctime>
#include <random>

#include <SFML/Graphics.hpp>
#include "Bank_App.hpp"

class phone;

class gamble {

public:
	gamble();
	void update(const sf::Vector2f& mouseWorld, phone& phoneInstance);
	void draw(sf::RenderWindow& window);

private:
	int Guessed_Number = 0;

	sf::Texture Gamble_App_Texture;
	sf::Texture Odd_Texture;
	sf::Texture Even_Texture;
	sf::Texture Play_Texture;
	

	sf::Sprite Gamble_App_Sprite;


	sf::RectangleShape Close_Gamble_App;
	sf::RectangleShape Odd;
	sf::RectangleShape Even;
	sf::RectangleShape Play;


	bool wasLeftMouseDown = false;
	bool was_Odd_Button_Pressed = false;
	bool was_Even_Button_Pressed = false;
	bool was_Play_Clicked = false;

	bank		bank_money;
};