#pragma once

#include "SFML/Graphics.hpp"

class phone {
public:
	phone();
	void update();
	void draw(sf::RenderWindow& window);
	bool isPhoneHidden = true;

private:
	
	sf::Texture phoneTexture;
	sf::Sprite phoneSprite;

};