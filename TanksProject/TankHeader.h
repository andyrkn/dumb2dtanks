#include<SFML\Graphics.hpp>
#include<Windows.h>
#include"Bots.h"
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
		Maps[j].setPosition(x, 200.0f);
		Maps[j].setSize(sf::Vector2f(116.0f, 41.0f));
		Maps[j].setOrigin(sf::Vector2f(58.0f, 20.5f));
	}

	for (int i = 0; i < nr; i++) {
		x = 100 * (i + 5);
		tanks[i].setPosition(x, 350.0f);
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
// RENDER WINDOWS 

sf::RenderWindow MainMenu(sf::VideoMode(1000, 600), "Tanks Menu", sf::Style::Close);

// INITIALIZE TANK TEXTURES 

sf::Texture playerTankTextures[5], mapsTextures[3];
sf::RectangleShape playerTanksbackup[5], playerTanks[5], MAPS[3];


// STANDARD VECTORS FOR SIZES

sf::Vector2f baserectangle = sf::Vector2f(100.0f, 50.0f);
sf::Vector2f largerRectangle = sf::Vector2f(200.0f, 100.0f);
sf::Vector2f tankVector = sf::Vector2f(60.0f, 42.0f);
sf::RectangleShape ExitButton(baserectangle), SingleplayerButton(largerRectangle), CurrentTankTXT(baserectangle);
sf::RectangleShape currentTank(baserectangle);
sf::RectangleShape OptionsButton(largerRectangle), SurvivalButton(largerRectangle), PvPButton(largerRectangle);
sf::Texture ExitButtonText, SingpleButtonText, CurrentTankTexture, OptionsText, SurvivalText, PvPText;


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

	ExitButton.setPosition(200.0f, 500.0f);
	SingleplayerButton.setPosition(200.0f, 100.0f);
	CurrentTankTXT.setPosition(MainMenu.getSize().x / 2 + 200, 480.0f);
	OptionsButton.setPosition(200.0f, 400.0f);
	SurvivalButton.setPosition(200.0f, 200.0f);
	PvPButton.setPosition(200.0f, 300.0f);

	ExitButtonText.loadFromFile("Textures/MenuText.png");
	SingpleButtonText.loadFromFile("Textures/SingleplayerText.png");
	CurrentTankTexture.loadFromFile("Textures/CurrentTankTXT.png");
	SurvivalText.loadFromFile("Textures/Survival.png");
	OptionsText.loadFromFile("Textures/OptionsText.png");
	PvPText.loadFromFile("Textures/PvPText.png");


	ExitButton.setTexture(&ExitButtonText);
	SingleplayerButton.setTexture(&SingpleButtonText);
	CurrentTankTXT.setTexture(&CurrentTankTexture);
	SurvivalButton.setTexture(&SurvivalText);
	OptionsButton.setTexture(&OptionsText);
	PvPButton.setTexture(&PvPText);
}

void drawButtons(bool currentTankSelectedBool)
{
	MainMenu.draw(ExitButton);
	MainMenu.draw(SingleplayerButton);
	MainMenu.draw(CurrentTankTXT);
	MainMenu.draw(OptionsButton);
	MainMenu.draw(SurvivalButton);
	MainMenu.draw(PvPButton);
	if (currentTankSelectedBool)
		MainMenu.draw(currentTank);
	for (int i = 0; i < 5; i++)
		MainMenu.draw(playerTanksbackup[i]);
	for (int j = 0; j < 3; j++)
		MainMenu.draw(MAPS[j]);
}