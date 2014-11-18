#pragma once
#include "TileMap.h"
class CollisionHandling
{
public:
	CollisionHandling(TextureManager* tm, TileMap* map);
	~CollisionHandling();
	sf::Vector2f GetWorldToTileCoords(sf::Vector2f pos);
	bool PlayerCollisionDetection(char pressed, sf::Vector2f playerPos, sf::Vector2f playerVel);
private:
	int tileSize;
	TextureManager* textMan;
	TileMap* tileMap;
};

