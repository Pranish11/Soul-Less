#include "../../include/items/Place.hpp"
#include "../../include/inventory/Inventory.hpp"
#include "../../include/items/Item.hpp"
#include "../../include/level/Tiles.hpp"
#include "../../include/Money/Money.hpp"
#include <utility>
#include <cmath>

place::place()
{
}

void place::update(const sf::Vector2f& mouseWorld, Inventory& inventory, Tiles& tilemap, bool canPlace)
{
	const bool leftMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	const bool isFreshLeftClick = leftMouseDown && !wasLeftMouseDown;

	if (canPlace && isFreshLeftClick) {
		const std::string selectedItem = inventory.getSelectedItemName();
		const int tileCol = static_cast<int>(mouseWorld.x / Tiles::TILE_SIZE);
		const int tileRow = static_cast<int>(mouseWorld.y / Tiles::TILE_SIZE);

		if (selectedItem == "Broom") {
			for (auto it = placedItems.begin(); it != placedItems.end(); ++it) {
				if (it->tileRow == tileRow && it->tileCol == tileCol) {
					placedItems.erase(it);
					tilemap.setTileAt(tileRow, tileCol, 0);
					wasLeftMouseDown = leftMouseDown;
					return;
				}
			}

			wasLeftMouseDown = leftMouseDown;
			return;
		}

		if (tilemap.getTileAt(tileRow, tileCol) != 0) {
			wasLeftMouseDown = leftMouseDown;
			return;
		}

		if (!selectedItem.empty()) {
			const Item* itemData = inventory.getItemData(selectedItem);
			if (itemData && itemData->texture && inventory.removeSelectedItem(1)) {
				PlacedItem placedItem;
				placedItem.itemName = selectedItem;
				placedItem.texture = itemData->texture.get();
				placedItem.position = {
					tileCol * Tiles::TILE_SIZE,
					tileRow * Tiles::TILE_SIZE
				};
				placedItem.tileRow = tileRow;
				placedItem.tileCol = tileCol;
				placedItems.push_back(std::move(placedItem));
				tilemap.setTileAt(tileRow, tileCol, 2);
			}
		}
	}

	wasLeftMouseDown = leftMouseDown;
}

void place::generateCash(money& moneyInstance, float deltaTime)
{
	if (placedItems.empty() || deltaTime <= 0.f) {
		return;
	}

	int cokeCount = 0;
	int weedCount = 0;
	int chemicalCount = 0;

	for (const PlacedItem& placedItem : placedItems) {
		if (placedItem.itemName == "Coke") {
			++cokeCount;
		}
		else if (placedItem.itemName == "B_Weed") {
			++weedCount;
		}
		else if (placedItem.itemName == "Chemical") {
			++chemicalCount;
		}
	}

	const int incomePerSecond = (cokeCount * 1000) + (weedCount * 200) + (chemicalCount * 2500);
	if (incomePerSecond <= 0) {
		return;
	}

	const float earned = (static_cast<float>(incomePerSecond) * deltaTime) + cashRemainder;
	const int wholeDollars = static_cast<int>(std::floor(earned));
	cashRemainder = earned - static_cast<float>(wholeDollars);

	if (wholeDollars > 0) {
		moneyInstance.cash += wholeDollars;
	}
}

void place::draw(sf::RenderWindow& window)
{
	for (const PlacedItem& placedItem : placedItems) {
		if (!placedItem.texture) {
			continue;
		}

		sf::Sprite sprite(*placedItem.texture);
		sprite.setPosition(placedItem.position);
		const sf::Vector2u texSize = placedItem.texture->getSize();
		if (texSize.x > 0u && texSize.y > 0u) {
			sprite.setScale({
				Tiles::TILE_SIZE / static_cast<float>(texSize.x),
				Tiles::TILE_SIZE / static_cast<float>(texSize.y)
			});
		}
		window.draw(sprite);
	}
}
