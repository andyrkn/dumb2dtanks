#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<Windows.h>
#include"Bots.h"
#include "TankPlayer.h"
#include "Maps.h"
#include<string>
#include<random>
#define ToF(a) static_cast<float>(a)
using namespace std;
void inittextures(sf::RectangleShape tanks[], int nr, sf::Vector2f tanksize, sf::Texture textures[],sf::RectangleShape maintanks[], sf::RectangleShape Maps[], sf::Texture mapsTextures[], int noMaps)
{
	textures[0].loadFromFile("Textures/tanksblue.png");  tanks[0].setTexture(&textures[0]);
	textures[1].loadFromFile("Textures/tankswhite.png"); tanks[1].setTexture(&textures[1]);
	textures[2].loadFromFile("Textures/tanksgreen.png"); tanks[2].setTexture(&textures[2]);
	textures[3].loadFromFile("Textures/tankspurple.png"); tanks[3].setTexture(&textures[3]);
	textures[4].loadFromFile("Textures/tanksyellow.png"); tanks[4].setTexture(&textures[4]);
	mapsTextures[0].loadFromFile("Textures/MAP1.png"); Maps[0].setTexture(&mapsTextures[0]);
	mapsTextures[1].loadFromFile("Textures/MAP2.png"); Maps[1].setTexture(&mapsTextures[1]);
	mapsTextures[2].loadFromFile("Textures/MAP3.png"); Maps[2].setTexture(&mapsTextures[2]);

	float x;
	sf::Vector2u texturesize = textures[0].getSize();
	texturesize.x /= 2;

	for (int j = 0; j < noMaps; j++)
	{
		x = 150 * (j + 3);
		Maps[j].setPosition(x, 100.0f);
		Maps[j].setSize(sf::Vector2f(116.0f, 41.0f));
		Maps[j].setOrigin(sf::Vector2f(58.0f, 20.5f));
	}

	for (int i = 0; i < nr; i++) {
		x = 100 * (i + 5);
		tanks[i].setPosition(x, 430.0f);
		tanks[i].setSize(tanksize);
		tanks[i].setTextureRect(sf::IntRect(0, 0, texturesize.x, texturesize.y));
		tanks[i].setOrigin(tanksize.x / 2, tanksize.y / 2);
		maintanks[i] = tanks[i];
	}

}

bool mouseclickbutton(sf::Vector2i MousePos, sf::RectangleShape button)
{
	sf::Vector2f buttonsize(button.getSize().x, button.getSize().y);
	sf::Vector2f buttonposi(button.getPosition().x, button.getPosition().y);

	if (ToF(MousePos.x) >= (buttonposi.x - buttonsize.x / 2) && ToF(MousePos.x) <= (buttonposi.x + buttonsize.x / 2))
		if (ToF(MousePos.y) <= (buttonposi.y + buttonsize.y / 2) && ToF(MousePos.y) >= (buttonposi.y - buttonsize.y / 2))
			return true;
	return false;
}


Bots createbot(sf::RectangleShape bodys[], sf::Texture textures[],int used[],int ct)
{
	int x;
	while (true) {
		x = rand() % 5 + 1;
		if (used[x] == 0 && (x-1)!=ct) {
			Bots b(bodys[x - 1], &textures[x - 1], 2, 0.2f);
			used[x] = 1;
			return b;
		}
	}
}

//============= MAIN VARIABLES 

bool EasyDifficulty = true, NormalDifficulty = false, HardDifficulty = false;
int BotsNumber = 3;
int ct;
bool currentTankSelectedBool = false, mapSelected = false;

// RENDER WINDOWS 

sf::RenderWindow MainMenu(sf::VideoMode(1000, 600), "Tanks Menu", sf::Style::Close);

//SOUND

sf::SoundBuffer ButtonClickSoundBuffer;
sf::Sound ButtonClickSound;

// INITIALIZE TANK TEXTURES 

sf::Texture playerTankTextures[5], mapsTextures[3];
sf::RectangleShape playerTanksbackup[5], playerTanks[5], MAPS[3];


// STANDARD VECTORS FOR SIZES

