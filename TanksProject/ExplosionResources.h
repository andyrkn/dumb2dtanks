#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>

sf::Texture ExplosionTexture;

sf::SoundBuffer ExplosionBuffer;
sf::Sound ExplosionSound;

bool explLoaded = false;
void _loadExplosion()
{
	if (!explLoaded) {
		ExplosionTexture.loadFromFile("Textures/Explosions/Explosion.png");
		ExplosionBuffer.loadFromFile("Sounds/Explosion.wav");
		ExplosionSound.setBuffer(ExplosionBuffer);
		explLoaded = true;
	}

}