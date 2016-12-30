#include "Projectiles.h"



Projectiles::Projectiles(sf::Vector2f pos, int dir)
{
	this->projectile.setSize(sf::Vector2f(5.0f, 3.0f));
	this->projectile.setPosition(pos);
	this->dir = dir;
	this->projectile.setFillColor(sf::Color::Red);
}


Projectiles::~Projectiles()
{
}

int Projectiles::getRight()
{
	return this->projectile.getPosition().x+this->projectile.getSize().x;
}

int Projectiles::getLeft()
{
	return this->projectile.getPosition().x;
}

int Projectiles::getTop()
{
	return this->projectile.getPosition().y;
}

int Projectiles::getBottom()
{
	return this->projectile.getPosition().y + this->projectile.getSize().y;
}

void Projectiles::fire(int speed)
{
	if(this->projectile.getPosition().x<1300 && this->projectile.getPosition().x>-100
		&& this->projectile.getPosition().y<1300 && this->projectile.getPosition().y > -100)
		{
		if(this->dir == 1) this->projectile.move(speed, 0.0f);
		if(this->dir == 2)this->projectile.move(0.0f, speed);
		if(this->dir == 3)this->projectile.move(-speed, 0.0f);
		if(this->dir == 4)this->projectile.move(0.0f, -speed);
		}

}

void Projectiles::draw(sf::RenderWindow & window)
{
	window.draw(this->projectile);
}

