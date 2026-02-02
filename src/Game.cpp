#include "../include/Game.hpp"
#include "../include/MenuState.hpp"
#include "../include/Tiles.hpp"
#include "../include/Pause.hpp"
#include "../include/Player.hpp"
#include <iostream>

Game::Game() : window(sf::VideoMode({ 1920, 1080 }), "Game", sf::State::Fullscreen) {
    if (!Pixelfont.openFromFile("assets/fonts/Silkscreen-Regular.ttf")) {
        std::cerr << "FAILED to load font\n";
    }
}

void Game::run()
{
    MenuState menu;
    Tiles gametile;
    Pause pausemenu(Pixelfont);
    Player HumanPlayer;

    bool isinmenu = true;
    bool ispaused = false;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            // Handle Escape key press
            if (event->is<sf::Event::KeyPressed>()) {
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                    if (!isinmenu) {
                        ispaused = !ispaused;
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
                HumanPlayer.update();
                gametile.draw(window);
                HumanPlayer.draw(window);
            }
            else {
                gametile.draw(window);
                HumanPlayer.draw(window);
                pausemenu.PauseDraw(window);
            }
        }

        window.display();
    }
}