sf::Vector2f baserectangle = sf::Vector2f(100.0f, 50.0f);
sf::Vector2f largerRectangle = sf::Vector2f(200.0f, 100.0f);
sf::Vector2f tankVector = sf::Vector2f(60.0f, 42.0f);
sf::RectangleShape ExitButton(baserectangle), SingleplayerButton(largerRectangle), CurrentTankTXT(baserectangle);
sf::RectangleShape currentTank(baserectangle);
sf::RectangleShape EasyButton(largerRectangle), NormalButton(largerRectangle), HardButton(largerRectangle);
sf::RectangleShape SelectMapButton(largerRectangle), DifficultyButton(largerRectangle);
sf::RectangleShape OptionsButton(largerRectangle), SurvivalButton(largerRectangle), PvPButton(largerRectangle);
sf::RectangleShape BackButton(largerRectangle), SelectTankButton(largerRectangle), NrOfBotsButton(largerRectangle);
sf::RectangleShape Nr1B(baserectangle), Nr2B(baserectangle), Nr3B(baserectangle), Nr4B(baserectangle), Nr5B(baserectangle);
sf::RectangleShape NumbersBox(baserectangle), DifficultyBox(largerRectangle), MapBox(sf::Vector2f(160.0f,80.0f));
sf::Texture ExitButtonText, SingpleButtonText, CurrentTankTexture, OptionsText, SurvivalText, PvPText;
sf::Texture BackButtonText, SelectTankText, NrOfBotsText;
sf::Texture currentTextureSel, SelectMapText;
sf::Texture Nr1BText, Nr2BText, Nr3BText, Nr4BText, Nr5BText;
sf::Texture EasyText, NormalText, HardText, DifficultyText;
sf::Texture SmallBoxTexture, LargeBoxTexture;

// MAP

Maps Map;

