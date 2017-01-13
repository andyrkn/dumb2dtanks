#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Projectiles.h"
#include "Maps.h"
#include "Explosion.h"
#include "PowerUps.h"
using namespace std;

class Bots
{
public:
	Bots();
	Bots(sf::RectangleShape tankBody, sf::Texture* texture, int imageCount, float switchTime);
	~Bots();
	void UpdateEasy(float delta, Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[], int ib, int &isDead, PowerUps &ability);
	void UpdateNormal(float delta, Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[], int ib, int &isDead, PowerUps &ability);
	void UpdateHard(float delta, Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[], int ib, int &isDead,vector<Projectiles> PlayerBullets, PowerUps &ability);
	void draw(sf::RenderWindow& window);
	bool checkColission(Maps map,sf::Vector2f PlayerPos,sf::Vector2f BotsPos[], int ib, int &isDead, PowerUps &ability);
	bool checkColissionWalls(Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[], int ib);
	bool checkColissionFrame(Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[], int ib);
	sf::Vector2f GetPosition();
	void changePos(float delta);
	bool Bots::checkColissionHard(Maps map, sf::Vector2f BotsPos[], int nrBot, bool directionUp, bool directionDown, bool directionLeft, bool directionRight, float delta);
	int tankHP = 3;
	int backUpLife = 0;
	int power = 0, lastPower=0;
	int getDificulty();
	void setDificulty(int level);
	void setPosition(sf::Vector2f v);
	bool stillTraped;

private:

	void setdirection(bool upOnly, bool downOnly, bool rightOnly, bool leftOnly);
	void createbullet(bool upOnly,bool downOnly);

	sf::RectangleShape tankBody;
	vector<Projectiles> PVector;
	int dificultyLevel;
	bool startUp = false;
	bool startDown = false;
	bool direction = false;
	int Frames = 90;
	int ReloadTime = 0;

	Animation animation;
	Explosion explo;
};

