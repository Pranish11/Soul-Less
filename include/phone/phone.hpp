#pragma once

#include "SFML/Graphics.hpp"

class phone {
public:
	phone();
	void update();
	void draw(sf::RenderWindow& window);


	bool isPhoneHidden = true;

private:
	
	sf::Texture phoneTexture;
	sf::Sprite phoneSprite;

	sf::Texture Bank_App_Texture;
	sf::Texture Shop_App_Texture;
	sf::Texture ID_App_Texture;
	sf::Texture Illegal_App_Texture;
	sf::Texture Business_App_Texture;

	sf::RectangleShape Bank_App_Rect;
	sf::RectangleShape Shop_App_Rect;
	sf::RectangleShape ID_App_Rect;
	sf::RectangleShape Illegal_App_Rect;
	sf::RectangleShape Business_App_Rect;

};