#include "TankHeader.h"


int main()
{
	// HIDE CONSOLE

	ShowWindow(GetConsoleWindow(), SW_HIDE);

	// -- GLOBAL LOAD

	LoadVariables();

	// -- PROGRAM START

	while (MainMenu.isOpen()) {
		sf::Event evnt;
		while (MainMenu.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case evnt.Closed:
				MainMenu.close();
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			sf::Vector2i mousepos = sf::Mouse::getPosition(MainMenu);

			if (mouseclickbutton(mousepos, ExitButton) == true)
				MainMenu.close();

			if (mouseclickbutton(mousepos, OptionsButton) == true) {
				ButtonClickSound.play();
				sf::RenderWindow OptionsWindow(sf::VideoMode(1000, 600), "Options", sf::Style::Close);

				MainMenu.setVisible(false);
				MainMenu.setActive(false);

				while (OptionsWindow.isOpen())
					OptionsWindowEngine(OptionsWindow);

			}

			if (!mapSelected)
				Map.selectMap(100);

			if (currentTankSelectedBool == true && mouseclickbutton(mousepos, SingleplayerButton) == true)
			{
				MainMenu.setVisible(false);
				sf::RenderWindow GameWindow(sf::VideoMode(1200, 600), "Tanks", sf::Style::Close);
				SinglePlayerEngine(GameWindow);
			}

			if (currentTankSelectedBool == true && Player2Selected == true
				&& mouseclickbutton(mousepos, PvPButton) == true) {
				MainMenu.setVisible(false);
				sf::RenderWindow PvPWindow(sf::VideoMode(1200, 600), "PvP", sf::Style::Close);
				PvPEngine(PvPWindow);
				MainMenu.setVisible(true);
			}
		

		}

		drawButtons();
		MainMenu.display();
		MainMenu.clear(sf::Color(132, 137, 201));
	}
	return 0;
}