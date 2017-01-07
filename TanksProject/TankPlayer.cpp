#include "TankPlayer.h"


TankPlayer::TankPlayer(sf::RectangleShape tankBody, sf::Texture* texture, int imageCount, float switchTime) :
	animation(texture,imageCount, switchTime)
{
	this->tankBody = tankBody;
	this->tankBody.setOrigin(sf::Vector2f(this->tankBody.getSize().x / 2, this->tankBody.getSize().y / 2));

}


TankPlayer::~TankPlayer()
{
}

void TankPlayer::Update(float delta, Maps map, sf::Vector2f botPos[4], int botLife[4])
{
	this->tankBody.setRotation(0);
	
	float speed = 0.3f;
	
	bool didItMove=false, rightOnly=false, leftOnly = false, upOnly = false, downOnly = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { this->tankBody.move(-speed, 0.0f);  directionUp = false; directionDown = false; leftOnly = true; direction = false; didItMove = true; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { this->tankBody.move(0.0f, speed); directionUp = false; directionDown = true; downOnly = true; didItMove = true;direction = false; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { this->tankBody.move(speed, 0.0f); directionUp = false; directionDown = false; rightOnly = true; direction = true; didItMove = true; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) { this->tankBody.move(0.0f, -speed); directionUp = true; directionDown = false;  upOnly = true; didItMove = true; direction = false; }

	if (checkColission(map, botPos, botLife))
	{
		if (rightOnly && upOnly)
			this->tankBody.move(-speed, speed);
		else if(rightOnly && downOnly)
			this->tankBody.move(-speed, -speed);
		else if(leftOnly && downOnly)
			this->tankBody.move(speed, -speed);
		else if(leftOnly && upOnly)
			this->tankBody.move(speed, speed);
		else
		{
			if (upOnly)
				this->tankBody.move(0.0f, speed);
			if (downOnly)
				this->tankBody.move(0.0f, -speed);
			if (rightOnly)
				this->tankBody.move(-speed, 0.0f);
			if (leftOnly)
				this->tankBody.move(speed, 0.0f);
		}	
	}

	if (didItMove) {
		animation.Update(delta, direction);
		this->tankBody.setTextureRect(animation.currentTexture);
	}
	if (directionUp)
		this->tankBody.setRotation(90);
	if (directionDown)
		this->tankBody.setRotation(-90);
	if (direction)
	{
		if (directionUp)
			this->tankBody.setRotation(-90);
		if (directionDown)
			this->tankBody.setRotation(90);
	}

	Frames++;
	ReloadTime++;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && Frames>90)
	{
		ReloadTime = 0;
		Frames = 0;
		int dir = 0;
		if (directionUp) dir = 4;
		if (directionDown) dir = 2;
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
		PVector[i].fire(1.0f);
}

void TankPlayer::draw(sf::RenderWindow& window)
{
	window.draw(this->tankBody);

	for (int i = 0; i < PVector.size(); i++)
		PVector[i].draw(window);
}

bool TankPlayer::checkColission(Maps map, sf::Vector2f botPos[4], int botLife[4])
{
	int k;
	bool gone;
	float deltaX, deltaY, intersectX, intersectY;
	sf::RectangleShape object;

	for (int j = 0; j < PVector.size(); j++)
	{
		gone = false;
		for (k = 0; k < map.getNoWalls(); k++)
		{
			object = map.getWall(k);
			if (PVector[j].getPos().x >= object.getPosition().x
				&& PVector[j].getPos().x <= (object.getPosition().x + object.getSize().x))
				if (PVector[j].getPos().y >= object.getPosition().y
					&& PVector[j].getPos().y <= (object.getPosition().y + object.getSize().y))
				{
					PVector.erase(PVector.begin() + j);
					gone = true;
					break;
				}
		}
		if(!gone)
		for (k = 0; k < 3; k++)
		{
			if (PVector[j].getPos().x >= botPos[k].x - 30.0f && PVector[j].getPos().x <= botPos[k].x + 30.0f)
				if (PVector[j].getPos().y >= botPos[k].y - 21.0f && PVector[j].getPos().y <= botPos[k].y + 21.0f)
				{
					botLife[k]--;
					PVector.erase(PVector.begin() + j);
					break;
				}
		}
	}
	for (k = 0; k < 3; k++)
		if(botLife[k])
	{
		deltaX = abs(this->tankBody.getPosition().x - botPos[k].x);
		deltaY = abs(this->tankBody.getPosition().y - botPos[k].y);
		intersectX = deltaX - 60.0f;
		intersectY = deltaY - 42.0f;
		if (intersectX < 0.0f && intersectY < 0.0f)
			return true;
	}
	for (int i = 0; i < map.getNoWalls(); i++)
	{
		sf::Vector2f wallPosition = map.getWall(i).getPosition();
		deltaX = abs(wallPosition.x + map.getWall(i).getSize().x / 2 - this->tankBody.getPosition().x);
		deltaY = abs(wallPosition.y + map.getWall(i).getSize().y / 2 - this->tankBody.getPosition().y);
		intersectX = deltaX - (map.getWall(i).getSize().x / 2 + tankBody.getSize().x / 2);
		intersectY = deltaY - (map.getWall(i).getSize().y / 2 + tankBody.getSize().y / 2);
		if (intersectX < 0.0f && intersectY < 0.0f)
			return true;
	}
	return false;
}

sf::Vector2f TankPlayer::GetPosition()
{
	return this->tankBody.getPosition();
}

vector<Projectiles> TankPlayer::getBullets()
{
	return PVector;
}
