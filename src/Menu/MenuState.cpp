#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../include/Menu/MenuState.hpp"
#include "../../include/Menu/Pause.hpp"

// i can make this better but idc.

void MenuState::StartBtnFunction(sf::RenderWindow& window, bool canContinue) {
	    sf::Font Pixelfont;
	    if (!Pixelfont.openFromFile("assets/fonts/Silkscreen-Regular.ttf")) {
	        std::cerr << "FAILED to load font\n";
	    }
	    Pause pause(Pixelfont);
	    sf::Text title(Pixelfont);
	    title.setString("Soul-Less");
	    title.setCharacterSize(96);
	    title.setFillColor(sf::Color::White);
	    title.setPosition({ 10.f, 100.f });

		    // START TEXT
		    sf::Text StartText(Pixelfont);
		    StartText.setString("Continue");
		    StartText.setCharacterSize(48);
		    StartText.setFillColor(canContinue ? sf::Color::White : sf::Color(120, 120, 120));
		    StartText.setPosition({ 10.f, 540.f });

	    // Load Text
	    sf::Text LoadText(Pixelfont);
	    LoadText.setString("New Game");
	    LoadText.setCharacterSize(48);
	    LoadText.setFillColor(sf::Color::White);
	    LoadText.setPosition({ 10.f, 740.f });

    // for Quit Text
    sf::Text QuitText(Pixelfont);
    QuitText.setString("Quit");
    QuitText.setCharacterSize(48);
    QuitText.setFillColor(sf::Color::White);
    QuitText.setPosition({ 10.f, 940.f });

    // for version text
    sf::Text versionText(Pixelfont);
    versionText.setString("v1.0.0");
    versionText.setCharacterSize(24);
    versionText.setFillColor(sf::Color::White);
    versionText.setPosition({ 10.f, 10.f });

	   
	    isVisible = true;
		isStartClicked = false;
        isLoadClicked = false;

    // Rectangles for buttons
    sf::RectangleShape Start;
    Start.setFillColor(sf::Color(255, 0, 0, 128));
    Start.setPosition({ 10.f, 540.f });
    Start.setSize({ 350.f, 140.f });

    sf::RectangleShape Load;
    Load.setFillColor(sf::Color(0, 255, 0, 128));
    Load.setPosition({ 10.f, 740.f });
    Load.setSize({ 350.f, 140.f });

    sf::RectangleShape Quit;
    Quit.setFillColor(sf::Color(0, 0, 255, 128));
    Quit.setPosition({ 10.f, 940.f });
    Quit.setSize({ 350.f, 140.f });

    // Buttons global bounds
    sf::FloatRect StartButtonGB = Start.getGlobalBounds();
    sf::FloatRect LoadButtonGB = Load.getGlobalBounds();
    sf::FloatRect QuitButtonGB = Quit.getGlobalBounds();

	    // Mouse position + proper "fresh click" handling
	    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        const bool leftMouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        const bool isFreshLeftClick = leftMouseDown && !wasLeftMouseDown;

		    // For Start Button
		    if (StartButtonGB.contains(sf::Vector2f{ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) })) {
		        if (isFreshLeftClick) {
		            if (canContinue) {
		                isVisible = false;
		                isStartClicked = true;
		            }
		        }
		    }

	    // For load
	    if (LoadButtonGB.contains(sf::Vector2f{ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) })) {
	        if (isFreshLeftClick) {
				isVisible = false;
                isLoadClicked = true;
	        }
	    }

	    // For Quit
	    if (QuitButtonGB.contains(sf::Vector2f{ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) })) {
	        if (isFreshLeftClick) {
	            window.close();
	        }
	    }

	    if (isVisible) {
	        window.draw(title);
	        window.draw(versionText);
	        //window.draw(Start);
	        window.draw(StartText);
	        //window.draw(Load);
	        window.draw(LoadText);
	        //window.draw(Quit);
	        window.draw(QuitText);
	    }

        wasLeftMouseDown = leftMouseDown;
	}

