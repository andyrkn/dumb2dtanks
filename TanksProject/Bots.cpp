#include "Bots.h"
#include<random>

Bots::Bots():
	animation()
{

}
 
Bots::Bots(sf::RectangleShape tankBody, sf::Texture * texture, int imageCount, float switchTime):
	animation(texture, imageCount, switchTime)
{
	this->tankBody = tankBody;
	this->tankBody.setOrigin(sf::Vector2f(this->tankBody.getSize().x / 2, this->tankBody.getSize().y / 2));

	int x = rand() % 4 + 1;

	if (x == 1) direction = true; else
		if (x == 2) startDown = true; else
			if (x == 3) direction = false; else
				if (x == 4) startUp = true;

}

Bots::~Bots()
{

}

void Bots::UpdateEasy(float delta, Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[])
{
	if (tankHP) {

		bool leftOnly = false, upOnly = false, downOnly = false, rightOnly = false;

		if (startUp)   {	upOnly    = true; tankBody.move(0.0f, -0.1f);   }	else
		if (startDown) {	downOnly  = true; tankBody.move(0.0f, 0.1f);    }	else
		if (direction) {	rightOnly = true; tankBody.move(0.1f, 0.0f);	}	else
			{	leftOnly = true; tankBody.move(-0.1f, 0.0f);	}
		

		if (checkColission(map,PlayerPos,BotsPos))
		{
			if (upOnly) {
				this->tankBody.move(0.0f, 0.1f); setdirection(upOnly, downOnly, rightOnly, leftOnly); }
			if (downOnly) {
				this->tankBody.move(0.0f, -0.1f); setdirection(upOnly, downOnly, rightOnly, leftOnly); }
			if (rightOnly) {
				this->tankBody.move(-0.1f, 0.0f); setdirection(upOnly, downOnly, rightOnly, leftOnly);	}
			if (leftOnly) {
				this->tankBody.move(0.1f, 0.0f); setdirection(upOnly, downOnly, rightOnly, leftOnly); }				
		}

		animation.Update(delta, direction);
		this->tankBody.setTextureRect(animation.currentTexture);

		this->tankBody.setRotation(0);

		if (upOnly)
			this->tankBody.setRotation(90);
		if (downOnly)
			this->tankBody.setRotation(-90);
		if (direction)
		{
			if (upOnly)
				this->tankBody.setRotation(-90);
			if (downOnly)
				this->tankBody.setRotation(90);
		}


		Frames++; ReloadTime++;

		if (Frames>360)
		{
			ReloadTime = 0;
			Frames = 0;
			int dir = 0;
			if (upOnly) dir = 4;
			if (downOnly) dir = 2;
			if (direction && dir == 0) dir = 1;
			if (!direction && dir == 0) dir = 3;

			Projectiles bullet(this->tankBody.getPosition(), dir);
			PVector.push_back(bullet);
		}

		if (ReloadTime > 900) {
			PVector.clear();
			ReloadTime = 0;
		}

		for (int i = 0; i < PVector.size(); i++)
			PVector[i].fire(2);

	}
}



void Bots::UpdateNormal(float delta, Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[])
{
	if (tankHP) {

	}
}


void Bots::UpdateHard(float delta, Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[])
{
	if (tankHP) {

	}
}


void Bots::draw(sf::RenderWindow & window)
{
	if (tankHP) {
		window.draw(this->tankBody);

		for (int i = 0; i < PVector.size(); i++)
			PVector[i].draw(window);
	}
}


bool Bots::checkColission(Maps map,sf::Vector2f PlayerPos, sf::Vector2f BotsPos[])
{
	float deltaX, deltaY, intersectX, intersectY;
	sf::RectangleShape object;

	for (int j = 0; j < PVector.size(); j++)
		for (int k = 0; k < map.getNoWalls(); k++)
		{
			object = map.getWall(k);
			if (PVector[j].getPos().x >= object.getPosition().x
				&& PVector[j].getPos().x <= (object.getPosition().x + object.getSize().x))
				if (PVector[j].getPos().y >= object.getPosition().y
					&& PVector[j].getPos().y <= (object.getPosition().y + object.getSize().y))
				{
					PVector.erase(PVector.begin() + j);
					break;
				}
		}


	int i;
	for ( i = 0; i < map.getNoWalls(); i++)
	{
		sf::Vector2f wallPosition = map.getWall(i).getPosition();
		deltaX = abs(wallPosition.x + map.getWall(i).getSize().x / 2 - this->tankBody.getPosition().x);
		deltaY = abs(wallPosition.y + map.getWall(i).getSize().y / 2 - this->tankBody.getPosition().y);
		intersectX = deltaX - (map.getWall(i).getSize().x / 2 + tankBody.getSize().x / 2);
		intersectY = deltaY - (map.getWall(i).getSize().y / 2 + tankBody.getSize().y / 2);
		if (intersectX < 0.0f && intersectY < 0.0f)
			return true;
	}

	for (i = 0; i < 3; i++)
		//if(BotsPos[i] != this->tankBody.getPosition() ){
		if (BotsPos[i].x != this->tankBody.getPosition().x &&
			BotsPos[i].y != this->tankBody.getPosition().y){
		deltaX = abs(BotsPos[i].x - this->tankBody.getPosition().x);
		deltaY = abs(BotsPos[i].y - this->tankBody.getPosition().y);
		intersectX = deltaX - 60.0f;
		intersectY = deltaY - 42.0f;
		if (intersectX < 0.0f && intersectY < 0.0f)
			return true;
		}

	return false;
}


void Bots::setdirection(bool  upOnly, bool  downOnly, bool  rightOnly, bool  leftOnly)
{
	int x;

	while (true) {
		x = rand() % 4 + 1;

		if (x == 1 && !rightOnly) {
			direction = true; startDown = false; startUp = false;
			break;
		}

		if(x==2 && !downOnly){
			startDown = true; startUp = false;
			break;
		}
		
		if (x == 3 && !leftOnly) {
			direction = false; startUp = false; startDown = false;
			break;
		}

		if (x == 4 && !upOnly) {
			startUp = true; startDown = false;
			break;
		}
	}
}


sf::Vector2f Bots::GetPosition()
{
	return this->tankBody.getPosition();
}