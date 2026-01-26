#pragma once
#ifndef SOUL_LESS_PAUSE_HPP
#define	SOUL_LESS_PAUSE_HPP

#include <SFML/Graphics.hpp>

class Pause {
public:
	Pause() = default;
	void PauseDraw(sf::RenderWindow& window);
	bool isPaused = false;

private:
	sf::RectangleShape Continue;
	sf::RectangleShape Save;
	sf::RectangleShape Exit;
};

#endif // !SOUL_LESS_PAUSE_HPP

