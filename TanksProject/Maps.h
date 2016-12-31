#pragma once
#include "SFML\Graphics.hpp"
class Maps
{
public:
	Maps();
	~Maps();
	void MapInitialize1();
	void draw(sf::RenderWindow& window);
	sf::RectangleShape getWall(int i);
	int getNoWalls();
private:
	sf::RectangleShape walls[10];
	unsigned int noWalls;
};

