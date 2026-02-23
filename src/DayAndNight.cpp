#include <iostream>
#include <cstdint>
#include <cmath>
#include <algorithm>

#include "../include/DayAndNight.hpp"
#include "../include/Game.hpp"

DayAndNight::DayAndNight(): daylenght(60.f),progress(0.f),alpha(0),daySprite(dayTexture),nightSprite(nightTexture)
{
	dayTexture.loadFromFile("assets/textures/Am_time.png");
	nightTexture.loadFromFile("assets/textures/Pm_time.png");

	daySprite.setPosition({ 0.f, 0.f });
	nightSprite.setPosition({ 0.f, 0.f });

	nightOverlay.setSize(sf::Vector2f(1920.f, 1080.f));
	nightOverlay.setFillColor(sf::Color(0, 0, 0, 0));
}

void DayAndNight::update() {
	float time = fmod(dayNightClock.getElapsedTime().asSeconds(), daylenght);
	progress = time / daylenght; 

	// sine wave for darkness
	float darkness = (std::sin(progress * 2.f * 3.14159265f - 1.5707963f) + 1.f) / 2.f;
	darkness = std::clamp(darkness, 0.f, 1.f);

	alpha = static_cast<std::uint8_t>(darkness * 180.f + 0.5f);
	nightOverlay.setFillColor(sf::Color(0, 0, 50, alpha));
}

void DayAndNight::draw(sf::RenderWindow& window) {
	window.draw(nightOverlay);
	if (progress < 0.5f) {
		//day
		window.draw(daySprite);
	} else {
		window.draw(nightSprite);
	}

}