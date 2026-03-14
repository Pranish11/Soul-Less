#pragma once

#include <SFML/Graphics.hpp>

class money{
public:
	money(const sf::Font& f);
	void update();
	void draw(sf::RenderWindow& window);
	void cashDraw(sf::RenderWindow& window);
	int cash = 1000;

private:
	const sf::Font& Pixelfont;
	sf::Text Cash_Text;
	sf::Text Cash_Amount_Display;
};