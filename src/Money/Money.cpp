
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


// for cash
void money::cashDraw(sf::RenderWindow& window)
{
	const float y = 20.f;
	const float rightPadding = 20.f;
	const float gap = 10.f;
	const float windowWidth = static_cast<float>(window.getSize().x);

	const auto cashBounds = Cash_Amount_Display.getLocalBounds();
	Cash_Amount_Display.setOrigin(sf::Vector2f{ cashBounds.size.x, 0.f });
	Cash_Amount_Display.setPosition(sf::Vector2f{ windowWidth - rightPadding, y });
	window.draw(Cash_Amount_Display);

	const auto labelBounds = Cash_Text.getLocalBounds();
	Cash_Text.setOrigin(sf::Vector2f{ labelBounds.size.x, 0.f });
	Cash_Text.setPosition(sf::Vector2f{ windowWidth - rightPadding - cashBounds.size.x - gap, y });
	window.draw(Cash_Text);
}
