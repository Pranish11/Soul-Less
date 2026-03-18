#pragma once

#include <SFML/Graphics.hpp>

class MenuState {
public:
	    MenuState() = default;
	    void StartBtnFunction(sf::RenderWindow& window, bool canContinue);
	    bool isStartClicked = false;
	    bool isLoadClicked = false;

private:
    sf::RectangleShape Start;
    sf::RectangleShape Quit;
    sf::RectangleShape Load;
    bool isVisible = false;
    bool wasLeftMouseDown = false;
};
