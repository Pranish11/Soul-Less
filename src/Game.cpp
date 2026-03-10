#include "../include/Game.hpp"
#include "../include/Menu/MenuState.hpp"
#include "../include/level/Tiles.hpp"
#include "../include/Menu/Pause.hpp"
#include "../include/player/Player.hpp"
#include "../include/Day_Night_Cycle/DayAndNight.hpp"
#include "../include/phone/phone.hpp"

#include <iostream>
#include <string>

Game::Game() : window(sf::VideoMode({ 1920, 1080 }), "Game", sf::State::Fullscreen), inventory(5, 5, 50.f, { 100.f, 100.f }) {
    if (!Pixelfont.openFromFile("assets/fonts/Silkscreen-Regular.ttf")) {
        std::cerr << "FAILED to load font\n";
    }
    inventory.centerInWindow(window.getSize());
    window.setFramerateLimit(144);
}

sf::Clock deltaClock;

const sf::Vector2f& Game::getMouseWorld() const
{
    return mouseWorld;
}

void Game::run()
{
    MenuState menu;
    Tiles gametile;
    Pause pausemenu(Pixelfont);
    Player HumanPlayer;
    DayAndNight timecycle;
	phone Human_Player_Phone;

    bool isinmenu = true;
    bool ispaused = false;
    bool isPhoneOpen = false;

    inventoryManager.registerDefaultItems(inventory);
    //Broom to remove place items
    inventoryManager.giveItem(inventory, "Broom", 1);


    while (window.isOpen())
    {
        sf::Time dt = deltaClock.restart();
        float deltaTime = dt.asSeconds();
        mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            // Handle Escape key press
            if (event->is<sf::Event::KeyPressed>()) {
                auto keyEvent = event->getIf<sf::Event::KeyPressed>();
                if (keyEvent->code == sf::Keyboard::Key::Escape) {
                    if (!isinmenu) {
                        ispaused = !ispaused;
                    }
                }
                // Handle E key for inventory toggle
                if (keyEvent->code == sf::Keyboard::Key::E) {
                    if (!isinmenu && !ispaused) {
                        inventoryOpen = !inventoryOpen;
                    }
                }
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                {
                    if (keyPressed->code == sf::Keyboard::Key::P)
                    {
                        isPhoneOpen = !isPhoneOpen; // toggle
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        // Menu display
        if (isinmenu) {
            menu.StartBtnFunction(window);

            if (menu.isStartClicked) {
                isinmenu = false;
            }
        }

        // In game
        else {
            if (!ispaused) {
                HumanPlayer.update(deltaTime, gametile);
                gametile.draw(window);
                itemPlacer.draw(window);
                HumanPlayer.draw(window);
            }
            else {
                gametile.draw(window);
                itemPlacer.draw(window);
                HumanPlayer.draw(window);
                const PauseAction pauseAction = pausemenu.PauseDraw(window);
                if (pauseAction == PauseAction::ContinueGame) {
                    ispaused = false;
                }
                else if (pauseAction == PauseAction::ExitToMainMenu) {
                    ispaused = false;
                    isPhoneOpen = false;
                    inventoryOpen = false;
                    isinmenu = true;
                }
				inventoryOpen = false;
            }

            //Phone
            if (isPhoneOpen && ispaused == false && inventoryOpen == false)
            {
				Human_Player_Phone.isPhoneHidden = false;       //for boxes to be visible during testing, will be removed later. if not needed remove this line
                Human_Player_Phone.update(mouseWorld, window, inventory, inventoryManager);
                Human_Player_Phone.draw(window, Pixelfont);
            }

            // Draw inventory if open
            if (!ispaused && inventoryOpen) {
                inventory.draw(window);
                inventory.update(mouseWorld);
                selectedInventoryItem = inventory.getSelectedItemName();
            }

            itemPlacer.update(mouseWorld, inventory, gametile, !isinmenu && !ispaused && !isPhoneOpen && !inventoryOpen);

            //day and night
            timecycle.update();
            timecycle.draw(window);
        }
        window.setMouseCursorVisible(true);
        window.display();
    }
}
