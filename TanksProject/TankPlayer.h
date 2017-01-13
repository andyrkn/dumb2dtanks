#pragma 
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Projectiles.h"
#include "Maps.h"
#include "Explosion.h"
#include "PowerUps.h"

using namespace std;

class TankPlayer
{
public:
	TankPlayer(sf::RectangleShape tankBody, sf::Texture* texture, int imageCount, float switchTime,short KeyPriority,int SelectedTank);
	~TankPlayer();
	void Update(float delta, Maps map, sf::Vector2f botPos[4], int botLife[4], PowerUps &ability);
	void draw(sf::RenderWindow& window);
	bool checkColission(Maps map, sf::Vector2f botPos[4], int botLife[4], PowerUps &ability);
	bool checkColissionWalls(Maps map, sf::Vector2f botPos[4]);
	bool checkColissionFrame(Maps map, sf::Vector2f botPos[4]);
	void kill();
	int tankHP = 3, backUpLife=0;
	int power=0, lastPower=0;
	sf::Vector2f GetPosition();
	vector<Projectiles> getBullets();
	
private:
	sf::RectangleShape tankBody;
	bool direction;
	vector<Projectiles> PVector;
	int Frames = 90;
	int ReloadTime = 0;
	bool directionUp = false;
	bool directionDown = false;
	short KeyPriority = 0;	
	Animation animation;
	Explosion explo;
	bool stillTraped = false;

	float Bspeed = 0.25f, BbulletSpeed = 1.5f;
};


