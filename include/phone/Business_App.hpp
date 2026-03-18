#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Bank_App.hpp"
#include "../Money/Money.hpp"


class phone;

class BusinessApp {
public:
	BusinessApp(const sf::Font& f);
	void update(const sf::Vector2f& mouseWorld, phone& phoneInstance);
	void draw(sf::RenderWindow& window);
	void generateCash(money& moneyInstance, float deltaTime);

	// Save/Load support: expose owned businesses as simple IDs.
	std::vector<std::string> getOwnedBusinesses() const;
	void setOwnedBusinesses(const std::vector<std::string>& businessIds);

	bool is_Business_Application_open = false;
	
private:
	void refreshOwnedTextures();

	bank Bank_Buy;

	const sf::Font& Pixelfont;

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

	sf::Text Business_One_Text;
	sf::Text Business_Two_Text;
	sf::Text Business_Two_Price_Text;
	sf::Text Business_One_Price_Text;

	sf::Text Business_One_Description_Text;
	sf::Text Business_Two_Description_Text;


	bool First_Business_Bought = false;
	bool Second_Business_Bought = false;
	float businessCashRemainder = 0.f;
	bool wasLeftMouseDown = false;
};
