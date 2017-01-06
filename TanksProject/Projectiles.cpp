#include "Projectiles.h"
#include"ProjectileRes.h"


Projectiles::Projectiles(sf::Vector2f pos, int dir)
{
	_loadProjectileTexture();
	this->dir = dir;
	sprite.setTexture(ProjectileTexturegg);
	sprite.setPosition(pos);
}


Projectiles::~Projectiles()
{

}


sf::Vector2f Projectiles::getPos()
{
	return this->sprite.getPosition();
}

void Projectiles::fire(int speed)
{
	this->sprite.setRotation(0);

		if (this->dir == 1) this->sprite.move(speed, 0.0f);
		if (this->dir == 2) {this->sprite.move(0.0f, speed); sprite.setRotation(-90);}
		if (this->dir == 3){this->sprite.move(-speed, 0.0f); sprite.setRotation(180);}
		if (this->dir == 4){this->sprite.move(0.0f, -speed); sprite.setRotation(90);}

		sf::Sprite newSprite;
		newSprite.setTexture(SmokeTexture);
		newSprite.setPosition(sprite.getPosition());
		if (dir == 4) newSprite.move(-3.0f, 3.0f);
		if (dir == 2 ) newSprite.move(5.0f, -16.0f);
		newSprite.setOrigin(sf::Vector2f(6.0f, 13.0f));
		newSprite.setColor(sf::Color(255, 255, 255,8));
		if (dir == 1) newSprite.setRotation(180);
		if (dir == 2) newSprite.setRotation(-90);
		if (dir == 4) newSprite.setRotation(90);
		smokeSprite.push_back(newSprite);
}

void Projectiles::draw(sf::RenderWindow & window)
{
	window.draw(this->sprite);
	for (int i = 0; i < smokeSprite.size(); i++) {
		sf::Color color;
		color = smokeSprite[i].getColor();
		int alpha = color.a;
		if (alpha >0)
			smokeSprite[i].setColor(sf::Color(255, 255, 255, alpha - 1));
		if(alpha)
			window.draw(smokeSprite[i]);
	}
}

