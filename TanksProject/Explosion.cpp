#include "Explosion.h"
#include "ExplosionResources.h"


Explosion::Explosion()
{
	_loadExplosion();
	ExplosionSprite.setTexture(ExplosionTexture);
	TextureWidth = ExplosionTexture.getSize().x / 5;
	TextureHeight = ExplosionTexture.getSize().y / 5;
	ExplosionSprite.setScale(sf::Vector2f(0.4f, 0.5f));
}

Explosion::~Explosion()
{
}

void Explosion::UpdateExplosion(float delta)
{
	if (isExploding) {
		frameTime += delta;
		if (frameTime >= SwitchTime) {
			frameTime -= SwitchTime;
			if (column < 4) column++;
			else {
				column = 0;
				if (row < 4) row++;
				else isExploding = false;
			}
		}

		ExplosionSprite.setTextureRect(sf::IntRect(row*TextureWidth, column*TextureHeight, TextureWidth, TextureHeight));
	}
}

void Explosion::draw(sf::RenderWindow & window)
{
	window.draw(ExplosionSprite);
}

void Explosion::setExplosionPosition(sf::Vector2f Position)
{
	ExplosionSprite.setPosition(sf::Vector2f(Position.x - 30.0f, Position.y - 30.0f));
	positionSet = true;
	ExplosionSound.play();
}
