#include "TankHeader.h"


int main()
{
	// RENDER WINDOWS 

	sf::RenderWindow MainMenu(sf::VideoMode(1000, 600), "Tanks Menu", sf::Style::Close);


	// HIDE CONSOLE

	ShowWindow(GetConsoleWindow(), SW_HIDE);

	// STANDARD VECTORS FOR SIZES

	sf::Vector2f baserectangle = sf::Vector2f(100.0f, 50.0f);
	sf::Vector2f largerRectangle = sf::Vector2f(200.0f, 100.0f);
	sf::Vector2f tankVector = sf::Vector2f(60.0f, 42.0f);
	sf::RectangleShape ExitButton(baserectangle), SingleplayerButton(largerRectangle),CurrentTankTXT(baserectangle);
	
	// INITIALIZE TANK TEXTURES 

	sf::Texture playerTankTextures[5];
	sf::RectangleShape playerTanksbackup[5],playerTanks[5];
	inittextures(playerTanksbackup,5,tankVector,playerTankTextures,playerTanks);

	// NOT SURE ???

	sf::RectangleShape Player1(tankVector);
	Player1.setFillColor(sf::Color(27, 68, 135));
	Player1.setOrigin(Player1.getSize().x, Player1.getSize().y);

	//SETTINGS BUTTONS TEXTURE/POSITION

	ExitButton.setOrigin(baserectangle.x / 2, baserectangle.y / 2);
	SingleplayerButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);
	CurrentTankTXT.setOrigin(baserectangle.x / 2, baserectangle.y / 2);

	ExitButton.setPosition(MainMenu.getSize().x/2 - 250.0f, 460.0f);
	SingleplayerButton.setPosition(MainMenu.getSize().x / 2 - 250, 320.0f);
	CurrentTankTXT.setPosition(MainMenu.getSize().x / 2 + 200, 480.0f);

	sf::Texture ExitButtonText, SingpleButtonText, CurrentTankTexture;
	ExitButtonText.loadFromFile("Textures/MenuText.png");
	SingpleButtonText.loadFromFile("Textures/SingleplayerText.png");
	CurrentTankTexture.loadFromFile("Textures/CurrentTankTXT.png");

	ExitButton.setTexture(&ExitButtonText);
	SingleplayerButton.setTexture(&SingpleButtonText);
	CurrentTankTXT.setTexture(&CurrentTankTexture);

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

			if (mouseclickbutton(mousepos, SingleplayerButton) == true)
			{
				MainMenu.setVisible(false);

				sf::RenderWindow GameWindow(sf::VideoMode(1200, 600), "Tanks", sf::Style::Close);

				playerTanks[0].setPosition(100.0f, 100.0f);
				while (GameWindow.isOpen())
				{

					sf::Event evnt1;
					while (GameWindow.pollEvent(evnt1))
					{
						if (evnt1.type == evnt1.Closed)
							GameWindow.close();
					}

					

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))	playerTanks[0].move(-0.1f, 0.0f);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))	playerTanks[0].move(0.0f, 0.1f);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))	playerTanks[0].move(0.1f, 0.0f);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))	playerTanks[0].move(0.0f, -0.1f);

					GameWindow.draw(playerTanks[0]);
					GameWindow.display();
					GameWindow.clear(sf::Color(230, 230, 230));
				}
				MainMenu.setVisible(true);
			}

		}
		
		MainMenu.draw(ExitButton);
		MainMenu.draw(SingleplayerButton);
		MainMenu.draw(CurrentTankTXT);
		for (int i = 0; i < 5; i++)
			MainMenu.draw(playerTanksbackup[i]);
		MainMenu.display();
		MainMenu.clear(sf::Color(132, 137, 201));
	}
	return 0;
}