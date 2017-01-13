#pragma once
#include <SFML\Graphics.hpp>
#include <ctime>
#include "Maps.h"
class PowerUps
{
public:
	PowerUps();
	~PowerUps();
	void update();
	void createPowerUp(time_t startTime, Maps map, sf::Vector2f playerPos);
	double getTime();
	bool checkIsON();
	void deletePowerUp();
	void setPosition(Maps map);
	void draw(sf::RenderWindow &window);
	sf::Vector2f getPosition();
	int getType();
	void setStatus();
	void setPickedUpTime(time_t timer);
	time_t getPickedUpTime();
private:
	sf::RectangleShape body;
	sf::Texture texture;
	int type;
	sf::Vector2f position;
	time_t startTime, pickedUpTime=0.0f;
	bool isOn = false;
	double deltaTime;

};

