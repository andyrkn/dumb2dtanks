#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Projectiles.h"
#include "Maps.h"
using namespace std;

class Bots
{
public:
	Bots();
	Bots(sf::RectangleShape tankBody, sf::Texture* texture, int imageCount, float switchTime);
	~Bots();
	void UpdateEasy(float delta, Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[], int ib, int &isDead);
	void UpdateNormal(float delta, Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[], int ib, int &isDead);
	void UpdateHard(float delta, Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[], int ib, int &isDead,vector<Projectiles> PlayerBullets);
	void draw(sf::RenderWindow& window);
	bool checkColission(Maps map,sf::Vector2f PlayerPos,sf::Vector2f BotsPos[], int ib, int &isDead);
	bool checkColissionHard(Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[], int ib, int &isDead);
	sf::Vector2f GetPosition();
	void changePos(float delta);
	int tankHP = 3;

private:

	void setdirection(bool upOnly, bool downOnly, bool rightOnly, bool leftOnly);
	void createbullet(bool upOnly,bool downOnly);
	void directionDetails(bool upOnly, bool downOnly, bool rightOnly, bool leftOnly);

	sf::RectangleShape tankBody;
	Animation animation;
	vector<Projectiles> PVector;
	bool startUp = false;
	bool startDown = false;
	bool direction = false;
	int Frames = 90;
	int ReloadTime = 0;
};

