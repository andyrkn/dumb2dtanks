#include "Maps.h"
#include <iostream>


Maps::Maps()
{
	for (int i = 0; i < 65; i++)
		for (int j = 0; j < 125; j++)
			this->MAP[i].push_back(make_pair(0, 0));
}


Maps::~Maps()
{
}

void Maps::MapInitialize1()
{	
	int i, j;
	noWalls = 8;
	walls[0].setSize(sf::Vector2f(1400.0f, 20.0f)); walls[0].setPosition(-100.0f, -10.0f); walls[0].setFillColor(sf::Color::Blue);
	walls[1].setSize(sf::Vector2f(1400.0f, 20.0f)); walls[1].setPosition(-100.0f,  590.0f); walls[1].setFillColor(sf::Color::Blue);
	walls[2].setSize(sf::Vector2f(20.0f, 700.0f)); walls[2].setPosition(-10.0f, -50.0f); walls[2].setFillColor(sf::Color::Blue);
	walls[3].setSize(sf::Vector2f(20.0f, 700.0f)); walls[3].setPosition(1190.0f, -50.0f); walls[3].setFillColor(sf::Color::Blue);
	walls[4].setSize(sf::Vector2f(40.0f, 210.0f)); walls[4].setPosition(580.0f, -10.0f); walls[4].setFillColor(sf::Color::Blue);
	walls[5].setSize(sf::Vector2f(40.0f, 210.0f)); walls[5].setPosition(580.0f, 400.0f); walls[5].setFillColor(sf::Color::Blue);
	walls[6].setSize(sf::Vector2f(500.0f, 40.0f)); walls[6].setPosition(-10.0f, 280.0f); walls[6].setFillColor(sf::Color::Blue);
	walls[7].setSize(sf::Vector2f(500.0f, 40.0f)); walls[7].setPosition(700.0f, 280.0f); walls[7].setFillColor(sf::Color::Blue);
	
	for (i = 0; i < 121; i++)
	{
		MAP[5][i].first = 1;
		MAP[56][i].first = 1;
	}
	for (i = 0; i < 61; i++)
	{
		MAP[i][5].first= 1;
		MAP[i][115].first = 1;
	}
	
	for (i = 55; i < 66; i++)
		for (j = 0; j < 23; j++)
			MAP[j][i].first = 1;
	for (i = 55; i < 66; i++)
		for (j = 38; j < 61; j++)
			MAP[j][i].first = 1;
	for (i = 0; i < 52; i++)
		for (j = 25; j < 36; j++)
			MAP[j][i].first = 1;
	for (i = 70; i < 121; i++)
		for (j = 25; j < 36; j++)
			MAP[j][i].first = 1;

	for (i = 0; i < 61; i++)
	{
		for (j = 0; j < 121; j++)
			cout << MAP[i][j].first;
		cout << '\n';
	}
}

void Maps::MapInitialize2()
{
	noWalls = 10;
	walls[0].setSize(sf::Vector2f(1400.0f, 20.0f)); walls[0].setPosition(-100.0f, -10.0f); walls[0].setFillColor(sf::Color::Black);
	walls[1].setSize(sf::Vector2f(1400.0f, 20.0f)); walls[1].setPosition(-100.0f, 590.0f); walls[1].setFillColor(sf::Color::Black);
	walls[2].setSize(sf::Vector2f(20.0f, 700.0f)); walls[2].setPosition(-10.0f, -50.0f); walls[2].setFillColor(sf::Color::Black);
	walls[3].setSize(sf::Vector2f(20.0f, 700.0f)); walls[3].setPosition(1190.0f, -50.0f); walls[3].setFillColor(sf::Color::Black);
	walls[4].setSize(sf::Vector2f(30.0f, 190.0f)); walls[4].setPosition(200.0f, 75.0f); walls[4].setFillColor(sf::Color::Black);
	walls[5].setSize(sf::Vector2f(30.0f, 190.0f)); walls[5].setPosition(850.0f, 75.0f); walls[5].setFillColor(sf::Color::Black);
	walls[6].setSize(sf::Vector2f(30.0f, 190.0f)); walls[6].setPosition(200.0f, 350.0f); walls[6].setFillColor(sf::Color::Black);
	walls[7].setSize(sf::Vector2f(190.0f, 30.0f)); walls[7].setPosition(770.0f, 155.0f); walls[7].setFillColor(sf::Color::Black);
	walls[8].setSize(sf::Vector2f(190.0f, 30.0f)); walls[8].setPosition(120.0f, 430.0f); walls[8].setFillColor(sf::Color::Black);
	walls[9].setSize(sf::Vector2f(190.0f, 30.0f)); walls[9].setPosition(770.0f, 430.0f); walls[9].setFillColor(sf::Color::Black);
}

void Maps::MapInitialize3()
{
	noWalls = 9;
	walls[0].setSize(sf::Vector2f(1400.0f, 20.0f)); walls[0].setPosition(-100.0f, -10.0f); walls[0].setFillColor(sf::Color::Black);
	walls[1].setSize(sf::Vector2f(1400.0f, 20.0f)); walls[1].setPosition(-100.0f, 590.0f); walls[1].setFillColor(sf::Color::Black);
	walls[2].setSize(sf::Vector2f(20.0f, 700.0f)); walls[2].setPosition(-10.0f, -50.0f); walls[2].setFillColor(sf::Color::Black);
	walls[3].setSize(sf::Vector2f(20.0f, 700.0f)); walls[3].setPosition(1190.0f, -50.0f); walls[3].setFillColor(sf::Color::Black);

	walls[4].setSize(sf::Vector2f(40.0f, 400.0f)); walls[4].setPosition(200.0f, 100.0f); walls[4].setFillColor(sf::Color::Magenta); walls[4].setSize(sf::Vector2f(40.0f, 400.0f)); walls[4].setPosition(200.0f, 100.0f); walls[4].setFillColor(sf::Color::Magenta);
	walls[5].setSize(sf::Vector2f(40.0f, 400.0f)); walls[5].setPosition(700.0f, 100.0f); walls[5].setFillColor(sf::Color::Magenta);
	walls[6].setSize(sf::Vector2f(40.0f, 400.0f)); walls[6].setPosition(1000.0f, 100.0f); walls[6].setFillColor(sf::Color::Magenta);

	walls[7].setSize(sf::Vector2f(300.0f, 40.0f)); walls[7].setPosition(200.0f, 100.0f); walls[7].setFillColor(sf::Color::Magenta);
	walls[8].setSize(sf::Vector2f(300.0f, 40.0f)); walls[8].setPosition(200.0f, 300.0f); walls[8].setFillColor(sf::Color::Magenta);

	
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

void Maps::selectMap(int whichOne)
{
	switch (whichOne)
	{
	case 0:
		MapInitialize1();
		break;
	case 1:
		MapInitialize2();
		break;
	case 2:
		MapInitialize3();
		break;
	default:
		MapInitialize3();
		break;
	}
}