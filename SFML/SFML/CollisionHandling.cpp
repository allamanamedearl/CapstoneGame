#include "CollisionHandling.h"
#include <iostream>

CollisionHandling::CollisionHandling(TextureManager* tm)
{
	textMan = tm;
}


CollisionHandling::~CollisionHandling()
{
	delete textMan;
	textMan = nullptr;
}
void CollisionHandling::GetWorldToTileCoords(sf::Vector2f pos)
{
	tileSize =textMan->GetTileSize();
	float tileX = pos.x / tileSize;
	float tileY = pos.y / tileSize;
	//maybe round up number
	std::cout << "Tile X = " << tileX << " Tile Y = " << tileY << " tileSize "<< tileSize << std::endl;

}
