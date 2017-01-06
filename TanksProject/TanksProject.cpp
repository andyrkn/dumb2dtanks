#include "TankHeader.h"
#include "TankPlayer.h"
#include "Maps.h"
#include "Bots.h"


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

	sf::Texture playerTankTextures[5], mapsTextures[3];
	sf::RectangleShape playerTanksbackup[5], playerTanks[5], MAPS[3];
	inittextures(playerTanksbackup, 5, tankVector, playerTankTextures, playerTanks, MAPS, mapsTextures, 3);

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
	bool currentTankSelectedBool = false, mapSelected=false;
	sf::Texture currentTextureSel;
	Maps Map;
	int ct;
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
				if (mouseclickbutton(mousepos, playerTanksbackup[st]) == true)	{
					currentTank = playerTanksbackup[st];
					ct = st;
					currentTextureSel = playerTankTextures[st];
					currentTank.setPosition(MainMenu.getSize().x / 2 + 300, 480.0f);
					currentTankSelectedBool = true;
					break;
				}

			for (int i = 0; i < 3; i++)
				if (mouseclickbutton(mousepos, MAPS[i]) == true)	{
					mapSelected = true;
					Map.selectMap(i);
					break;
				}

			if (!mapSelected)
				Map.selectMap(100);

			if (currentTankSelectedBool == true && mouseclickbutton(mousepos, SingleplayerButton) == true)
			{
				MainMenu.setVisible(false);

				sf::RenderWindow GameWindow(sf::VideoMode(1200, 600), "Tanks", sf::Style::Close);
				sf::RectangleShape PlayerGameTank = currentTank;


				PlayerGameTank.setPosition(100.0f, 100.0f);
				TankPlayer player1(PlayerGameTank, &currentTextureSel, 2, 0.2f);

				int used[] = { 0,0,0,0,0,0,0,0 };
				int botLife[4];
				bool hasBeenKilled[] = { false, false, false, false}, EndOfGame;
				sf::Vector2f botPos[4];
				Bots bot[4];
				for (int bots = 0; bots < 3; bots++)
					bot[bots] = createbot(playerTanksbackup, playerTankTextures,used,ct);

				sf::Font font; font.loadFromFile("arial.ttf");
				sf::Text PlayerHPtext;
				PlayerHPtext.setFont(font);
				PlayerHPtext.setColor(sf::Color(108, 193, 129));
				PlayerHPtext.setStyle(sf::Text::Bold);
				PlayerHPtext.setCharacterSize(24);
				PlayerHPtext.setPosition(sf::Vector2f(15.0f, 10.0f));


				while (GameWindow.isOpen())
				{
					int ib, tankLife;
					delta = clock.restart().asSeconds();
					sf::Event evnt1;

					while (GameWindow.pollEvent(evnt1))
					{
						if (evnt1.type == evnt1.Closed) {
							GameWindow.close();
							GameWindow.clear();
						}
					}

					for (ib = 0; ib < 3; ib++)
					{
						botPos[ib] = bot[ib].GetPosition();
						botLife[ib] = bot[ib].tankHP;
					}

					player1.Update(delta, Map, botPos, botLife);
					EndOfGame = true;
					for (ib = 0; ib < 3; ib++)
					{
						tankLife = player1.tankHP;
						bot[ib].tankHP = botLife[ib];
						if (bot[ib].tankHP)
						{
							bot[ib].UpdateNormal(delta, Map, player1.GetPosition(), botPos, ib, tankLife);
							bot[ib].draw(GameWindow);
							EndOfGame = false;
						}
						else if (hasBeenKilled[ib] == false)
						{
							bot[ib].changePos(2000.0f);
							hasBeenKilled[ib] = true;
						}
						player1.tankHP = tankLife;
						if (!player1.tankHP)GameWindow.close();
					}

					string HPstring = "PlayerHP : ";
					if (player1.tankHP == 1) HPstring.push_back('1');
					if (player1.tankHP == 2) HPstring.push_back('2');
					if (player1.tankHP == 3) HPstring.push_back('3');
					
					PlayerHPtext.setString(HPstring);
					player1.draw(GameWindow);
					Map.draw(GameWindow);
					GameWindow.draw(PlayerHPtext);
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
		for (int j = 0; j < 3; j++)
			MainMenu.draw(MAPS[j]);
		MainMenu.display();
		MainMenu.clear(sf::Color(132, 137, 201));
	}
	return 0;
}