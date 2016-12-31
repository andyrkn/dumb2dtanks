#include "Maps.h"
#include "SFML\Graphics.hpp"


Maps::Maps()
{
}


Maps::~Maps()
{
}

void Maps::MapInitialize1()
{
	noWalls = 7;
	walls[0].setSize(sf::Vector2f(1400.0f, 20.0f)); walls[0].setPosition(-100.0f, -10.0f); walls[0].setFillColor(sf::Color::Blue);
	walls[1].setSize(sf::Vector2f(1400.0f, 20.0f)); walls[1].setPosition(-100.0f,  590.0f); walls[1].setFillColor(sf::Color::Blue);
	walls[2].setSize(sf::Vector2f(20.0f, 700.0f)); walls[2].setPosition(-10.0f, -50.0f); walls[2].setFillColor(sf::Color::Blue);
	walls[3].setSize(sf::Vector2f(20.0f, 700.0f)); walls[3].setPosition(1190.0f, -50.0f); walls[3].setFillColor(sf::Color::Blue);
	walls[4].setSize(sf::Vector2f(200.0f, 100.0f)); walls[4].setPosition(500.0f, 300.0f); walls[4].setFillColor(sf::Color::Blue);
	walls[5].setSize(sf::Vector2f(300.0f, 50.0f)); walls[5].setPosition(650.0f, 400.0f); walls[5].setFillColor(sf::Color::Blue);
	walls[6].setSize(sf::Vector2f(30.0f, 300.0f)); walls[6].setPosition(900.0f, 50.0f); walls[6].setFillColor(sf::Color::Blue);
}

void Maps::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < noWalls; i++)
		window.draw(walls[i]);
}

sf::RectangleShape Maps::getWall(int i)
{
	return walls[i];
}

int Maps::getNoWalls()
{
	return noWalls;
}
