#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Inventory;
class Tiles;
class money;

class place
{
public :
	place();
	void update(const sf::Vector2f& mouseWorld, Inventory& inventory, Tiles& tilemap, bool canPlace);
	void generateCash(money& moneyInstance, float deltaTime);
	void draw(sf::RenderWindow& window);
private:
	struct PlacedItem {
		std::string itemName;
		const sf::Texture* texture = nullptr;
		sf::Vector2f position;
		int tileRow = 0;
		int tileCol = 0;
	};

	std::vector<PlacedItem> placedItems;
	bool wasLeftMouseDown = false;
	float cashRemainder = 0.f;

};
