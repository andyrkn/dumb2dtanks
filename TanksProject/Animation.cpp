#include "Animation.h"



Animation::Animation(sf::Texture* texture, int imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	int curentImage = 0;

	currentTexture.width = texture->getSize().x / float(imageCount);
	currentTexture.height = texture->getSize().y;
}


Animation::~Animation()
{
}

void Animation::Update(float delta, bool right)
{
	totalTime += delta;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount)
			currentImage.x = 0;
	}

	currentTexture.top = 0;

	if (right)
	{
		currentTexture.left = currentImage.x * currentTexture.width;
		currentTexture.width = abs(currentTexture.width);
	}
	else
	{
		currentTexture.left = (currentImage.x + 1) * abs(currentTexture.width);
		currentTexture.width = -abs(currentTexture.width);
	}
}
