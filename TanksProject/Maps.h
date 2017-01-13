#pragma once
#include "SFML\Graphics.hpp"
class Maps
{
public:
	Maps();
	~Maps();
	void MapInitialize1();
	void MapInitialize2();
	void MapInitialize3();
	void draw(sf::RenderWindow& window);
	sf::RectangleShape getWall(int i);
	int getNoWalls();
	void selectMap(int whichOne);
private:
	sf::RectangleShape walls[10];
	sf::RectangleShape MapBackground;
	unsigned int noWalls;
};

