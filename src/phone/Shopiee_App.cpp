#include <iostream>
#include <string>

#include "../../include/phone/Shopiee_App.hpp"
#include "../../include/Game.hpp"
#include "../../include/inventory/Inventory.hpp"
#include "../../include/inventory/InventoryManager.hpp"
#include "../../include/phone/phone.hpp"
#include "../../include/Money/Money.hpp"

// MOST OF THE CODE FOR THIS FILES IS MADE BY CHATGPT, Idk wtf is going on 

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
	item1.price = 200;
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


	// Item 2 - Bed
	items.emplace_back();
	ShopItems& item2 = items.back();
	item2.name = "Bed";
	item2.price = 900;
	item2.position = { 640.f,180.f };
	item2.rect.setSize({ 120.f,120.f });
	item2.rect.setPosition(item2.position);
	item2.rect.setFillColor({ 128, 128, 128 });

	if (!item2.texture.loadFromFile("assets/ItemTextures/Bed.png"))
	{
		std::cerr << "ERROR: Failed to load Bed.png \n";
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
	
	//item3 table
	items.emplace_back();
	ShopItems& item3 = items.back();
	item3.name = "Table";
	item3.price = 400;
	item3.position = { 860,180 };
	item3.rect.setSize({120.f,120.f});
	item3.rect.setPosition(item3.position);
	item3.rect.setFillColor({ 128, 128, 128 });

	if (!item3.texture.loadFromFile("assets/ItemTextures/Table.png"))
	{
		std::cerr << "ERROR: Failed to load Table.png \n";
	}
	else
	{
		item3.sprite.setTexture(item3.texture, true);
		item3.sprite.setPosition(item3.position);
		item3.sprite.setScale({ 2.f, 2.f });
	}
	if (Buy_Sign_Texture.getSize().x > 0)
	{
		item3.buySign.setTexture(Buy_Sign_Texture, true);
		item3.buySign.setScale({ 2.f, 2.f });

		sf::FloatRect itemSpriteBounds = item3.sprite.getGlobalBounds();
		if (rectWidth(itemSpriteBounds) <= 0.f || rectHeight(itemSpriteBounds) <= 0.f)
		{
			itemSpriteBounds = item3.rect.getGlobalBounds();
		}
		const sf::FloatRect signBounds = item3.buySign.getGlobalBounds();
		item3.buySign.setPosition({
			rectLeft(itemSpriteBounds) + (rectWidth(itemSpriteBounds) - rectWidth(signBounds)) * 0.5f,
			rectTop(itemSpriteBounds) + rectHeight(itemSpriteBounds) + 8.f
		});
	}

	// Item 4 - coke table
	items.emplace_back();
	ShopItems& item4 = items.back();
	item4.name = "Coke";
	item4.price = 250000;
	item4.position = { 1080,180 };
	item4.rect.setSize({ 120.f,120.f });
	item4.rect.setPosition(item4.position);
	item4.rect.setFillColor({ 128, 128, 128 });

	if (!item4.texture.loadFromFile("assets/ItemTextures/coke_table.png"))
	{
		std::cerr << "ERROR: Failed to load coke_table.png \n";
	}
	else
	{
		item4.sprite.setTexture(item4.texture, true);
		item4.sprite.setPosition(item4.position);
		item4.sprite.setScale({ 2.f, 2.f });
	}
	if (Buy_Sign_Texture.getSize().x > 0)
	{
		item4.buySign.setTexture(Buy_Sign_Texture, true);
		item4.buySign.setScale({ 2.f, 2.f });

		sf::FloatRect itemSpriteBounds = item4.sprite.getGlobalBounds();
		if (rectWidth(itemSpriteBounds) <= 0.f || rectHeight(itemSpriteBounds) <= 0.f)
		{
			itemSpriteBounds = item4.rect.getGlobalBounds();
		}
		const sf::FloatRect signBounds = item4.buySign.getGlobalBounds();
		item4.buySign.setPosition({
			rectLeft(itemSpriteBounds) + (rectWidth(itemSpriteBounds) - rectWidth(signBounds)) * 0.5f,
			rectTop(itemSpriteBounds) + rectHeight(itemSpriteBounds) + 8.f
		});
	}

	//item 5 - Chemical Table
	items.emplace_back();
	ShopItems& item5 = items.back();
	item5.name = "Chemical";
	item5.price = 25000000;
	item5.position = { 420,540 };
	item5.rect.setSize({ 120.f,120.f });
	item5.rect.setPosition(item5.position);
	item5.rect.setFillColor({ 128, 128, 128 });

	if (!item5.texture.loadFromFile("assets/ItemTextures/chemical_table.png"))
	{
		std::cerr << "ERROR: Failed to load chemical_table.png \n";
	}
	else
	{
		item5.sprite.setTexture(item5.texture, true);
		item5.sprite.setPosition(item5.position);
		item5.sprite.setScale({ 2.f, 2.f });
	}
	if (Buy_Sign_Texture.getSize().x > 0)
	{
		item5.buySign.setTexture(Buy_Sign_Texture, true);
		item5.buySign.setScale({ 2.f, 2.f });

		sf::FloatRect itemSpriteBounds = item5.sprite.getGlobalBounds();
		if (rectWidth(itemSpriteBounds) <= 0.f || rectHeight(itemSpriteBounds) <= 0.f)
		{
			itemSpriteBounds = item5.rect.getGlobalBounds();
		}
		const sf::FloatRect signBounds = item5.buySign.getGlobalBounds();
		item5.buySign.setPosition({
			rectLeft(itemSpriteBounds) + (rectWidth(itemSpriteBounds) - rectWidth(signBounds)) * 0.5f,
			rectTop(itemSpriteBounds) + rectHeight(itemSpriteBounds) + 8.f
		});
	}

	//item 6 - Better weed
	items.emplace_back();
	ShopItems& item6 = items.back();
	item6.name = "B_Weed";
	item6.price = 1000;
	item6.position = { 640,540 };
	item6.rect.setSize({ 120.f,120.f });
	item6.rect.setPosition(item6.position);
	item6.rect.setFillColor({ 128, 128, 128 });

	if (!item6.texture.loadFromFile("assets/ItemTextures/Better_Weed.png"))
	{
		std::cerr << "ERROR: Failed to load Better_Weed.png \n";
	}
	else
	{
		item6.sprite.setTexture(item6.texture, true);
		item6.sprite.setPosition(item6.position);
		item6.sprite.setScale({ 2.f, 2.f });
	}
	if (Buy_Sign_Texture.getSize().x > 0)
	{
		item6.buySign.setTexture(Buy_Sign_Texture, true);
		item6.buySign.setScale({ 2.f, 2.f });

		sf::FloatRect itemSpriteBounds = item6.sprite.getGlobalBounds();
		if (rectWidth(itemSpriteBounds) <= 0.f || rectHeight(itemSpriteBounds) <= 0.f)
		{
			itemSpriteBounds = item6.rect.getGlobalBounds();
		}
		const sf::FloatRect signBounds = item6.buySign.getGlobalBounds();
		item6.buySign.setPosition({
			rectLeft(itemSpriteBounds) + (rectWidth(itemSpriteBounds) - rectWidth(signBounds)) * 0.5f,
			rectTop(itemSpriteBounds) + rectHeight(itemSpriteBounds) + 8.f
		});
	}
}

