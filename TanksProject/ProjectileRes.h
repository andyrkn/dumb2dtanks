#pragma once
#include<SFML\Graphics.hpp>

sf::Texture ProjectileTexturegg;
sf::Texture SmokeTexture;

void _loadProjectileTexture()
{
	ProjectileTexturegg.loadFromFile("Textures/bullet.png");
	SmokeTexture.loadFromFile("Textures/smoke2.png");
}