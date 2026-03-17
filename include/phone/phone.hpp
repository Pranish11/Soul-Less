#pragma once
#include "SFML/Graphics.hpp"
#include "IDApp.hpp"
#include "Shopiee_App.hpp"
#include "Bank_App.hpp"
#include "Business_App.hpp"
#include "Gamble.hpp"
#include <string>

class Inventory;
class InventoryManager;
class money;

class phone {
public:
    phone(const sf::Font& font);
    void update(const sf::Vector2f& mouseWorld, sf::RenderWindow& window, Inventory& inventory, InventoryManager& inventoryManager, money& moneyInstance);
    void draw(sf::RenderWindow& window, const sf::Font& font);
    void generateBusinessIncome(money& moneyInstance, float deltaTime);
    bool isPhoneHidden = true;
    bool IDApplicationOpen = false;
    bool Shop_App_Open = false;
    bool Bank_App_Open = false;
    bool Business_App_Open = false;
    bool Gamble_App_Open = false;

    bool AppOpened = false;
    sf::Texture phoneTexture;

private:
    //made this look a little bit cleaner
    sf::Sprite              phoneSprite;
    sf::Texture             Bank_App_Texture;
    sf::Texture             Shop_App_Texture;
    sf::Texture             ID_App_Texture;
    sf::Texture             Illegal_App_Texture;
    sf::Texture             Business_App_Texture;
    sf::RectangleShape      Bank_App_Rect;
    sf::RectangleShape      Shop_App_Rect;
    sf::RectangleShape      ID_App_Rect;
    sf::RectangleShape      Illegal_App_Rect;
    sf::RectangleShape      Business_App_Rect;

    ID                      idApp; 
    Shop                    ShopApp;
    bank                    BankApp;
    BusinessApp             Business;
    gamble                  Gamble;

    bool wasLeftMouseDown = false;
};
