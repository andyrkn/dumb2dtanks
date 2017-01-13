#include "PowerUps.h"
#include <random>



PowerUps::PowerUps()
{
	body.setSize(sf::Vector2f(45.0f, 45.0f));
	body.setOrigin(sf::Vector2f(body.getSize().x / 2, body.getSize().y / 2));
	//body.setFillColor(sf::Color::Black);
}

PowerUps::~PowerUps()
{
}

void PowerUps::update()
{
	time_t timer = time(NULL);
	deltaTime = abs(difftime(startTime, timer));
}

void PowerUps::createPowerUp(time_t startTime, Maps map, sf::Vector2f playerPos)
{
	this->startTime = startTime;
	type = rand() % 3+1;
	//type = 3;
	switch (type)
	{
	case 1:
		texture.loadFromFile("Textures/PowerUp1.jpg");
		break;
	case 2:
		texture.loadFromFile("Textures/PowerUp2.png");
		break;
	case 3:
		texture.loadFromFile("Textures/PowerUp3.png");
		break;
	}
	body.setTexture(&texture);
	setPosition(map);	
	isOn = true;
}

double PowerUps::getTime()
{
	return deltaTime;
}

bool PowerUps::checkIsON()
{
	return isOn;
}

void PowerUps::deletePowerUp()
{
	this->body.move(sf::Vector2f(0.0f, 2000.0f));
	isOn = false;
}


void PowerUps::setPosition(Maps map)
{
	bool repeat = true;
	float posX, posY, deltaX, deltaY, intersectX, intersectY;
	sf::RectangleShape object;
	while (repeat)
	{
		repeat = false;
		posX = rand() % 1100 + 50;
		posY = rand() % 500 + 50;
		for (int i = 4; i < map.getNoWalls(); i++)
		{
			sf::Vector2f wallPosition = map.getWall(i).getPosition();
			deltaX = abs(wallPosition.x + map.getWall(i).getSize().x / 2 - posX);
			deltaY = abs(wallPosition.y + map.getWall(i).getSize().y / 2 - posY);
			intersectX = deltaX - (map.getWall(i).getSize().x / 2 + body.getSize().x/2);
			intersectY = deltaY - (map.getWall(i).getSize().y / 2 + body.getSize().y/2);
			if (intersectX < 0.0f && intersectY < 0.0f)
			{
				repeat = true;
				break;
			}		
		}
	}
	body.setPosition(sf::Vector2f(posX, posY));
}


void PowerUps::draw(sf::RenderWindow & window)
{
	window.draw(body);
}

sf::Vector2f PowerUps::getPosition()
{
	return sf::Vector2f(body.getPosition().x, body.getPosition().y);
}

int PowerUps::getType()
{
	return type;
}

void PowerUps::setStatus()
{
	isOn = false;
}

void PowerUps::setPickedUpTime(time_t timer)
{
	pickedUpTime = timer;
}

time_t PowerUps::getPickedUpTime()
{
	return pickedUpTime;
}
