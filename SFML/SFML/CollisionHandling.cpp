#include "CollisionHandling.h"
#include <iostream>

CollisionHandling::CollisionHandling(TextureManager* tm, TileMap* map)
{
	textMan = tm;
	//another tileSize in TextureManager which gets passed the engine tileSize
	tileMap = map;
	
}


CollisionHandling::~CollisionHandling()
{
	delete textMan;
	textMan = nullptr;
}
sf::Vector2f CollisionHandling::GetWorldToTileCoords(sf::Vector2f pos)
{
	std::cout << "TIleSIze COllision " << tileSize << std::endl;
	tileSize = textMan->GetTileSize();
	float tileX = pos.x / tileSize;
	float tileY = pos.y / tileSize;
	//maybe round up number
	std::cout << "Tile X = " << tileX << " Tile Y = " << tileY << " tileSize "<< tileSize << std::endl;
	return sf::Vector2f(tileX, tileY);

}
sf::Vector2f CollisionHandling::PlayerCollisionDetection(char pressed, sf::Vector2f playerPos, sf::Vector2f playerVel)
{
	sf::Vector2f tilePos = GetWorldToTileCoords(playerPos);//player position in tile coordinates
	if (pressed == 'r')
	{
		//if tilePosX not whole number eg 1.7 - 1.0 ==0.7 
		if (tilePos.x - floor(tilePos.x) > 0.0f)
		{
			std::cout << "If tilePosx not whole number\n";
			//get 2 tiles affected
			
			//check if walkable
		}
		else
		{
			std::cout << " tilePosx is whole number\n";
		}
			
	}
	if (pressed == 'l')
	{
	}
	if (pressed == 'u')
	{
	}
	if (pressed == 'd')
	{
	}
	return sf::Vector2f(0, 0);
}
