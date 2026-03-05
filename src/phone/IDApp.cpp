#include "../../include/phone/IDApp.hpp"
#include "../../include/phone/phone.hpp"
#include <iostream>

ID::ID() : ID_Sprite(ID_Texture)
{
    if (!ID_Texture.loadFromFile("assets/textures/ID_Page_Phone.png"))
    {
        std::cerr << "Error: Failed to load ID_Page_Phone.png\n";
    }

    ID_Sprite.setTexture(ID_Texture, true);
    ID_Sprite.setPosition({ 1500.f, 500.f }); // same as phone to cover it
    ID_Sprite.setScale({ 4.f, 4.f });

    ID_App_Close.setSize({ 32.f, 32.f });
    ID_App_Close.setPosition({ 1850.f, 550.f });
    ID_App_Close.setFillColor({ 255, 0, 0, 128 });
}

void ID::update(const sf::Vector2f& mouseWorld, phone& phoneInstance)
{
    if (ID_App_Close.getGlobalBounds().contains(mouseWorld))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            is_ID_App_Open = false;
            phoneInstance.IDApplicationOpen = false; // close the  ID app
            phoneInstance.isPhoneHidden = false;     // show the phone icons again
        }
    }
}

void ID::draw(sf::RenderWindow& window)
{
    std::cerr << "Drawing ID sprite at: " << ID_Sprite.getPosition().x << ", " << ID_Sprite.getPosition().y << "\n";
    std::cerr << "Texture size: " << ID_Texture.getSize().x << "x" << ID_Texture.getSize().y << "\n";
    if (is_ID_App_Open)
    {
        window.draw(ID_Sprite);
        //window.draw(ID_App_Close);    //for testing
    }
}
