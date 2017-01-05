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
	void UpdateEasy(float delta, Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[]);
	void UpdateNormal(float delta, Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[]);
	void UpdateHard(float delta, Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[]);
	void draw(sf::RenderWindow& window);
	bool checkColission(Maps map,sf::Vector2f PlayerPos,sf::Vector2f BotsPos[]);

	sf::Vector2f GetPosition();

private:

	void setdirection(bool upOnly, bool downOnly, bool rightOnly, bool leftOnly);

	sf::RectangleShape tankBody;
	Animation animation;
	vector<Projectiles> PVector;
	bool startUp = false;
	bool startDown = false;
	bool direction = false;
	int tankHP = 3;

	int Frames = 90;
	int ReloadTime = 0;
};