void Shop::update(const sf::Vector2f& mouseWorld, phone& phoneInstance, Inventory& inventory, InventoryManager& inventoryManager, money& moneyInstance)
{
	const bool leftMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	const bool isFreshLeftClick = leftMouseDown && !wasLeftMouseDown;

	if (showInventoryFullText && inventoryTextTimer.getElapsedTime().asSeconds() > 2.0f)
	{
		showInventoryFullText = false;
	}
	if (showNotEnoughFundsText && notEnoughFundsTextTimer.getElapsedTime().asSeconds() > 2.0f)
	{
		showNotEnoughFundsText = false;
	}

	if (Shop_Close.getGlobalBounds().contains(mouseWorld) && isFreshLeftClick)
	{
		isShopAppOpen = false;
		phoneInstance.Shop_App_Open = false;
		phoneInstance.isPhoneHidden = false;     // again show the phone icon
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

			if (item.price > 0 && moneyInstance.cash < item.price)
			{
				showNotEnoughFundsText = true;
				notEnoughFundsTextTimer.restart();
				break;
			}

			const bool wasAdded = inventoryManager.giveItem(inventory, item.name, 1);
			if (!wasAdded)
			{
				showInventoryFullText = true;
				inventoryTextTimer.restart();
				break;
			}

			if (item.price > 0)
			{
				moneyInstance.cash -= item.price;
			}
			break;
		}
	}

	wasLeftMouseDown = leftMouseDown;
}


