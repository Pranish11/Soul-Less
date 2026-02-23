#include "../include/Pause.hpp"
#include "../include/MenuState.hpp"


Pause::Pause(const sf::Font& f) : Pixelfont(f) {
}

void Pause::PauseDraw(sf::RenderWindow& window)
{
	sf::RectangleShape Continue;
	sf::RectangleShape Save;
	sf::RectangleShape Exit;
	bool isPaused = true;
	sf::Vector2i MousePos = sf::Mouse::getPosition(window);

	Continue.setSize({ 200.f, 50.f });
	Continue.setFillColor(sf::Color(0, 255, 0, 128));
	Continue.setPosition({ 860.f, 400.f });

	Save.setSize({ 200.f, 50.f });
	Save.setFillColor(sf::Color(0, 0, 255, 128));
	Save.setPosition({ 860.f, 500.f });

	Exit.setSize({ 200.f, 50.f });
	Exit.setFillColor(sf::Color(255, 0, 0, 128));
	Exit.setPosition({ 860.f, 600.f });

	sf::FloatRect ContinueGB = Continue.getGlobalBounds();
	sf::FloatRect SaveGB = Save.getGlobalBounds();
	sf::FloatRect ExitGB = Exit.getGlobalBounds();

	//Text
	sf::Text ContinueText(Pixelfont);
	ContinueText.setString("Continue");
	ContinueText.setPosition({ 860.f, 400.f });
	ContinueText.setCharacterSize(48);
	ContinueText.setFillColor(sf::Color::White);

	sf::Text SaveText(Pixelfont);
	SaveText.setString("Save");
	SaveText.setPosition({ 860.f, 500.f });
	SaveText.setCharacterSize(48);
	SaveText.setFillColor(sf::Color::White);

	sf::Text ExitText(Pixelfont);
	ExitText.setString("Exit");
	ExitText.setPosition({ 860.f, 600.f });
	ExitText.setCharacterSize(48);
	ExitText.setFillColor(sf::Color::White);

	window.draw(ContinueText);
	window.draw(SaveText);
	window.draw(ExitText);

	if (ContinueGB.contains(sf::Vector2f{ static_cast<float>(MousePos.x),static_cast<float>(MousePos.y) }))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			return;
		}
	}
	if (SaveGB.contains(sf::Vector2f{ static_cast<float>(MousePos.x),static_cast<float>(MousePos.y) }))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			return;
		}
	}
	if (ExitGB.contains(sf::Vector2f{ static_cast<float>(MousePos.x),static_cast<float>(MousePos.y) }))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			window.close();
		}
	}
}