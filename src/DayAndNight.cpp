#include <iostream>
#include <cstdint>
#include <cmath>
#include <algorithm>

#include "../include/DayAndNight.hpp"
#include "../include/Game.hpp"

DayAndNight::DayAndNight(){
	//texture and sprite for day and night cycle
	sf::Texture dayTexture("assets/textures/Am_time.png");
	sf::Texture nightTexture("assets/textures/Pm_time.png");

	sf::Sprite daySprite(dayTexture);
	sf::Sprite nightSprite(nightTexture);
	
	//postion and scale
	daySprite.setPosition({ 0.f, 0.f });
	nightSprite.setPosition({ 0.f, 0.f });
	daySprite.setScale({ 1.f, 1.f });
	nightSprite.setScale({ 1.f, 1.f });

	sf::Clock dayNightClock;
	float daylenght = 60.f; //length of day in seconds


	//night overlay
	sf::RectangleShape nightOverlay;
	nightOverlay.setSize(sf::Vector2f{1920,1080});
	nightOverlay.setFillColor(sf::Color(0, 0, 0, 0)); // start daytime

}

void DayAndNight::update() {
		float time = fmod(dayNightClock.getElapsedTime().asSeconds(), daylenght);
		float progress = time / daylenght;

		// sine wave: day to night to again day
		float darkness = (std::sin(progress * 2.f * 3.14159265f - 1.5707963f) + 1.f) / 2.f;

		// clamp
		darkness = std::clamp(darkness, 0.f, 1.f);

		// map to alpha 0–180 
		std::uint8_t alpha = static_cast<std::uint8_t>(darkness * 180.f + 0.5f);

		nightOverlay.setFillColor(sf::Color(0, 0, 50, alpha));
}

void DayAndNight::draw(sf::RenderWindow& window) {
	window.draw(nightOverlay);
}