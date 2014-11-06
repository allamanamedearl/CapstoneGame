#pragma once
#include "TileMap.h"
class CollisionHandling
{
public:
	CollisionHandling(TextureManager* tm);
	~CollisionHandling();
	void GetWorldToTileCoords(sf::Vector2f pos);
private:
	int tileSize;
	TextureManager* textMan;
};

