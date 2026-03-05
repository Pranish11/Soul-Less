#pragma once

#include <string>
#include "SFML/Graphics.hpp"

class phone;
class Game;

class Shop {
public:
	Shop();
	void update(const sf::Vector2f& mouseWorld, phone& phoneInstance);
	void draw(sf::RenderWindow& window);

	bool isShopAppOpen = false;

private:
	sf::Texture Shop_Texture;
	sf::Sprite Shop_Sprite;
	sf::RectangleShape Shop_Close;
};



struct Shop_Rectangle
{
	std::string name;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Color color;

	sf::RectangleShape Shop;

	Shop_Rectangle(const std::string& n, sf::Vector2f p, sf::Vector2f sz, const sf::Color& c)
		: name(n), position(p), size(sz), color(c)
	{
		Shop.setPosition(position);
		Shop.setSize(size);
		Shop.setFillColor(color);
	}

	bool isClicked(const sf::Vector2f& mouseWorld) const {
		return Shop.getGlobalBounds().contains(mouseWorld);
	}
};