void LoadVariables()
{
	inittextures(playerTanksbackup, 5, tankVector, playerTankTextures, playerTanks, MAPS, mapsTextures, 3);

	//SETTINGS BUTTONS TEXTURE/POSITION
	SingleplayerButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);
	SurvivalButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);
	OptionsButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);
	PvPButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);
	ExitButton.setOrigin(baserectangle.x / 2, baserectangle.y / 2);
	CurrentTankTXT.setOrigin(baserectangle.x / 2, baserectangle.y / 2);
	BackButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);
	SelectTankButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);
	NrOfBotsButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);
	SelectMapButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);
	DifficultyBox.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);
	NumbersBox.setOrigin(baserectangle.x / 2, baserectangle.y / 2);

	MapBox.setOrigin(80.0f, 40.0f);

	DifficultyButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);
	EasyButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);
	NormalButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);
	HardButton.setOrigin(largerRectangle.x / 2, largerRectangle.y / 2);

	Nr1B.setOrigin(baserectangle.x / 2, baserectangle.y / 2);
	Nr2B.setOrigin(baserectangle.x / 2, baserectangle.y / 2);
	Nr3B.setOrigin(baserectangle.x / 2, baserectangle.y / 2);
	Nr4B.setOrigin(baserectangle.x / 2, baserectangle.y / 2);
	Nr5B.setOrigin(baserectangle.x / 2, baserectangle.y / 2);

	ExitButton.setPosition(200.0f, 500.0f);
	SingleplayerButton.setPosition(200.0f, 100.0f);
	CurrentTankTXT.setPosition(MainMenu.getSize().x / 2 + 200, 480.0f);
	OptionsButton.setPosition(200.0f, 400.0f);
	SurvivalButton.setPosition(200.0f, 200.0f);
	PvPButton.setPosition(200.0f, 300.0f);
	BackButton.setPosition(200.0f, 550.0f);
	SelectTankButton.setPosition(200.0f, 430.0f);
	NrOfBotsButton.setPosition(200.0f, 330.0f);
	SelectMapButton.setPosition(200.0f, 100.0f);

	DifficultyButton.setPosition(200.0f, 230.0f);
	EasyButton.setPosition(450.0f, 230.0f);
	NormalButton.setPosition(660.0f, 230.0f);
	HardButton.setPosition(850.0f, 230.0f);

	Nr1B.setPosition(500.0f, 330.0f);
	Nr2B.setPosition(600.0f, 330.0f);
	Nr3B.setPosition(700.0f, 330.0f);
	Nr4B.setPosition(800.0f, 330.0f);
	Nr5B.setPosition(900.0f, 330.0f);

	DifficultyBox.setPosition(EasyButton.getPosition());
	NumbersBox.setPosition(Nr3B.getPosition());
	MapBox.setPosition(750.0f, 100.0f);

	ExitButtonText.loadFromFile("Textures/MenuText.png");
	SingpleButtonText.loadFromFile("Textures/SingleplayerText.png");
	CurrentTankTexture.loadFromFile("Textures/CurrentTankTXT.png");
	SurvivalText.loadFromFile("Textures/Survival.png");
	OptionsText.loadFromFile("Textures/OptionsText.png");
	PvPText.loadFromFile("Textures/PvPText.png");
	BackButtonText.loadFromFile("Textures/BackText.png");
	SelectTankText.loadFromFile("Textures/SelectTankText.png");
	NrOfBotsText.loadFromFile("Textures/NrOfBotsText.png");
	SelectMapText.loadFromFile("Textures/SelectMapText.png");

	Nr1BText.loadFromFile("Textures/Nr1.png");
	Nr2BText.loadFromFile("Textures/Nr2.png");
	Nr3BText.loadFromFile("Textures/Nr3.png");
	Nr4BText.loadFromFile("Textures/Nr4.png");
	Nr5BText.loadFromFile("Textures/Nr5.png");

	DifficultyText.loadFromFile("Textures/Difficulty.png");
	EasyText.loadFromFile("Textures/EasyText.png");
	NormalText.loadFromFile("Textures/NormalText.png");
	HardText.loadFromFile("Textures/HardText.png");

	SmallBoxTexture.loadFromFile("Textures/SmallRectangleBox.png");
	LargeBoxTexture.loadFromFile("Textures/LargeRectangleBox.png");

	ExitButton.setTexture(&ExitButtonText);
	SingleplayerButton.setTexture(&SingpleButtonText);
	CurrentTankTXT.setTexture(&CurrentTankTexture);
	SurvivalButton.setTexture(&SurvivalText);
	OptionsButton.setTexture(&OptionsText);
	PvPButton.setTexture(&PvPText);
	BackButton.setTexture(&BackButtonText);
	SelectTankButton.setTexture(&SelectTankText);
	NrOfBotsButton.setTexture(&NrOfBotsText);
	SelectMapButton.setTexture(&SelectMapText);

	DifficultyBox.setTexture(&LargeBoxTexture);
	NumbersBox.setTexture(&SmallBoxTexture);
	MapBox.setTexture(&LargeBoxTexture);

	Nr1B.setTexture(&Nr1BText);
	Nr2B.setTexture(&Nr2BText);
	Nr3B.setTexture(&Nr3BText);
	Nr4B.setTexture(&Nr4BText);
	Nr5B.setTexture(&Nr5BText);

	DifficultyButton.setTexture(&DifficultyText);
	EasyButton.setTexture(&EasyText);
	NormalButton.setTexture(&NormalText);
	HardButton.setTexture(&HardText);

	//SOUND
	ButtonClickSoundBuffer.loadFromFile("Sounds/ButtonClick.wav");
	ButtonClickSound.setBuffer(ButtonClickSoundBuffer);
}

void drawButtons()
{
	MainMenu.draw(ExitButton);
	MainMenu.draw(SingleplayerButton);
	MainMenu.draw(OptionsButton);
	MainMenu.draw(SurvivalButton);
	MainMenu.draw(PvPButton);
}

