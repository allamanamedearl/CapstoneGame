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
bool CollisionHandling::CheckIfTile(sf::Vector2f pos)
{
	if (pos.x <0 || pos.x>tileMap->GetWidth() || pos.y <0 || pos.y>tileMap->GetHeight())
	{
		return false; //no there's NOT a tile there
	}
	else
	{
		return true;
	}
}
sf::Vector2f CollisionHandling::GetWorldToTileCoords(sf::Vector2f pos)
{
	//std::cout << "TIleSIze COllision " << tileSize << std::endl;
	tileSize = textMan->GetTileSize();
	float tileX = pos.x / tileSize;
	float tileY = pos.y / tileSize;
	//maybe round up number
	//std::cout << "Tile X = " << tileX << " Tile Y = " << tileY << " tileSize "<< tileSize << std::endl;
	return sf::Vector2f(tileX, tileY);

}
sf::Vector2f CollisionHandling::GetTileToWorldCoords(sf::Vector2f pos)
{
	tileSize = textMan->GetTileSize();
	float tileX = pos.x *tileSize;
	float tileY = pos.y *tileSize;
	return sf::Vector2f(tileX, tileY);
}
bool CollisionHandling::PlayerCollisionDetection(char pressed, sf::Vector2f playerPos, sf::Vector2f playerVel)
{
	//sf::Vector2f tilePos = GetWorldToTileCoords(playerPos);//player position in tile coordinates
	//if (pressed == 'r')
	//{
	//	if (tilePos.x < 0)
	//	{
	//		tilePos.x = 0;
	//	}
	//	if (tilePos.y < 0)
	//	{
	//		tilePos.y = 0;
	//	}
	//	if (tilePos.x > tileMap->GetWidth()* tileSize)
	//	{
	//		tilePos.x = tileMap->GetWidth()* tileSize;
	//	}
	//	if (tilePos.y > tileMap->GetHeight()* tileSize)
	//	{
	//		tilePos.y = tileMap->GetHeight()* tileSize;
	//	}

	//	//if tilePosy not whole number eg 1.7 - 1.0 ==0.7 means you're colliding with 2 tiles
	//	if (tilePos.y - floor(tilePos.y) > 0.0f)
	//	{
	//		std::cout << "If tilePosY not whole number - for pressing r\n";
	//		//get 2 tiles affected
	//		//check if walkable
	//		//checks if tile to top right and bottom right is walkable
	//		if (tileMap->GetTile((int)ceilf(tilePos.x), (int)floorf(tilePos.y))->CheckIfWalkable() == false ||
	//			tileMap->GetTile((int)ceilf(tilePos.x), (int)ceilf(tilePos.y))->CheckIfWalkable() == false)
	//		{
	//			return sf::Vector2f(-0.2f, playerVel.y);
	//		}
	//	}
	//	else
	//	{
	//		std::cout << " tilePosx is whole number\n";
	//	}
	//		
	//}
	//if (pressed == 'l')
	//{
	//	if (tilePos.x < 0)
	//	{
	//		tilePos.x = 0;
	//	}
	//	if (tilePos.y < 0)
	//	{
	//		tilePos.y = 0;
	//	}
	//	if (tilePos.x > tileMap->GetWidth()* tileSize)
	//	{
	//		tilePos.x = tileMap->GetWidth()* tileSize;
	//	}
	//	if (tilePos.y > tileMap->GetHeight()* tileSize)
	//	{
	//		tilePos.y = tileMap->GetHeight()* tileSize;
	//	}
	//	//if tilePosy not whole number eg 1.7 - 1.0 ==0.7 means you're colliding with 2 tiles
	//	if (tilePos.y - floor(tilePos.y) > 0.0f)
	//	{
	//		std::cout << "If tilePosY not whole number - for pressing r\n";
	//		//get 2 tiles affected
	//		//check if walkable
	//		//checks if tile to top left and bottom left is walkable
	//		if (tileMap->GetTile((int)floorf(tilePos.x), (int)floorf(tilePos.y))->CheckIfWalkable() == false ||
	//			tileMap->GetTile((int)floorf(tilePos.x), (int)ceilf(tilePos.y))->CheckIfWalkable() == false)
	//		{
	//			return sf::Vector2f(0.2f, playerVel.y);
	//		}
	//	}
	//	else
	//	{
	//		std::cout << " tilePosx is whole number\n";
	//	}
	//}
	//if (pressed == 'u')
	//{
	//	if (tilePos.x < 0)
	//	{
	//		tilePos.x = 0;
	//	}
	//	if (tilePos.y < 0)
	//	{
	//		tilePos.y = 0;
	//	}
	//	if (tilePos.x > tileMap->GetWidth()* tileSize)
	//	{
	//		tilePos.x = tileMap->GetWidth()* tileSize;
	//	}
	//	if (tilePos.y > tileMap->GetHeight()* tileSize)
	//	{
	//		tilePos.y = tileMap->GetHeight()* tileSize;
	//	}
	//	//if tilePosy not whole number eg 1.7 - 1.0 ==0.7 means you're colliding with 2 tiles
	//	if (tilePos.x - floor(tilePos.x) > 0.0f)
	//	{
	//		std::cout << "If tilePosY not whole number - for pressing r\n";
	//		//get 2 tiles affected
	//		//check if walkable
	//		//checks if tile to top left and top right is walkable
	//		if (tileMap->GetTile((int)floorf(tilePos.x), (int)floorf(tilePos.y))->CheckIfWalkable() == false ||
	//			tileMap->GetTile((int)ceilf(tilePos.x), (int)floorf(tilePos.y))->CheckIfWalkable() == false)
	//		{
	//			return sf::Vector2f(playerVel.x, 0.2f);
	//		}
	//	}
	//	else
	//	{
	//		std::cout << " tilePosx is whole number\n";
	//	}
	//}
	//if (pressed == 'd')
	//{
	//	if (tilePos.x < 0)
	//	{
	//		tilePos.x = 0;
	//	}
	//	if (tilePos.y < 0)
	//	{
	//		tilePos.y = 0;
	//	}
	//	if (tilePos.x > tileMap->GetWidth()* tileSize)
	//	{
	//		tilePos.x = tileMap->GetWidth()* tileSize;
	//	}
	//	if (tilePos.y > tileMap->GetHeight() * tileSize)
	//	{
	//		tilePos.y = tileMap->GetHeight() * tileSize;
	//	}
	//	//if tilePosy not whole number eg 1.7 - 1.0 ==0.7 means you're colliding with 2 tiles
	//	if (tilePos.x - floor(tilePos.x) > 0.0f)
	//	{
	//		std::cout << "If tilePosY not whole number - for pressing r\n";
	//		//get 2 tiles affected
	//		//check if walkable
	//		//checks if tile to top left and top right is walkable
	//		if (tileMap->GetTile((int)floorf(tilePos.x), (int)ceilf(tilePos.y))->CheckIfWalkable() == false ||
	//			tileMap->GetTile((int)ceilf(tilePos.x), (int)ceilf(tilePos.y))->CheckIfWalkable() == false)
	//		{
	//			return sf::Vector2f(playerVel.x, -0.2f);
	//		}
	//	}
	//	else
	//	{
	//		std::cout << " tilePosx is whole number\n";
	//	}
	//}
	//return playerVel;

	sf::Vector2f tilePos = GetWorldToTileCoords(playerPos);
	
	if (pressed == 'r')
	{
		if (tilePos.x >= tileMap->GetWidth()-1)
		{
			return false;
		}
		
		else
		{
			return tileMap->GetTile((int)tilePos.x + 1, (int)tilePos.y)->CheckIfWalkable();
		}
		
	
	}
	if (pressed == 'l')
	{
		if (tilePos.x -1 < 0)
		{
			return false;
		}
		else
		{
			return tileMap->GetTile((int)tilePos.x - 1, (int)tilePos.y)->CheckIfWalkable();
		}
		
	}
	if (pressed == 'u')
	{
		
		if (tilePos.y -1 < 0)
		{
			return false;
		}
		else
		{
			return tileMap->GetTile((int)tilePos.x, (int)tilePos.y - 1)->CheckIfWalkable();
		}
	}
	if (pressed == 'd')
	{
		if (tilePos.y >= tileMap->GetHeight()-1)
		{
			std::cout << "Tilemap height : " << tileMap->GetHeight() << std::endl;
			return false;
		}
		else
		{
			return tileMap->GetTile((int)tilePos.x, (int)tilePos.y + 1)->CheckIfWalkable();
		}
		
	}
}
