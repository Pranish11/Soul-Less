#include "../include/Game.hpp"
#include "../include/MenuState.hpp"
#include "../include/Tiles.hpp"
#include "../include/Pause.hpp"
#include "../include/Player.hpp"
#include "../include/DayAndNight.hpp"

#include <iostream>
#include <memory>

Game::Game() : window(sf::VideoMode({ 1920, 1080 }), "Game", sf::State::Fullscreen), inventory(5, 5, 50.f, { 100.f, 100.f }) {
    if (!Pixelfont.openFromFile("assets/fonts/Silkscreen-Regular.ttf")) {
        std::cerr << "FAILED to load font\n";
    }
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

    bool isinmenu = true;
    bool ispaused = false;

    Inventory inventory(4, 5, 64.0f, sf::Vector2f(100.f, 100.f));
    auto TestChair = std::make_unique<Item>("TestChair", "assets/ItemTextures/TestImage.png");
    inventory.registerItem(TestChair.get());
    inventory.addItem("TestChair", 1);



    while (window.isOpen())
    {
        sf::Time dt = deltaClock.restart();
        float deltaTime = dt.asSeconds();

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
                HumanPlayer.draw(window);
            }
            else {
                gametile.draw(window);
                HumanPlayer.draw(window);
                pausemenu.PauseDraw(window);
				inventoryOpen = false;
            }

            // Draw inventory if open
            if (!ispaused && inventoryOpen) {
                inventory.draw(window);
                inventory.update(mouseWorld);
            }
            //day and night
            timecycle.update();
            timecycle.draw(window);
        }


        window.setMouseCursorVisible(true);
        mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        window.display();
    }
}