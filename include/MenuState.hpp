#pragma once

#ifndef PROJECT_2_MENUSTATE_HPP
#define PROJECT_2_MENUSTATE_HPP

#include <SFML/Graphics.hpp>

class MenuState {
public:
    MenuState() = default;
    void StartBtnFunction(sf::RenderWindow& window);
    bool IsInStartMenu = false;
    bool IsInLoadMenu = false;

private:
    sf::RectangleShape Start;
    sf::RectangleShape Quit;
    sf::RectangleShape Load;
    bool isVisible;

};

#endif // PROJECT_2_MENUSTATE_HPP
