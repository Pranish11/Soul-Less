
#include <iostream>
#include "../../include/Money/Money.hpp"
#include "../../include/Game.hpp"

money::money(const sf::Font& f) : Pixelfont(f), Cash_Text(Pixelfont, "Cash : "), Cash_Amount_Display(Pixelfont, std::to_string(cash))
{
	Cash_Text.setCharacterSize(24);
	Cash_Text.setScale({ 1.f, 1.f });

	Cash_Amount_Display.setCharacterSize(24);
	Cash_Amount_Display.setScale({ 1.f,1.f });

};

void money::update()
{
	//cash += 1;
	Cash_Amount_Display.setString(std::to_string(cash));
}


// For bank
void money::draw(sf::RenderWindow& window)
{

}

// for cash
void money::cashDraw(sf::RenderWindow& window)
{
	const auto bounds = Cash_Text.getLocalBounds();
	Cash_Text.setOrigin(sf::Vector2f{ bounds.size.x, 0.f });
	Cash_Text.setPosition(sf::Vector2f{ static_cast<float>(window.getSize().x) - 180.f, 20.f });
	window.draw(Cash_Text);

	const auto Cash_Bounds = Cash_Amount_Display.getLocalBounds();
	Cash_Amount_Display.setOrigin(sf::Vector2f{ Cash_Bounds.size.x, 0.f });
	Cash_Amount_Display.setPosition(sf::Vector2f{ static_cast<float>(window.getSize().x) - 20.f, 20.f });
	window.draw(Cash_Amount_Display);
}
