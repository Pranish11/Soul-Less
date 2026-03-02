#pragma once
#include "SFML/Graphics.hpp"
#include "IDApp.hpp"
#include <string>

class phone {
public:
    phone();
    void update(const sf::Vector2f& mouseWorld, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    std::string consumePurchasedItem();
    bool isPhoneHidden = true;
    bool IDApplicationOpen = false;

    bool AppOpened = false;
    sf::Texture phoneTexture;

private:
    sf::Sprite phoneSprite;
    sf::Texture Bank_App_Texture;
    sf::Texture Shop_App_Texture;
    sf::Texture ID_App_Texture;
    sf::Texture Illegal_App_Texture;
    sf::Texture Business_App_Texture;
    sf::RectangleShape Bank_App_Rect;
    sf::RectangleShape Shop_App_Rect;
    sf::RectangleShape ID_App_Rect;
    sf::RectangleShape Illegal_App_Rect;
    sf::RectangleShape Business_App_Rect;

    ID idApp; 
    std::string pendingPurchasedItem;
    bool wasLeftMouseDown = false;
};