//gonna put every thing here to draw :), its was easier since i had done it early and the text and price are mostly new
void Shop::draw(sf::RenderWindow& window, const sf::Font& font)
{
	window.draw(Shop_Sprite);

	for (ShopItems& item : items)
	{
		window.draw(item.rect);
		window.draw(item.sprite);
		window.draw(item.buySign);
	}

	sf::Text Chair_Text(font, "Chair");
	sf::Text Chair_Price_Text(font, "Price : $200/-");
	Chair_Text.setPosition({ 420.f, 140.f });
	Chair_Price_Text.setPosition({420.f,330.f});
	Chair_Text.setCharacterSize(16);
	Chair_Price_Text.setCharacterSize(16);
	Chair_Text.setFillColor(sf::Color::Black);
	Chair_Price_Text.setFillColor(sf::Color::Black);

	window.draw(Chair_Price_Text);
	window.draw(Chair_Text);

	sf::Text Bed_Text(font, "Bed");
	sf::Text Bed_Price_Text(font, "Price : $900/-");
	Bed_Text.setPosition({ 640.f, 140.f });
	Bed_Price_Text.setPosition({ 640.f,330.f });
	Bed_Text.setCharacterSize(16);
	Bed_Price_Text.setCharacterSize(16);
	Bed_Text.setFillColor(sf::Color::Black);
	Bed_Price_Text.setFillColor(sf::Color::Black);

	window.draw(Bed_Price_Text);
	window.draw(Bed_Text);

	sf::Text Table_Text(font, "Table");
	sf::Text Table_Price_Text(font, "Price : $400");
	Table_Text.setPosition({ 860.f, 140.f });
	Table_Price_Text.setPosition({ 860.f,330.f });
	Table_Text.setCharacterSize(16);
	Table_Price_Text.setCharacterSize(16);
	Table_Text.setFillColor(sf::Color::Black);
	Table_Price_Text.setFillColor(sf::Color::Black);

	window.draw(Table_Price_Text);
	window.draw(Table_Text);

	sf::Text Coke_Text(font, "Coke");
	sf::Text Coke_Price_Text(font, "Price : $ 250K");
	Coke_Text.setPosition({ 1080.f, 140.f });
	Coke_Price_Text.setPosition({ 1080.f,330.f });
	Coke_Text.setCharacterSize(16);
	Coke_Price_Text.setCharacterSize(16);
	Coke_Text.setFillColor(sf::Color::Black);
	Coke_Price_Text.setFillColor(sf::Color::Black);

	window.draw(Coke_Price_Text);
	window.draw(Coke_Text);

	sf::Text Chemical_Text(font, "Chemical Stuff");
	sf::Text Chemical_Price_Text(font, "Price : $ 25M");
	Chemical_Text.setPosition({ 420.f, 500.f });
	Chemical_Price_Text.setPosition({ 420.f, 690 });
	Chemical_Text.setCharacterSize(16);
	Chemical_Price_Text.setCharacterSize(16);
	Chemical_Text.setFillColor(sf::Color::Black);
	Chemical_Price_Text.setFillColor(sf::Color::Black);

	window.draw(Chemical_Price_Text);
	window.draw(Chemical_Text);

	sf::Text Weed_Text(font, "Better Weed");
	sf::Text Weed_Price_Text(font, "Price : $ 1000");
	Weed_Text.setPosition({ 640.f, 500.f });
	Weed_Price_Text.setPosition({ 640.f, 690 });
	Weed_Text.setCharacterSize(16);
	Weed_Price_Text.setCharacterSize(16);
	Weed_Text.setFillColor(sf::Color::Black);
	Weed_Price_Text.setFillColor(sf::Color::Black);

	window.draw(Weed_Price_Text);
	window.draw(Weed_Text);


	//window.draw(Shop_Close);					// close button rectangle 

	if (showInventoryFullText)
	{
		sf::Text inventoryFullText(font, "Inventory Full");
		inventoryFullText.setCharacterSize(28);
		inventoryFullText.setFillColor(sf::Color::Red);
		inventoryFullText.setPosition({ 820.f, 110.f });
		window.draw(inventoryFullText);
	}

	if (showNotEnoughFundsText)
	{
		sf::Text notEnoughFundsText(font, "Not enough funds");
		notEnoughFundsText.setCharacterSize(28);
		notEnoughFundsText.setFillColor(sf::Color::Red);
		notEnoughFundsText.setPosition({ 780.f, 150.f });
		window.draw(notEnoughFundsText);
	}
}
