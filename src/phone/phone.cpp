#include "../../include/phone/phone.hpp"
#include "../../include/Game.hpp"
#include "../../include/phone/IDApp.hpp"

#include <iostream>
#include <utility>


phone::phone(): phoneSprite(phoneTexture){
	if (!phoneTexture.loadFromFile("assets/textures/Phone.png"))
	{
		std::cerr << "Error: Failed to load Phone.png\n";
	}
	phoneSprite = sf::Sprite(phoneTexture);

    if (!Bank_App_Texture.loadFromFile("assets/textures/Bank_App.png"))
    {
        std::cerr << "Error: Failed to load Bank_App.png\n";
    }

    if (!Shop_App_Texture.loadFromFile("assets/textures/shop_App.png"))
    {
        std::cerr << "Error: Failed to load shop_App.png\n";
    }

    if (!Business_App_Texture.loadFromFile("assets/textures/Business_App.png"))
    {
        std::cerr << "Error: Failed to load Business_App.png\n";
    }

    if (!Illegal_App_Texture.loadFromFile("assets/textures/illegal_App.png"))
    {
        std::cerr << "Error: Failed to load illegal_App.png\n";
    }

    if (!ID_App_Texture.loadFromFile("assets/textures/ID_App.png"))
    {
        std::cerr << "Error: Failed to load ID_App.png\n";
    }
    
    //wanted to follow good coding habits
	phoneSprite.setPosition		    ({ 1500.f, 500.f });
	phoneSprite.setScale		    ({ 4.f, 4.f });

    Bank_App_Rect.setSize           ({ 64.f, 64.f });
    Shop_App_Rect.setSize           ({ 64.f, 64.f });
    ID_App_Rect.setSize             ({ 64.f, 64.f });
    Illegal_App_Rect.setSize        ({ 64.f, 64.f });
    Business_App_Rect.setSize       ({ 64.f, 64.f });

    Bank_App_Rect.setPosition       ({ 1650.f, 600.f });
    Shop_App_Rect.setPosition       ({ 1750.f, 600.f });
    ID_App_Rect.setPosition         ({ 1650.f, 700.f });
    Illegal_App_Rect.setPosition    ({ 1750.f, 700.f });
    Business_App_Rect.setPosition   ({ 1650.f, 800.f });

    //Bank_App_Rect.setFillColor      ({ 255, 0, 0, 128 });     // visible red for testing
    //Shop_App_Rect.setFillColor      ({ 0, 255, 0, 128 });
    //ID_App_Rect.setFillColor        ({ 0, 0, 255, 128 });
    //Illegal_App_Rect.setFillColor   ({ 255, 255, 0, 128 });
    //Business_App_Rect.setFillColor  ({ 255, 0, 255, 128 });

	Bank_App_Rect.setTexture        (&Bank_App_Texture);
	Shop_App_Rect.setTexture        (&Shop_App_Texture);
	ID_App_Rect.setTexture          (&ID_App_Texture);
	Illegal_App_Rect.setTexture     (&Illegal_App_Texture);
	Business_App_Rect.setTexture    (&Business_App_Texture);

	sf::FloatRect bankAppBounds     = Bank_App_Rect.getGlobalBounds();
	sf::FloatRect shopAppBounds     = Shop_App_Rect.getGlobalBounds();
	sf::FloatRect idAppBounds       = ID_App_Rect.getGlobalBounds();
	sf::FloatRect illegalAppBounds  = Illegal_App_Rect.getGlobalBounds();
	sf::FloatRect businessAppBounds = Business_App_Rect.getGlobalBounds();

    bool AppOpened = false;
}

void phone::update(const sf::Vector2f& mouseWorld, sf::RenderWindow& window)
{
    const bool leftMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    const bool isFreshLeftClick = leftMouseDown && !wasLeftMouseDown;

    if (IDApplicationOpen)
    {
        idApp.update(mouseWorld, *this);
        wasLeftMouseDown = leftMouseDown;
        return; // block icon clicks while app is open
    }

    if (Bank_App_Rect.getGlobalBounds().contains(mouseWorld)) {
        if (isFreshLeftClick) {
            std::cout << "Bank App Clicked\n";
        }
    }

    if (Shop_App_Rect.getGlobalBounds().contains(mouseWorld)) {
        if (isFreshLeftClick) {
            std::cout << "Shop App Clicked\n";
            pendingPurchasedItem = "TestChair";
        }
    }

    if (ID_App_Rect.getGlobalBounds().contains(mouseWorld)) {
        if (isFreshLeftClick) {
            std::cout << "ID App Clicked\n";
            idApp.is_ID_App_Open = true;
            IDApplicationOpen = true;
        }
    }

    if (Illegal_App_Rect.getGlobalBounds().contains(mouseWorld)) {
        if (isFreshLeftClick) {
            std::cout << "Illegal App Clicked\n";
        }
    }

    if (Business_App_Rect.getGlobalBounds().contains(mouseWorld)) {
        if (isFreshLeftClick) {
            std::cout << "Business App Clicked\n";
        }
    }

    wasLeftMouseDown = leftMouseDown;
}

void phone::draw(sf::RenderWindow& window)
{
    window.draw(phoneSprite);

    if (!isPhoneHidden && !IDApplicationOpen)
    {
        window.draw(Bank_App_Rect);
        window.draw(Shop_App_Rect);
        window.draw(ID_App_Rect);
        window.draw(Illegal_App_Rect);
        window.draw(Business_App_Rect);
    }

    if (IDApplicationOpen)
    {
        idApp.draw(window);
    }
}

std::string phone::consumePurchasedItem()
{
    std::string purchasedItem = std::move(pendingPurchasedItem);
    pendingPurchasedItem.clear();
    return purchasedItem;
}
