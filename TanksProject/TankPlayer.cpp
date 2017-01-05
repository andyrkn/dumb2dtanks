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

void TankPlayer::Update(float delta, Maps map)
{
	this->tankBody.setRotation(0);

	bool didItMove=false, rightOnly=false, leftOnly = false, upOnly = false, downOnly = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { this->tankBody.move(-0.1f, 0.0f);  leftOnly = true; direction = false; didItMove = true; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { this->tankBody.move(0.0f, 0.1f); downOnly = true; didItMove = true;direction = false; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { this->tankBody.move(0.1f, 0.0f); rightOnly = true; direction = true; didItMove = true; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) { this->tankBody.move(0.0f, -0.1f); upOnly = true; didItMove = true; direction = false; }

	if (checkColission(map))
	{
		if (rightOnly && upOnly)
			this->tankBody.move(-0.1f, 0.1f);
		else if(rightOnly && downOnly)
			this->tankBody.move(-0.1f, -0.1f);
		else if(leftOnly && downOnly)
			this->tankBody.move(0.1f, -0.1f);
		else if(leftOnly && upOnly)
			this->tankBody.move(0.1f, 0.1f);
		else
		{
			if (upOnly)
				this->tankBody.move(0.0f, 0.1f);
			if (downOnly)
				this->tankBody.move(0.0f, -0.1f);
			if (rightOnly)
				this->tankBody.move(-0.1f, 0.0f);
			if (leftOnly)
				this->tankBody.move(0.1f, 0.0f);
		}	
	}

	if (didItMove) {
		animation.Update(delta, direction);
		this->tankBody.setTextureRect(animation.currentTexture);
	}

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
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && Frames>90)
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

void TankPlayer::draw(sf::RenderWindow& window)
{
	window.draw(this->tankBody);

	for (int i = 0; i < PVector.size(); i++)
		PVector[i].draw(window);
}

bool TankPlayer::checkColission(Maps map)
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
