#pragma once

#include <SFML/Graphics.hpp>

class money{
public:
	money(const sf::Font& f);
	void update();
	void cashDraw(sf::RenderWindow& window);
	long long cash = 3500000000;

private:
	const sf::Font& Pixelfont;
	sf::Text Cash_Text;
	sf::Text Cash_Amount_Display;
};