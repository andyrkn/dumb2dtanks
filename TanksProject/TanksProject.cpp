#include "TankHeader.h"
#include "TankPlayer.h"


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
	sf::RectangleShape ExitButton(baserectangle), SingleplayerButton(largerRectangle), CurrentTankTXT(baserectangle);
	sf::RectangleShape currentTank(baserectangle);

	// INITIALIZE TANK TEXTURES 

	sf::Texture playerTankTextures[5];
	sf::RectangleShape playerTanksbackup[5], playerTanks[5];
	inittextures(playerTanksbackup, 5, tankVector, playerTankTextures, playerTanks);

	//SETTINGS BUTTONS TEXTURE/POSITION

	ExitButton.setOrigin(baserectangle.x / 2, baserectangle.y / 2);
	SingleplayerButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);
	CurrentTankTXT.setOrigin(baserectangle.x / 2, baserectangle.y / 2);

	ExitButton.setPosition(MainMenu.getSize().x / 2 - 250.0f, 460.0f);
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

	float delta = 0.0f;
	sf::Clock clock;
	bool currentTankSelectedBool = false;
	sf::Texture currentTextureSel;
		

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

			for (int st = 0; st < 5; st++)
				if (mouseclickbutton(mousepos, playerTanksbackup[st]) == true)
				{
					currentTank = playerTanksbackup[st];
					currentTextureSel = playerTankTextures[st];

					currentTank.setPosition(MainMenu.getSize().x / 2 + 300, 480.0f);
					currentTankSelectedBool = true;
					break;
				}

			if (currentTankSelectedBool == true && mouseclickbutton(mousepos, SingleplayerButton) == true)
			{
				MainMenu.setVisible(false);

				sf::RenderWindow GameWindow(sf::VideoMode(1200, 600), "Tanks", sf::Style::Close);
				sf::RectangleShape PlayerGameTank = currentTank;
				PlayerGameTank.setPosition(100.0f, 100.0f);
				TankPlayer player1(PlayerGameTank, &currentTextureSel, 2, 0.2f);
				while (GameWindow.isOpen())
				{
					delta = clock.restart().asSeconds();
					sf::Event evnt1;
					while (GameWindow.pollEvent(evnt1))
					{
						if (evnt1.type == evnt1.Closed) {
							GameWindow.close();
							GameWindow.clear();
						}
					}
					player1.Update(delta);
					player1.draw(GameWindow);

					GameWindow.display();
					GameWindow.clear(sf::Color(230, 230, 230));
				}
				MainMenu.setVisible(true);
			}

		}

		MainMenu.draw(ExitButton);
		MainMenu.draw(SingleplayerButton);
		MainMenu.draw(CurrentTankTXT);
		if (currentTankSelectedBool)
			MainMenu.draw(currentTank);
		for (int i = 0; i < 5; i++)
			MainMenu.draw(playerTanksbackup[i]);
		MainMenu.display();
		MainMenu.clear(sf::Color(132, 137, 201));
	}
	return 0;
}