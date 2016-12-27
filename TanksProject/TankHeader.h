#include<SFML\Graphics.hpp>
#include<Windows.h>
#define ToF(a) static_cast<float>(a)

void inittextures(sf::RectangleShape tanks[], int nr, sf::Vector2f tanksize, sf::Texture textures[],sf::RectangleShape maintanks[])
{
	textures[0].loadFromFile("Textures/tanksblue.png");  tanks[0].setTexture(&textures[0]);
	textures[1].loadFromFile("Textures/tankswhite.png"); tanks[1].setTexture(&textures[1]);
	textures[2].loadFromFile("Textures/tanksgreen.png"); tanks[2].setTexture(&textures[2]);
	textures[3].loadFromFile("Textures/tankspurple.png"); tanks[3].setTexture(&textures[3]);
	textures[4].loadFromFile("Textures/tanksyellow.png"); tanks[4].setTexture(&textures[4]);

	float x;
	sf::Vector2u texturesize = textures[0].getSize();
	texturesize.x /= 2;

	for (int i = 0; i < nr; i++) {
		x = 100 * (i + 5);
		tanks[i].setPosition(x, 350.0f);
		tanks[i].setSize(tanksize);
		tanks[i].setTextureRect(sf::IntRect(0, 0, texturesize.x, texturesize.y));

		maintanks[i] = tanks[i];
	}

}

bool mouseclickbutton(sf::Vector2i MousePos, sf::RectangleShape button)
{
	sf::Vector2f buttonsize(button.getSize().x, button.getSize().y);
	sf::Vector2f buttonposi(button.getPosition().x, button.getPosition().y);

	if (ToF(MousePos.x) >= (buttonposi.x - buttonsize.x / 2) && ToF(MousePos.x) <= (buttonposi.x + buttonsize.x / 2))
		if (ToF(MousePos.y) <= (buttonposi.y + buttonsize.y / 2) && ToF(MousePos.y) >= (buttonposi.y - buttonsize.y / 2))
			return true;
	return false;
}

