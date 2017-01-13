#pragma once
#include<SFML\Graphics.hpp>

sf::Texture bgTexture;

bool mapLoaded = false;

void _loadMapTexture(int x) {
	mapLoaded = true;

	switch (x)
	{
	case 0: {
		bgTexture.loadFromFile("Textures/MAP1Texture.png");

		break; }
	case 1: {
		bgTexture.loadFromFile("Textures/MAP2Texture.png");

		break; }
	case 2: {
		bgTexture.loadFromFile("Textures/MAP3Texture.png");

		break; }
	default: {
		bgTexture.loadFromFile("Textures/MAP3Texture.png");

		break; }
	}

}
