#pragma once

#include <SFML/Graphics.hpp>
#include "../Game.hpp"


class phone;

class BusinessApp {
public:
	BusinessApp();
	void update(const sf::Vector2f& mouseWorld, phone& phoneInstance);
	void draw(sf::RenderWindow& window);

	bool is_Business_Application_open = false;
	
private:
	sf::Texture Business_App_Texture;
	sf::Sprite	Business_App_Sprite;

	sf::Texture Business_One_Texture;
	sf::Texture Business_Two_Texture;

	sf::Texture Buy_Texture;
	sf::Texture Owned_Texture;

	sf::RectangleShape First_Business;
	sf::RectangleShape First_Business_Buy;
	sf::RectangleShape Second_Business;
	sf::RectangleShape Second_Business_Buy;


	sf::RectangleShape Business_App_Close;

};