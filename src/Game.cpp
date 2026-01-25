#include "../include/Game.hpp"
#include "../include/MenuState.hpp"
#include "../include/Tiles.hpp"
#include <iostream>

Game::Game() : window(sf::VideoMode({ 1920, 1080 }), "Game", sf::State::Fullscreen) {}

void Game::run()
{
    MenuState menu;
    Tiles gametile;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        // Menu display
        menu.StartBtnFunction(window);

        if (menu.isStartClicked==true)
        {
            gametile.draw(window);
        }
        
		// Mouse position
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            std::cout << mousePos.x << " " << mousePos.y << std::endl;
        }

        window.display();
    }
}

