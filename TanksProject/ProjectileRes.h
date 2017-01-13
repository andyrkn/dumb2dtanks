#pragma once
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>

sf::Texture ProjectileTexturegg;
sf::Texture SmokeTexture;

sf::SoundBuffer SoundBuffer;
sf::Sound TankFireWAV;

bool loaded = false;

void _loadProjectileTexture()
{
	if (!loaded) {
		ProjectileTexturegg.loadFromFile("Textures/bullet.png");
		SmokeTexture.loadFromFile("Textures/smoke.png");
		SoundBuffer.loadFromFile("Sounds/TankFire.wav");
		TankFireWAV.setBuffer(SoundBuffer);
		loaded = true;
	}
}