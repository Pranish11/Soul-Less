#include "../include/Game.hpp"
#include <iostream>
#include <string>

Game::Game() : window(sf::VideoMode({ 1920, 1080 }), "Game", sf::State::Fullscreen), inventory(5, 5, 50.f, { 100.f, 100.f }) {
    if (!Pixelfont.openFromFile("assets/fonts/Silkscreen-Regular.ttf")) {
        std::cerr << "FAILED to load font\n";
    }
    pausemenu = std::make_unique<Pause>(Pixelfont);
    Human_Player_Phone = std::make_unique<phone>(Pixelfont);
    Money_display = std::make_unique<money>(Pixelfont);
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
                // Handle P key for Phone toggle
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
			            menu.StartBtnFunction(window, saveManager.hasSave());

			            if (menu.isStartClicked) {
			                // Continue: load save if it exists.
			                const SaveManager::Result result = saveManager.load(HumanPlayer, *Money_display, inventory, itemPlacer, gametile, *Human_Player_Phone);
			                std::cout << (result.ok ? "[LOAD OK] " : "[LOAD FAIL] ") << result.message << "\n";
			                if (result.ok) {
			                    isinmenu = false;
			                }
			            }
			            else if (menu.isLoadClicked) {
			                // New game
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
	                const PauseAction pauseAction = pausemenu->PauseDraw(window);
	                if (pauseAction == PauseAction::ContinueGame) {
	                    ispaused = false;
	                }
	                else if (pauseAction == PauseAction::SaveGame) {
	                    const SaveManager::Result result = saveManager.save(HumanPlayer, *Money_display, inventory, itemPlacer, *Human_Player_Phone);
	                    std::cout << (result.ok ? "[SAVE OK] " : "[SAVE FAIL] ") << result.message << "\n";
	                }
	                else if (pauseAction == PauseAction::ExitToMainMenu) {
	                    ispaused = false;
	                    isPhoneOpen = false;
	                    inventoryOpen = false;
	                    isinmenu = true;
	                }
                inventoryOpen = false;
                Money_display->cashDraw(window);
            }

            //Phone
            if (isPhoneOpen && ispaused == false && inventoryOpen == false)
            {
				Human_Player_Phone->isPhoneHidden = false;       //for boxes to be visible during testing, will be removed later. if not needed remove this line
                Human_Player_Phone->update(mouseWorld, window, inventory, inventoryManager, *Money_display);
                Human_Player_Phone->draw(window, Pixelfont);
            }

            // Draw inventory if open
            if (!ispaused && inventoryOpen) {
                inventory.draw(window);
                inventory.update(mouseWorld);
                selectedInventoryItem = inventory.getSelectedItemName();
            }

            itemPlacer.update(mouseWorld, inventory, gametile, !isinmenu && !ispaused && !isPhoneOpen && !inventoryOpen);
            if (!ispaused) {
                itemPlacer.generateCash(*Money_display, deltaTime);
                Human_Player_Phone->generateBusinessIncome(*Money_display, deltaTime);
            }

            //day and night
            timecycle.update();
            timecycle.draw(window);

            // Money display will be hidden in menu/paused/inventory/phone
            if (!ispaused && !isPhoneOpen && !inventoryOpen) {
                Money_display->update();
                Money_display->cashDraw(window);
            }
        }
        window.setMouseCursorVisible(true);
        window.display();
    }
}
