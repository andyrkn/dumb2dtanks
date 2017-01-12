#pragma once
#include<SFML\Graphics.hpp>

class Explosion
{
public:
	Explosion();
	~Explosion();

	void UpdateExplosion(float delta);
	void draw(sf::RenderWindow& window);
	void setExplosionPosition(sf::Vector2f Position);

	bool isExploding = true;
	bool positionSet = false;

private:

	sf::Sprite ExplosionSprite;
	float frameTime=0.0f, SwitchTime=0.03f;
	int TextureWidth, TextureHeight;
	int row = 0, column = 0;
	
};

