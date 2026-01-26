#pragma once

#ifndef PROJECT_2_MENUSTATE_HPP
#define PROJECT_2_MENUSTATE_HPP

#include <SFML/Graphics.hpp>

class MenuState {
public:
    MenuState() = default;
    void StartBtnFunction(sf::RenderWindow& window);
    bool isStartClicked = false;
	sf::Font Pixelfont;

private:
    sf::RectangleShape Start;
    sf::RectangleShape Quit;
    sf::RectangleShape Load;
    bool isVisible = false;

};

#endif // PROJECT_2_MENUSTATE_HPP
