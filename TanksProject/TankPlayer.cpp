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
	directionUp = false;
	directionDown = false;
	this->tankBody.setRotation(0);

	bool didItMove=false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { this->tankBody.move(-0.1f, 0.0f);  direction = false; didItMove = true; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { this->tankBody.move(0.0f, 0.1f); didItMove = true; directionDown = true; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { this->tankBody.move(0.1f, 0.0f); direction = true; didItMove = true; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) { this->tankBody.move(0.0f, -0.1f); didItMove = true; directionUp = true; }

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
}

void TankPlayer::draw(sf::RenderWindow& window)
{
	window.draw(this->tankBody);
}
