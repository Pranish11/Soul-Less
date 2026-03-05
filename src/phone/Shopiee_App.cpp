#include <iostream>
#include <string>

#include "../../include/phone/Shopiee_App.hpp"
#include "../../include/Game.hpp"
#include "../../include/inventory/Inventory.hpp"
#include "../../include/inventory/InventoryManager.hpp"
#include "../../include/phone/phone.hpp"

#if SFML_VERSION_MAJOR >= 3
static float rectLeft(const sf::FloatRect& r) { return r.position.x; }
static float rectTop(const sf::FloatRect& r) { return r.position.y; }
static float rectWidth(const sf::FloatRect& r) { return r.size.x; }
static float rectHeight(const sf::FloatRect& r) { return r.size.y; }
#else
static float rectLeft(const sf::FloatRect& r) { return r.left; }
static float rectTop(const sf::FloatRect& r) { return r.top; }
static float rectWidth(const sf::FloatRect& r) { return r.width; }
static float rectHeight(const sf::FloatRect& r) { return r.height; }
#endif

Shop::Shop() : Shop_Sprite(Shop_Texture)
{
	if (!Shop_Texture.loadFromFile("assets/textures/Shoppiee_App.png"))
	{
		std::cerr << "ERROR: Failed to load Shoppiee_App.png \n";
	}

	Shop_Sprite.setTexture(Shop_Texture, true);
	Shop_Sprite.setPosition({ 230.f, 10.f });
	Shop_Sprite.setScale({ 6.5f, 4.f });

	//close rectangl e
	Shop_Close.setFillColor({ 255, 0, 0, 128 });
	Shop_Close.setSize({ 70.f,55.f });
	Shop_Close.setPosition({ 1810.f, 10.f });

	if (!Buy_Sign_Texture.loadFromFile("assets/textures/Buy_Sign.png"))
	{
		std::cerr << "ERROR: Failed to load Buy_Sign.png \n";
	}

	// Preventing vector reallocation from moving ShopItems and invalidating
	// sf::Sprite texture binding stored as internal pointer
	items.reserve(8);

	// Items for the shop app
	items.emplace_back();
	ShopItems& item1 = items.back();
	item1.name = "TestChair";
	item1.position = { 420.f, 180.f };
	item1.rect.setSize({ 120.f, 120.f });
	item1.rect.setPosition(item1.position);
	item1.rect.setFillColor({ 128, 128, 128 });

	if (!item1.texture.loadFromFile("assets/ItemTextures/TestImage.png"))
	{
		std::cerr << "ERROR: Failed to load TestImage.png \n";
	}
	else
	{
		item1.sprite.setTexture(item1.texture, true);
		item1.sprite.setPosition(item1.position);
		item1.sprite.setScale({ 2.f, 2.f });
	}
	if (Buy_Sign_Texture.getSize().x > 0)
	{
		item1.buySign.setTexture(Buy_Sign_Texture, true);
		item1.buySign.setScale({ 2.f, 2.f });

		sf::FloatRect itemSpriteBounds = item1.sprite.getGlobalBounds();
		if (rectWidth(itemSpriteBounds) <= 0.f || rectHeight(itemSpriteBounds) <= 0.f)
		{
			itemSpriteBounds = item1.rect.getGlobalBounds();
		}
		const sf::FloatRect signBounds = item1.buySign.getGlobalBounds();
		item1.buySign.setPosition({
			rectLeft(itemSpriteBounds) + (rectWidth(itemSpriteBounds) - rectWidth(signBounds)) * 0.5f,
			rectTop(itemSpriteBounds) + rectHeight(itemSpriteBounds) + 8.f
		});
	}

	items.emplace_back();
	ShopItems& item2 = items.back();
	item2.name = "Weed_Plant";
	item2.position = { 640.f,180.f };
	item2.rect.setSize({ 120.f,120.f });
	item2.rect.setPosition(item2.position);
	item2.rect.setFillColor({ 128, 128, 128 });

	if (!item2.texture.loadFromFile("assets/textures/Weed_Plant_Inventory.png"))
	{
		std::cerr << "ERROR: Failed to load Weed_Plant_Inventory.png \n";
	}
	else
	{
		item2.sprite.setTexture(item2.texture, true);
		item2.sprite.setPosition(item2.position);
		item2.sprite.setScale({ 2.f, 2.f });
	}
	if (Buy_Sign_Texture.getSize().x > 0)
	{
		item2.buySign.setTexture(Buy_Sign_Texture, true);
		item2.buySign.setScale({ 2.f, 2.f });

		sf::FloatRect itemSpriteBounds = item2.sprite.getGlobalBounds();
		if (rectWidth(itemSpriteBounds) <= 0.f || rectHeight(itemSpriteBounds) <= 0.f)
		{
			itemSpriteBounds = item2.rect.getGlobalBounds();
		}
		const sf::FloatRect signBounds = item2.buySign.getGlobalBounds();
		item2.buySign.setPosition({
			rectLeft(itemSpriteBounds) + (rectWidth(itemSpriteBounds) - rectWidth(signBounds)) * 0.5f,
			rectTop(itemSpriteBounds) + rectHeight(itemSpriteBounds) + 8.f
		});
	}
	
}

void Shop::update(const sf::Vector2f& mouseWorld, phone& phoneInstance, Inventory& inventory, InventoryManager& inventoryManager)
{
	const bool leftMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	const bool isFreshLeftClick = leftMouseDown && !wasLeftMouseDown;

	if (showInventoryFullText && inventoryTextTimer.getElapsedTime().asSeconds() > 1.6f)
	{
		showInventoryFullText = false;
	}

	if (Shop_Close.getGlobalBounds().contains(mouseWorld) && isFreshLeftClick)
	{
		isShopAppOpen = false;
		phoneInstance.Shop_App_Open = false;
		phoneInstance.isPhoneHidden = false;     // show the phone icons again
		wasLeftMouseDown = leftMouseDown;
		return;
	}

	if (isFreshLeftClick)
	{
		for (ShopItems& item : items)
		{
			if (!item.buySign.getGlobalBounds().contains(mouseWorld))
			{
				continue;
			}

			const bool wasAdded = inventoryManager.giveItem(inventory, item.name, 1);
			if (!wasAdded)
			{
				showInventoryFullText = true;
				inventoryTextTimer.restart();
			}
			break;
		}
	}

	wasLeftMouseDown = leftMouseDown;
}

void Shop::draw(sf::RenderWindow& window, const sf::Font& font)
{
	window.draw(Shop_Sprite);

	for (ShopItems& item : items)
	{
		window.draw(item.rect);
		window.draw(item.sprite);
		window.draw(item.buySign);
	}

	window.draw(Shop_Close);

	if (showInventoryFullText)
	{
		sf::Text inventoryFullText(font, "Inventory Full");
		inventoryFullText.setCharacterSize(28);
		inventoryFullText.setFillColor(sf::Color::Red);
		inventoryFullText.setPosition({ 820.f, 110.f });
		window.draw(inventoryFullText);
	}
}
