#pragma 
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <vector>
#include "Projectiles.h"
using namespace std;

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
	bool directionUp=false;
	bool directionDown=false;
	vector<Projectiles> PVector;
	int Frames = 90;
	int ReloadTime = 0;
};


