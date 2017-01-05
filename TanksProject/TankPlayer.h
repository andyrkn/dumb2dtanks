#pragma 
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Projectiles.h"
#include "Maps.h"
using namespace std;

class TankPlayer
{
public:
	TankPlayer(sf::RectangleShape tankBody, sf::Texture* texture, int imageCount, float switchTime);
	~TankPlayer();
	void Update(float delta, Maps map, sf::Vector2f botPos[4], int botLife[4]);
	void draw(sf::RenderWindow& window);
	bool checkColission(Maps map, sf::Vector2f botPos[4], int botLife[4]);
	int tankHP = 3;
	sf::Vector2f GetPosition();
	
private:
	sf::RectangleShape tankBody;
	Animation animation;
	bool direction;
	vector<Projectiles> PVector;
	int Frames = 90;
	int ReloadTime = 0;
	bool directionUp = false;
	bool directionDown = false;
};


