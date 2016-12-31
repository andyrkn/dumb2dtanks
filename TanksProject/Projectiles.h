#pragma once
#include<SFML\Graphics.hpp>

class Projectiles
{
public:
	Projectiles(sf::Vector2f pos, int dir);
	~Projectiles();
	int getRight();
	int getLeft();
	int getTop();
	int getBottom();
	sf::Vector2f getPos();

	void fire(int speed);
	void draw(sf::RenderWindow &window);

private:
	sf::RectangleShape projectile;
	// 1 dreapta, 2 jos, 3 stanga, 4 sus.
	int dir;
};

