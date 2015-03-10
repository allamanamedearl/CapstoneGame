#pragma once
#include "TileMap.h"
class CollisionHandling
{
public:
	CollisionHandling(TextureManager* tm, TileMap* map);
	~CollisionHandling();
	sf::Vector2f GetWorldToTileCoords(sf::Vector2f pos);
	sf::Vector2f GetTileToWorldCoords(sf::Vector2f pos);
	bool PlayerCollisionDetection(char pressed, sf::Vector2f playerPos, sf::Vector2f playerVel);
	
	void CheckBreakableTiles(sf::Vector2f pos);
private:
	bool CheckIfTile(sf::Vector2f pos);//for checking if there's a tile there or just blank space
	int tileSize;
	TextureManager* textMan;
	TileMap* tileMap;
};