void OptionsWindowEngine(sf::RenderWindow &OptionsWindow)
{

	sf::Event evnt2;
	while (OptionsWindow.pollEvent(evnt2))
	{
		switch (evnt2.type)
		{
		case evnt2.Closed: {
			MainMenu.setVisible(true);
			sf::Time sleepTime = sf::milliseconds(200);
			MainMenu.setActive(true);
			OptionsWindow.clear(); OptionsWindow.close();
			sf::sleep(sleepTime);
		}
		}
	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		sf::Vector2i mouseposOptions = sf::Mouse::getPosition(OptionsWindow);

		if (mouseclickbutton(mouseposOptions, Nr1B) == true){ ButtonClickSound.play(); sf::sleep(sf::milliseconds(200)); BotsNumber = 1; NumbersBox.setPosition(Nr1B.getPosition());	}
		if (mouseclickbutton(mouseposOptions, Nr2B) == true){ ButtonClickSound.play(); sf::sleep(sf::milliseconds(200)); BotsNumber = 2; NumbersBox.setPosition(Nr2B.getPosition());	}
		if (mouseclickbutton(mouseposOptions, Nr3B) == true){ ButtonClickSound.play(); sf::sleep(sf::milliseconds(200)); BotsNumber = 3; NumbersBox.setPosition(Nr3B.getPosition());	}
		if (mouseclickbutton(mouseposOptions, Nr4B) == true){ ButtonClickSound.play(); sf::sleep(sf::milliseconds(200)); BotsNumber = 4; NumbersBox.setPosition(Nr4B.getPosition());	}
	//	if (mouseclickbutton(mouseposOptions, Nr5B) == true) BotsNumber = 5;

		if (mouseclickbutton(mouseposOptions, EasyButton)) { ButtonClickSound.play(); sf::sleep(sf::milliseconds(200)); DifficultyBox.setPosition(EasyButton.getPosition()); EasyDifficulty = true; NormalDifficulty = false; HardDifficulty = false; }
		if (mouseclickbutton(mouseposOptions, NormalButton)) { ButtonClickSound.play(); sf::sleep(sf::milliseconds(200)); DifficultyBox.setPosition(NormalButton.getPosition()); EasyDifficulty = false; NormalDifficulty = true; HardDifficulty = false; }
		if (mouseclickbutton(mouseposOptions, HardButton)) { ButtonClickSound.play(); sf::sleep(sf::milliseconds(200)); DifficultyBox.setPosition(HardButton.getPosition()); EasyDifficulty = false; NormalDifficulty = false; HardDifficulty = true; }
	//default Easy difficult

		for (int st = 0; st < 5; st++)  // tank selection
			if (mouseclickbutton(mouseposOptions, playerTanksbackup[st]) == true) {
				ButtonClickSound.play();
				sf::sleep(sf::milliseconds(200));
				currentTank = playerTanksbackup[st];
				ct = st;
				currentTextureSel = playerTankTextures[st];
				currentTank.setPosition(MainMenu.getSize().x / 2 + 300, 480.0f);
				currentTankSelectedBool = true;
				break;
			}

		for (int i = 0; i < 3; i++)
			if (mouseclickbutton(mouseposOptions, MAPS[i]) == true) {
				ButtonClickSound.play();
				sf::sleep(sf::milliseconds(200));
				mapSelected = true;
				Map.selectMap(i);
				MapBox.setPosition(MAPS[i].getPosition());
				break;
			}

		if (mouseclickbutton(mouseposOptions, BackButton) == true) {
			ButtonClickSound.play();
			OptionsWindow.clear(); OptionsWindow.close(); 
			MainMenu.setVisible(true); MainMenu.setActive(true);
			sf::Time sleepTime = sf::milliseconds(200);
			sf::sleep(sleepTime);
		}
	}

	OptionsWindow.draw(NrOfBotsButton);
	OptionsWindow.draw(BackButton);
	OptionsWindow.draw(SelectTankButton);
	OptionsWindow.draw(CurrentTankTXT);
	OptionsWindow.draw(SelectMapButton);
	OptionsWindow.draw(Nr1B); OptionsWindow.draw(Nr2B);	OptionsWindow.draw(Nr3B); OptionsWindow.draw(Nr4B);// OptionsWindow.draw(Nr5B);
	OptionsWindow.draw(EasyButton);
	OptionsWindow.draw(NormalButton);
	OptionsWindow.draw(HardButton);
	OptionsWindow.draw(DifficultyButton);
	if (currentTankSelectedBool)
		OptionsWindow.draw(currentTank);
	for (int i = 0; i < 5; i++)
		OptionsWindow.draw(playerTanksbackup[i]);
	for (int j = 0; j < 3; j++)
		OptionsWindow.draw(MAPS[j]);

	OptionsWindow.draw(DifficultyBox);
	OptionsWindow.draw(NumbersBox);
	OptionsWindow.draw(MapBox);

	OptionsWindow.display();
	OptionsWindow.clear(sf::Color(132, 137, 201));
}

