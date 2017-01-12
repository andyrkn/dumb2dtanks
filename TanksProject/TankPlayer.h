#pragma 
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Projectiles.h"
#include "Maps.h"
#include "Explosion.h"

using namespace std;

class TankPlayer
{
public:
	TankPlayer(sf::RectangleShape tankBody, sf::Texture* texture, int imageCount, float switchTime,short KeyPriority);
	~TankPlayer();

	void Update(float delta, Maps map, sf::Vector2f botPos[4], int botLife[4]);
	void draw(sf::RenderWindow& window);
	bool checkColission(Maps map, sf::Vector2f botPos[4], int botLife[4]);
	void kill();
	int tankHP = 3;
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
};


