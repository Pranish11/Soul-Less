#include "../../include/phone/phone.hpp"
#include "../../include/Game.hpp"
#include <iostream>


phone::phone(): phoneSprite(phoneTexture) {
	if (!phoneTexture.loadFromFile("assets/textures/Phone.png"))
	{
		std::cerr << "Error: Failed to load Phone.png\n";
	}
	phoneSprite = sf::Sprite(phoneTexture);


	phoneSprite.setPosition		({ 1500.f, 500.f });
	phoneSprite.setScale		({ 4.f, 4.f });

    Bank_App_Rect.setSize       ({ 300.f, 200.f });
    Shop_App_Rect.setSize       ({ 300.f, 200.f });
    ID_App_Rect.setSize         ({ 300.f, 200.f });
    Illegal_App_Rect.setSize    ({ 300.f, 200.f });
    Business_App_Rect.setSize   ({ 300.f, 200.f });

    Bank_App_Rect.setPosition       ({ 1600.f, 600.f });
    Shop_App_Rect.setPosition       ({ 1700.f, 600.f });
    ID_App_Rect.setPosition         ({ 1600.f, 700.f });
    Illegal_App_Rect.setPosition    ({ 1700.f, 700.f });
    Business_App_Rect.setPosition   ({ 1650.f, 800.f });

    Bank_App_Rect.setFillColor      ({ 255, 0, 0, 128 });     // visible red for testing
    Shop_App_Rect.setFillColor      ({ 0, 255, 0, 128 });
    ID_App_Rect.setFillColor        ({ 0, 0, 255, 128 });
    Illegal_App_Rect.setFillColor   ({ 255, 255, 0, 128 });
    Business_App_Rect.setFillColor  ({ 255, 0, 255, 128 });
}


void phone::update()
{

}

void phone::draw(sf::RenderWindow& window)
{
		window.draw(phoneSprite);

		//for testing purposes, will be replaced with actual app icons and functionality later
        if (isPhoneHidden == false) {
            window.draw(Bank_App_Rect);
            window.draw(Shop_App_Rect);
            window.draw(ID_App_Rect);
            window.draw(Illegal_App_Rect);
            window.draw(Business_App_Rect);
        }
}