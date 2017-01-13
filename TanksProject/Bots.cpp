#include "Bots.h"
#include<random>

Bots::Bots():
	animation()
{

}
 
Bots::Bots(sf::RectangleShape tankBody, sf::Texture * texture, int imageCount, float switchTime) :
	animation(texture, imageCount, switchTime)
{
	this->tankBody = tankBody;
	this->tankBody.setOrigin(sf::Vector2f(this->tankBody.getSize().x / 2, this->tankBody.getSize().y / 2));
	this->tankBody.move(0.0f, -60.0f);
	int x = rand() % 4 + 1;

	if (x == 1) direction = true; else
		if (x == 2) startDown = true; else
			if (x == 3) direction = false; else
				if (x == 4) startUp = true;
}

Bots::~Bots()
{

}

void Bots::UpdateEasy(float delta, Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[], int ib, int &isDead, PowerUps &ability)
{
	float speed = 0.15f, bulletSpeed = 0.7f;
	bool leftOnly = false, upOnly = false, downOnly = false, rightOnly = false;
	if (tankHP)
	{
		if (stillTraped)
		{
			if (startUp) { upOnly = true; tankBody.move(0.0f, -speed); }
			else
				if (startDown) { downOnly = true; tankBody.move(0.0f, speed); }
				else
					if (direction) { rightOnly = true; tankBody.move(speed, 0.0f); }
					else
					{
						leftOnly = true; tankBody.move(-speed, 0.0f);
					}
			if (!checkColissionWalls(map, PlayerPos, BotsPos, ib))
				stillTraped = false;
		}
		else
		{
			time_t timer = time(NULL);
			if (power)
			{
				if (abs(difftime(ability.getPickedUpTime(), timer)) > 19.5f)
				{
					if (power == 3 && checkColissionWalls(map, PlayerPos, BotsPos, ib))
					{
						stillTraped = true;
						power = 0;
						ability.setPickedUpTime(0);
						return;
					}
					power = 0;
					ability.setPickedUpTime(0);
				}
			}
			switch (power)
			{
			case 1:
				speed = 0.5f;
				bulletSpeed = 3.0;
				break;
			case 2:
				tankHP = backUpLife;
				break;
			}

			if (startUp) { upOnly = true; tankBody.move(0.0f, -speed); }
			else
				if (startDown) { downOnly = true; tankBody.move(0.0f, speed); }
				else
					if (direction) { rightOnly = true; tankBody.move(speed, 0.0f); }
					else
					{
						leftOnly = true; tankBody.move(-speed, 0.0f);
					}
			//==========	

			float botX = this->tankBody.getPosition().x;
			float botY = this->tankBody.getPosition().y;

			if (direction && !upOnly && !downOnly)
				if (PlayerPos.x > botX && PlayerPos.y - 30 < botY && PlayerPos.y + 30 > botY && Frames > 450)
					createbullet(upOnly, downOnly);
			if (!direction && !upOnly && !downOnly)
				if (PlayerPos.x < botX && PlayerPos.y - 30 < botY && PlayerPos.y + 30 > botY && Frames > 450)
					createbullet(upOnly, downOnly);
			if (upOnly)
				if (PlayerPos.y < botY && PlayerPos.x - 21 < botX && PlayerPos.x + 21 > botX && Frames > 450)
					createbullet(upOnly, downOnly);
			if (downOnly)
				if (PlayerPos.y > botY && PlayerPos.x - 21 < botX && PlayerPos.x + 21 > botX && Frames > 450)
					createbullet(upOnly, downOnly);

			//===========
			if (checkColission(map, PlayerPos, BotsPos, ib, isDead, ability))
				if (power != 3 || checkColissionFrame(map, PlayerPos, BotsPos, ib))
				{
					if (upOnly) {
						this->tankBody.move(0.0f, speed); setdirection(upOnly, downOnly, rightOnly, leftOnly);
					}
					if (downOnly) {
						this->tankBody.move(0.0f, -speed); setdirection(upOnly, downOnly, rightOnly, leftOnly);
					}
					if (rightOnly) {
						this->tankBody.move(-speed, 0.0f); setdirection(upOnly, downOnly, rightOnly, leftOnly);
					}
					if (leftOnly) {
						this->tankBody.move(speed, 0.0f); setdirection(upOnly, downOnly, rightOnly, leftOnly);
					}
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

			Frames++;
			ReloadTime++;

			if (ReloadTime > 900) PVector.clear();
			for (int i = 0; i < PVector.size(); i++)
				PVector[i].fire(bulletSpeed);
		}
	}
		else {
			if (!explo.positionSet) explo.setExplosionPosition(this->tankBody.getPosition());
			if(explo.isExploding)
				explo.UpdateExplosion(delta);
		}
}


void Bots::UpdateNormal(float delta, Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[], int ib, int &isDead, PowerUps &ability)
{
	bool leftOnly = false, upOnly = false, downOnly = false, rightOnly = false;
	float speed = 0.20f, bulletSpeed = 1.0f;
	if (tankHP)
	{
		if (stillTraped)
		{
			if (startUp) { upOnly = true; tankBody.move(0.0f, -speed); }
			else
				if (startDown) { downOnly = true; tankBody.move(0.0f, speed); }
				else
					if (direction) { rightOnly = true; tankBody.move(speed, 0.0f); }
					else
					{
						leftOnly = true; tankBody.move(-speed, 0.0f);
					}
			if (!checkColissionWalls(map, PlayerPos, BotsPos, ib))
				stillTraped = false;
		}
		else {
			time_t timer = time(NULL);
			if (power)
			{
				if (abs(difftime(ability.getPickedUpTime(), timer)) > 19.5f)
				{
					if (power == 3 || checkColissionWalls(map, PlayerPos, BotsPos, ib))
					{
						stillTraped = true;
						power = 0;
						ability.setPickedUpTime(0);
						return;
					}
					power = 0;
					ability.setPickedUpTime(0);
				}
			}
			switch (power)
			{
			case 1:
				speed = 0.5f;
				bulletSpeed = 3.0;
				break;
			case 2:
				tankHP = backUpLife;
				break;
			}
			if (startUp) { upOnly = true; tankBody.move(0.0f, -speed); }
			else
				if (startDown) { downOnly = true; tankBody.move(0.0f, speed); }
				else
					if (direction) { rightOnly = true; tankBody.move(speed, 0.0f); }
					else
					{
						leftOnly = true; tankBody.move(-speed, 0.0f);
					}

			Frames++; ReloadTime++;
			//===================

			float botX = this->tankBody.getPosition().x;
			float botY = this->tankBody.getPosition().y;

			if (PlayerPos.x - 30 < botX && PlayerPos.x + 30 > botX && Frames > 450) {
				if (PlayerPos.y < botY) {
					startUp = true; startDown = false; upOnly = true; startDown = false;
				}
				else {
					startUp = false; startDown = true; upOnly = false; downOnly = true;
				}
				createbullet(upOnly, downOnly);
			}

			if (PlayerPos.y - 21 < botY && PlayerPos.y + 21 > botY && Frames > 450) {
				if (PlayerPos.x < botX) {
					startUp = false; startDown = false; direction = false; downOnly = false; upOnly = false;
				}
				else {
					startUp = false; startDown = false; direction = true; downOnly = false; upOnly = false;
				}

				createbullet(upOnly, downOnly);
			}

			//==================
			if (checkColission(map, PlayerPos, BotsPos, ib, isDead, ability))
				if (power != 3 || checkColissionFrame(map, PlayerPos, BotsPos, ib))
				{
					if (upOnly) {
						this->tankBody.move(0.0f, speed); setdirection(upOnly, downOnly, rightOnly, leftOnly);
					}
					if (downOnly) {
						this->tankBody.move(0.0f, -speed); setdirection(upOnly, downOnly, rightOnly, leftOnly);
					}
					if (rightOnly) {
						this->tankBody.move(-speed, 0.0f); setdirection(upOnly, downOnly, rightOnly, leftOnly);
					}
					if (leftOnly) {
						this->tankBody.move(speed, 0.0f); setdirection(upOnly, downOnly, rightOnly, leftOnly);
					}
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

			if (ReloadTime > 600)
				PVector.clear();

			for (int i = 0; i < PVector.size(); i++)
				PVector[i].fire(bulletSpeed);
		}
	}
	else {
		if (!explo.positionSet) explo.setExplosionPosition(this->tankBody.getPosition());
		if (explo.isExploding)
			explo.UpdateExplosion(delta);
	}
}


void Bots::UpdateHard(float delta, Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[], int ib, int &isDead, vector<Projectiles> PlayerBullets, PowerUps &ability)
{
	bool incoming = false;
	bool virtualUp, virtualDown, virtualRight, virtualLeft;
	float speed = 0.25f, bulletSpeed = 1.5f;
	
	float sizeX = this->tankBody.getSize().x;
	float sizey = this->tankBody.getSize().y;
	bool leftOnly = false, upOnly = false, downOnly = false, rightOnly = false;
	if (tankHP)
	{
		if (stillTraped)
		{
			if (startUp) { upOnly = true; tankBody.move(0.0f, -speed); }
			else
				if (startDown) { downOnly = true; tankBody.move(0.0f, speed); }
				else
					if (direction) { rightOnly = true; tankBody.move(speed, 0.0f); }
					else
					{
						leftOnly = true; tankBody.move(-speed, 0.0f);
					}
			if (!checkColissionWalls(map, PlayerPos, BotsPos, ib))
				stillTraped = false;
		}
		else {
			Frames++; ReloadTime++;
			//==============MOVEMENT
			time_t timer = time(NULL);
			if (power)
			{
				if (abs(difftime(ability.getPickedUpTime(), timer)) > 19.5f)
				{
					if (power == 3 && checkColissionWalls(map, PlayerPos, BotsPos, ib))
					{
						stillTraped = true;
						power = 0;
						ability.setPickedUpTime(0);
						return;
					}
					power = 0;
					ability.setPickedUpTime(0);
				}
			}
			switch (power)
			{
			case 1:
				speed = 0.5f;
				bulletSpeed = 3.0;
				break;
			case 2:
				tankHP = backUpLife;
				break;
			}

			if (startUp) { upOnly = true; tankBody.move(0.0f, -speed); }
			else
				if (startDown) { downOnly = true; tankBody.move(0.0f, speed); }
				else
					if (direction) { rightOnly = true; tankBody.move(speed, 0.0f); }
					else
					{
						leftOnly = true; tankBody.move(-speed, 0.0f);
					}
			//======================== AIM
			float botX = this->tankBody.getPosition().x;
			float botY = this->tankBody.getPosition().y;

			if (PlayerPos.x - 30 < botX && PlayerPos.x + 30 > botX && Frames > 450) {
				if (PlayerPos.y < botY) {
					startUp = true; startDown = false; upOnly = true; startDown = false;
				}
				else {
					startUp = false; startDown = true; upOnly = false; downOnly = true;
				}
				createbullet(upOnly, downOnly);
			}

			if (PlayerPos.y - 21 < botY && PlayerPos.y + 21 > botY && Frames > 450) {
				if (PlayerPos.x < botX) {
					startUp = false; startDown = false; direction = false; downOnly = false; upOnly = false;
				}
				else {
					startUp = false; startDown = false; direction = true; downOnly = false; upOnly = false;
				}
				createbullet(upOnly, downOnly);
			}
			//==========================DODGE
			int bi;

			for (bi = 0; bi < PlayerBullets.size(); bi++)
			{
				int dir = PlayerBullets[bi].getDir();
				sf::Vector2f bulletPos = PlayerBullets[bi].getPos();

				float absx1 = abs(botX - sizeX / 2 - bulletPos.x);
				float absx2 = abs(botX + sizeX / 2 - bulletPos.x);

				if (bulletPos.x + 4.0f >= botX - sizeX / 2 && bulletPos.x - 4.0f <= botX + sizeX / 2)
					if ((bulletPos.y < botY && dir == 2) || (bulletPos.y > botY && dir == 4)) {
						if (absx1 < absx2) {
							virtualUp = virtualDown = false; virtualLeft = false; virtualRight = true;
							if (!checkColissionHard(map, BotsPos, ib, virtualUp, virtualDown, virtualLeft, virtualRight, absx1 + 8.0f)) {
								direction = true; startUp = false; startDown = false; incoming = true; break;
							}
							else {
								direction = false; startUp = false; startDown = false; incoming = true; break;
							}
						}
						else {
							virtualUp = virtualDown = false; virtualLeft = true; virtualRight = false;
							if (!checkColissionHard(map, BotsPos, ib, virtualUp, virtualDown, virtualLeft, virtualRight, absx2 + 8.0f)) {
								direction = false; startUp = false; startDown = false; incoming = true; break;
							}
							else {
								direction = true; startUp = false; startDown = false; incoming = true; break;
							}
						}
					}

				float absy1 = abs(botY - sizey / 2 - bulletPos.y);
				float absy2 = abs(botY + sizey / 2 - bulletPos.y);

				if (bulletPos.y + 4.0f >= botY - sizey / 2 && bulletPos.y - 4.0f <= botY + sizey / 2)
					if ((bulletPos.x < botX && dir == 1) || (bulletPos.x > botY && dir == 3)) {
						if (absy1 < absy2) {
							virtualUp = false; virtualDown = true; virtualLeft = virtualRight = false;
							if (!checkColissionHard(map, BotsPos, ib, virtualUp, virtualDown, virtualLeft, virtualRight, absy1 + 8.0f)) {
								startDown = true; startUp = false; incoming = true; break;
							}
							else {
								startUp = true; startDown = false; incoming = true; break;
							}
						}
						else {
							virtualUp = true; virtualDown = false; virtualLeft = virtualRight = false;
							if (!checkColissionHard(map, BotsPos, ib, virtualUp, virtualDown, virtualLeft, virtualRight, absy2 + 8.0f)) {
								startUp = true; startDown = false; incoming = true; break;
							}
							else {
								startDown = true; startUp = false; incoming = true; break;
							}

						}
					}
			}
		// 1 dreapta, 2 jos, 3 stanga, 4 sus.


		//==========================

			if (checkColission(map, PlayerPos, BotsPos, ib, isDead, ability))
				if (power != 3 || checkColissionFrame(map, PlayerPos, BotsPos, ib))
				{
					if (upOnly) {
						this->tankBody.move(0.0f, speed);
						if (!incoming)
							setdirection(upOnly, downOnly, rightOnly, leftOnly);
					}
					if (downOnly) {
						this->tankBody.move(0.0f, -speed);
						if (!incoming)
							setdirection(upOnly, downOnly, rightOnly, leftOnly);
					}
					if (rightOnly) {
						this->tankBody.move(-speed, 0.0f);
						if (!incoming)
							setdirection(upOnly, downOnly, rightOnly, leftOnly);
					}
					if (leftOnly) {
						this->tankBody.move(speed, 0.0f);
						if (!incoming)
							setdirection(upOnly, downOnly, rightOnly, leftOnly);
					}
				}

			//============================= ANIMATION + BULLET FIRE
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

			if (ReloadTime > 600)
				PVector.clear();

			for (int i = 0; i < PVector.size(); i++)
				PVector[i].fire(bulletSpeed);

		}
	}
	else {
		if (!explo.positionSet) explo.setExplosionPosition(this->tankBody.getPosition());
		if (explo.isExploding)
			explo.UpdateExplosion(delta);
	}
}


void Bots::draw(sf::RenderWindow & window)
{
	if (tankHP) {
		window.draw(this->tankBody);

		for (int i = 0; i < PVector.size(); i++)
			PVector[i].draw(window);

	}
	else
		if (explo.isExploding)
			explo.draw(window);
}


bool Bots::checkColission(Maps map,sf::Vector2f PlayerPos, sf::Vector2f BotsPos[], int ib, int &isDead, PowerUps &ability)
{
	float deltaX, deltaY, intersectX, intersectY;
	sf::RectangleShape object;
	int k;
	bool gone;

	for (int j = 0; j < PVector.size(); j++)
	{
		gone = false;
		for (k = 0; k < map.getNoWalls(); k++)
		{
			object = map.getWall(k);
			if (PVector[j].getPos().x+4.0f >= object.getPosition().x
				&& PVector[j].getPos().x-4.0f <= (object.getPosition().x + object.getSize().x))
				if (PVector[j].getPos().y+4.0f >= object.getPosition().y
					&& PVector[j].getPos().y-4.0f <= (object.getPosition().y + object.getSize().y))
				{
					PVector.erase(PVector.begin() + j);
					gone = true;
					break;
				}
		}
		if(!gone)
		if (PVector[j].getPos().x+4.0f >= PlayerPos.x - 30.0f && PVector[j].getPos().x-4.0f <= PlayerPos.x + 30.0f)
			if (PVector[j].getPos().y+4.0f >= PlayerPos.y - 21.0f && PVector[j].getPos().y-4.0f <= PlayerPos.y + 21.0f)
			{
				isDead--;
				PVector.erase(PVector.begin() + j);
				gone = true;
			}
		if (!gone)
			for (k = 0; k <= 4; k++)
				if (k != ib)
				{
					if (PVector[j].getPos().x+4.0f >= BotsPos[k].x - 30.0f && PVector[j].getPos().x-4.0f <= BotsPos[k].x + 30.0f)
						if (PVector[j].getPos().y+4.0f >= BotsPos[k].y - 21.0f && PVector[j].getPos().y-4.0f <= BotsPos[k].y + 21.0f)
						{
							PVector.erase(PVector.begin() + j);
							break;
						}
				}
	}

	deltaX = abs(this->tankBody.getPosition().x - ability.getPosition().x);
	deltaY = abs(this->tankBody.getPosition().y - ability.getPosition().y);
	intersectX = deltaX - 55.0f;
	intersectY = deltaY - 45.0f;
	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		power = ability.getType();
		if (power == 2)
			backUpLife = tankHP;
		ability.setStatus();
		ability.setPickedUpTime(time(NULL));
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
	float auxX = this->tankBody.getPosition().x;
	float auxY = this->tankBody.getPosition().y;
	for (i = 0; i < 4; i++)
		if (ib != i){
		deltaX = abs(BotsPos[i].x - this->tankBody.getPosition().x);
		deltaY = abs(BotsPos[i].y - this->tankBody.getPosition().y);
		intersectX = deltaX - 60.0f;
		intersectY = deltaY - 42.0f;
		if (intersectX < 0.0f && intersectY < 0.0f)
			return true;
		}
	deltaX = abs(this->tankBody.getPosition().x - PlayerPos.x);
	deltaY = abs(this->tankBody.getPosition().y - PlayerPos.y);
	intersectX = deltaX - 60.0f;
	intersectY = deltaY - 42.0f;
	if (intersectX < 0.0f && intersectY < 0.0f)
		return true;

	return false;
}


bool Bots::checkColissionWalls(Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[], int ib)
{
	int i;
	float deltaX, deltaY, intersectX, intersectY;
	for (i = 0; i < map.getNoWalls(); i++)
	{
		sf::Vector2f wallPosition = map.getWall(i).getPosition();
		deltaX = abs(wallPosition.x + map.getWall(i).getSize().x / 2 - this->tankBody.getPosition().x);
		deltaY = abs(wallPosition.y + map.getWall(i).getSize().y / 2 - this->tankBody.getPosition().y);
		intersectX = deltaX - (map.getWall(i).getSize().x / 2 + tankBody.getSize().x / 2);
		intersectY = deltaY - (map.getWall(i).getSize().y / 2 + tankBody.getSize().y / 2);
		if (intersectX < 0.0f && intersectY < 0.0f)
			return true;
	}
	for (i = 0; i < 4; i++)
		if (ib != i) {
			deltaX = abs(BotsPos[i].x - this->tankBody.getPosition().x);
			deltaY = abs(BotsPos[i].y - this->tankBody.getPosition().y);
			intersectX = deltaX - 60.0f;
			intersectY = deltaY - 42.0f;
			if (intersectX < 0.0f && intersectY < 0.0f)
				return true;
		}
	deltaX = abs(this->tankBody.getPosition().x - PlayerPos.x);
	deltaY = abs(this->tankBody.getPosition().y - PlayerPos.y);
	intersectX = deltaX - 60.0f;
	intersectY = deltaY - 42.0f;
	if (intersectX < 0.0f && intersectY < 0.0f)
		return true;
	return false;
}


bool Bots::checkColissionFrame(Maps map, sf::Vector2f PlayerPos, sf::Vector2f BotsPos[], int ib)
{
	int i;
	float deltaX, deltaY, intersectX, intersectY;
	for (i = 0; i < 4; i++)
	{
		sf::Vector2f wallPosition = map.getWall(i).getPosition();
		deltaX = abs(wallPosition.x + map.getWall(i).getSize().x / 2 - this->tankBody.getPosition().x);
		deltaY = abs(wallPosition.y + map.getWall(i).getSize().y / 2 - this->tankBody.getPosition().y);
		intersectX = deltaX - (map.getWall(i).getSize().x / 2 + tankBody.getSize().x / 2);
		intersectY = deltaY - (map.getWall(i).getSize().y / 2 + tankBody.getSize().y / 2);
		if (intersectX < 0.0f && intersectY < 0.0f)
			return true;
	}
	for (i = 0; i < 4; i++)
		if (ib != i) {
			deltaX = abs(BotsPos[i].x - this->tankBody.getPosition().x);
			deltaY = abs(BotsPos[i].y - this->tankBody.getPosition().y);
			intersectX = deltaX - 60.0f;
			intersectY = deltaY - 42.0f;
			if (intersectX < 0.0f && intersectY < 0.0f)
				return true;
		}
	deltaX = abs(this->tankBody.getPosition().x - PlayerPos.x);
	deltaY = abs(this->tankBody.getPosition().y - PlayerPos.y);
	intersectX = deltaX - 60.0f;
	intersectY = deltaY - 42.0f;
	if (intersectX < 0.0f && intersectY < 0.0f)
		return true;
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


void Bots::createbullet(bool upOnly,bool downOnly)
{
	Frames = 0;
	ReloadTime = 0;
	int dir = 0;
	if (upOnly) dir = 4;
	if (downOnly) dir = 2;
	if (direction && dir == 0) dir = 1;
	if (!direction && dir == 0) dir = 3;

	Projectiles bullet(this->tankBody.getPosition(), dir);
	PVector.push_back(bullet);
}


sf::Vector2f Bots::GetPosition()
{
	return this->tankBody.getPosition();
}


void Bots::changePos(float delta)
{
	this->tankBody.move(0.0f, delta);
}


bool Bots::checkColissionHard(Maps map, sf::Vector2f BotsPos[],int nrBot, bool directionUp, bool directionDown, bool directionLeft, bool directionRight, float delta)
{
	float deltaX, deltaY, intersectX, intersectY;
	int k, i;
	bool coliding=false;
	if (directionUp)
		this->tankBody.move(0.0f, -delta);
	if (directionDown)
		this->tankBody.move(0.0f, delta);
	if (directionLeft)
		this->tankBody.move(-delta, 0.0f);
	if (directionRight)
		this->tankBody.move(delta, 0.0f);

	for (i = 0; i < map.getNoWalls(); i++)
	{
		sf::Vector2f wallPosition = map.getWall(i).getPosition();
		deltaX = abs(wallPosition.x + map.getWall(i).getSize().x / 2 - this->tankBody.getPosition().x);
		deltaY = abs(wallPosition.y + map.getWall(i).getSize().y / 2 - this->tankBody.getPosition().y);
		intersectX = deltaX - (map.getWall(i).getSize().x / 2 + tankBody.getSize().x / 2);
		intersectY = deltaY - (map.getWall(i).getSize().y / 2 + tankBody.getSize().y / 2);
		if (intersectX < 0.0f && intersectY < 0.0f)
			coliding=true;
	}
	float auxX = this->tankBody.getPosition().x;
	float auxY = this->tankBody.getPosition().y;
	for (i = 0; i < 4; i++)
		if (nrBot != i) {
			deltaX = abs(BotsPos[i].x - this->tankBody.getPosition().x);
			deltaY = abs(BotsPos[i].y - this->tankBody.getPosition().y);
			intersectX = deltaX - 60.0f;
			intersectY = deltaY - 42.0f;
			if (intersectX < 0.0f && intersectY < 0.0f)
				coliding=true;
		}

	if (directionUp)
		this->tankBody.move(0.0f, delta);
	if (directionDown)
		this->tankBody.move(0.0f, -delta);
	if (directionLeft)
		this->tankBody.move(delta, 0.0f);
	if (directionRight)
		this->tankBody.move(-delta, 0.0f);
	return coliding;
}


int Bots::getDificulty()
{
	return dificultyLevel;
}


void Bots::setDificulty(int level)
{
	dificultyLevel = level;
}


void Bots::setPosition(sf::Vector2f v)
{
	this->tankBody.setPosition(v);
	tankHP = 2;
	int x = rand() % 4 + 1;

	if (x == 1) direction = true; else
		if (x == 2) startDown = true; else
			if (x == 3) direction = false; else
				if (x == 4) startUp = true;
}
