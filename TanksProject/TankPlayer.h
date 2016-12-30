#pragma 
#include <SFML\Graphics.hpp>
#include "Animation.h"

class TankPlayer
{
public:
	TankPlayer(sf::RectangleShape tankBody, sf::Texture* texture, int imageCount, float switchTime);
	~TankPlayer();
	void Update(float delta);
	void draw(sf::RenderWindow& window);
	
private:
	sf::RectangleShape tankBody;
	Animation animation;
	bool direction;

};


