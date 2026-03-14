#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class phone;
class Game;
class Inventory;
class InventoryManager;
class money;

struct ShopItems
{
	std::string name;
	int price = 0;
	sf::RectangleShape rect;
	sf::Texture texture;
	sf::Sprite sprite{ texture };
	sf::Sprite buySign{ texture };
	sf::Vector2f position;
};

class Shop {
public:
	Shop();
	void update(const sf::Vector2f& mouseWorld, phone& phoneInstance, Inventory& inventory, InventoryManager& inventoryManager, money& moneyInstance);
	void draw(sf::RenderWindow& window, const sf::Font& font);

	bool isShopAppOpen = false;

private:

	sf::Texture Shop_Texture;
	sf::Texture Buy_Sign_Texture;
	sf::Sprite Shop_Sprite;
	sf::RectangleShape Shop_Close;
	std::vector<ShopItems> items;
	bool wasLeftMouseDown = false;
	bool showInventoryFullText = false;
	sf::Clock inventoryTextTimer;
	bool showNotEnoughFundsText = false;
	sf::Clock notEnoughFundsTextTimer;
};
