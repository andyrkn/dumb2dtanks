#include "TankPlayer.h"



TankPlayer::TankPlayer(sf::RectangleShape tankBody, sf::Texture* texture, int imageCount, float switchTime) :
	animation(texture,imageCount, switchTime)
{
	this->tankBody = tankBody;
}


TankPlayer::~TankPlayer()
{
}

void TankPlayer::Update(float delta)
{
	this->tankBody.setRotation(0);

	bool didItMove=false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { this->tankBody.move(-0.1f, 0.0f);  direction = false; didItMove = true; directionDown = directionUp = false; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { this->tankBody.move(0.0f, 0.1f); didItMove = true; directionDown = true; directionUp = false; direction = false; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { this->tankBody.move(0.1f, 0.0f); direction = true; didItMove = true; directionDown = directionUp = false; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) { this->tankBody.move(0.0f, -0.1f); didItMove = true; directionUp = true; directionDown = false; direction = false; }

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
		PVector[i].fire(2);

}

void TankPlayer::draw(sf::RenderWindow& window)
{
	window.draw(this->tankBody);

	for (int i = 0; i < PVector.size(); i++)
		PVector[i].draw(window);
}
