#pragma once
#include<SFML\Graphics.hpp>
#include<vector>
using namespace std;

class Projectiles
{
public:
	Projectiles(sf::Vector2f pos, int dir);
	~Projectiles();
	sf::Vector2f getPos();
	int getDir();
	void fire(float speed);
	void draw(sf::RenderWindow &window);

private:
	sf::Sprite sprite;
	vector<sf::Sprite> smokeSprite;
	// 1 dreapta, 2 jos, 3 stanga, 4 sus.
	int dir;
};