void SinglePlayerEngine(sf::RenderWindow &GameWindow) 
{
	ButtonClickSound.play();
	GameWindow.setFramerateLimit(450);
	Bots bot[7];
	int botLife[7];

	sf::RectangleShape PlayerGameTank = currentTank;

	PlayerGameTank.setPosition(100.0f, 100.0f);
	TankPlayer player1(PlayerGameTank, &currentTextureSel, 2, 0.2f);

	int used[] = { 0,0,0,0,0,0,0,0 };

	float time = 0.0f, timePrec = 0.0f;
	bool hasBeenKilled[] = { false, false, false, false }, EndOfGame;
	sf::Vector2f botPos[4];

	for (int bots = 0; bots < BotsNumber; bots++)
		bot[bots] = createbot(playerTanksbackup, playerTankTextures, used, ct);

	float delta = 0.0f;
	sf::Clock clock;


	sf::Font font;
	sf::Text PlayerHPtext;
	font.loadFromFile("arial.ttf");
	PlayerHPtext.setFont(font);
	PlayerHPtext.setColor(sf::Color(108, 193, 129));
	PlayerHPtext.setStyle(sf::Text::Bold);
	PlayerHPtext.setCharacterSize(24);
	PlayerHPtext.setPosition(sf::Vector2f(15.0f, 10.0f));

	while (GameWindow.isOpen())
	{

		//SinglePlayerEngine(GameWindow,PlayerHPtext,bot);
		timePrec = time;
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

		for (ib = 0; ib < BotsNumber; ib++)
		{
			botPos[ib] = bot[ib].GetPosition();
			botLife[ib] = bot[ib].tankHP;
		}

		player1.Update(delta, Map, botPos, botLife);
		EndOfGame = true;
		for (ib = 0; ib < BotsNumber; ib++)
		{
			tankLife = player1.tankHP;
			bot[ib].tankHP = botLife[ib];
			if (bot[ib].tankHP)
			{

				if(EasyDifficulty)		bot[ib].UpdateEasy(delta, Map, player1.GetPosition(), botPos, ib, tankLife);
				if(NormalDifficulty)	bot[ib].UpdateNormal(delta, Map, player1.GetPosition(), botPos, ib, tankLife);
				if(HardDifficulty)		bot[ib].UpdateHard(delta, Map, player1.GetPosition(), botPos, ib, tankLife, player1.getBullets());

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

		PlayerHPtext.setPosition(sf::Vector2f(15.0f, 10.0f));
		string HPstring = "PlayerHP : ";
		if (player1.tankHP == 1) HPstring.push_back('1');
		if (player1.tankHP == 2) HPstring.push_back('2');
		if (player1.tankHP == 3) HPstring.push_back('3');
		if (player1.tankHP == 4) HPstring.push_back('4');
		if (player1.tankHP == 5) HPstring.push_back('5');
		PlayerHPtext.setString(HPstring);
		GameWindow.draw(PlayerHPtext);



		PlayerHPtext.setPosition(sf::Vector2f(1000.0f, 10.0f));
		HPstring = "Enemy HP : ";
		if (bot[0].tankHP == 1) HPstring.push_back('1');
		if (bot[0].tankHP == 2) HPstring.push_back('2');
		if (bot[0].tankHP == 3) HPstring.push_back('3');
		PlayerHPtext.setString(HPstring);
		GameWindow.draw(PlayerHPtext);


		player1.draw(GameWindow);
		Map.draw(GameWindow);
		GameWindow.display();
		GameWindow.clear(sf::Color(230, 230, 230));

	}
	MainMenu.setVisible(true);
}