#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "inventory/Inventory.hpp"
#include "inventory/InventoryManager.hpp"
#include "items/Place.hpp"
#include "Menu/MenuState.hpp"
#include "level/Tiles.hpp"
#include "Menu/Pause.hpp"
#include "player/Player.hpp"
#include "Day_Night_Cycle/DayAndNight.hpp"
#include "phone/phone.hpp"
#include "Money/Money.hpp"
#include "save/SaveManager.hpp"

class Game {
public:
    Game();
    void run();

    const sf::Vector2f& getMouseWorld() const;
private:
    sf::RenderWindow window;
    sf::Font Pixelfont;
    Inventory inventory;
    InventoryManager inventoryManager;
    place itemPlacer;
    MenuState menu;
    Tiles gametile;
    Player HumanPlayer;
    DayAndNight timecycle;

    
	std::unique_ptr<Pause> pausemenu;
	std::unique_ptr<phone> Human_Player_Phone;
	std::unique_ptr<money> Money_display;
	SaveManager saveManager;
    bool inventoryOpen = false;
    sf::Vector2f mouseWorld;
    std::string selectedInventoryItem;
	};
