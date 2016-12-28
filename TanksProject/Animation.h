#pragma once
#include <SFML\Graphics.hpp>	
class Animation
{
public:
	Animation(sf::Texture* texture, int imageCount, float switchTime);
	~Animation();
	sf::IntRect currentTexture;
	void Update(float delta, bool right);

private:
	float imageCount;
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime;
};

