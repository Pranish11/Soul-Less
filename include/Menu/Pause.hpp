#pragma once

#include <SFML/Graphics.hpp>

enum class PauseAction {
    None,
    ContinueGame,
    ExitToMainMenu
};

class Pause {
public:
    Pause(const sf::Font& f);
    PauseAction PauseDraw(sf::RenderWindow& window);
    bool isPaused = false;

private:
    const sf::Font& Pixelfont;
    sf::RectangleShape Continue;
    sf::RectangleShape Save;
    sf::RectangleShape Exit;
    bool wasLeftMouseDown = false;
};
