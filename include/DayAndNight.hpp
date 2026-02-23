#pragma once
#include "SFML/Graphics.hpp"

class DayAndNight {
public:
	DayAndNight();
	void update();
	sf::Clock dayNightClock;
	float daylenght;
	void draw(sf::RenderWindow& window);

	sf::RectangleShape nightOverlay;

};