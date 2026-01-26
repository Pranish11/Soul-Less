#include "../include/Game.hpp"
#include "../include/MenuState.hpp"
#include "../include/Tiles.hpp"
#include "../include/Pause.hpp"

#include <iostream>

Game::Game() : window(sf::VideoMode({ 1920, 1080 }), "Game", sf::State::Fullscreen) {}

void Game::run()
{
    MenuState menu;
    Tiles gametile;
    bool isinmenu = true;
	Pause pausemenu;
	bool ispaused = false;


    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        // Menu display
        if(isinmenu){
            menu.StartBtnFunction(window);
        }

        if (menu.isStartClicked == true)
        {
            gametile.draw(window);
            isinmenu = false;

            if (isinmenu == false && ispaused == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                pausemenu.PauseDraw(window);
				bool ispaused = true;
            }
        }
        window.display();
    }
}
