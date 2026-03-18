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

	// Save/Load support.
	//We intentionally store only what we need: item id + world position.
	struct PlacedItemSaveData {
		std::string itemName;
		sf::Vector2f position{};
	};

	std::vector<PlacedItemSaveData> getSavePlacedItems() const;
	void clearPlacedItems(Tiles& tilemap);
	void setSavePlacedItems(const std::vector<PlacedItemSaveData>& items, const Inventory& inventory, Tiles& tilemap);
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
