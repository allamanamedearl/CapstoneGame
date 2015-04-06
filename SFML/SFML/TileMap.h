#pragma once
#include <vector>
#include "LightEngine.h"
#include "Tile.h"
#include "TextureManager.h"
class TileMap
{
private:
	//a 2D vector/array of Tile pointers
	std::vector<std::vector<Tile*>> map;

	//width and height of level in tiles
	int w;
	int h;

	struct NPC_ATTRIBUTES
	{
		std::string behaviour;//needs to be capitalized eg. Idle Patrol
		sf::Vector2f startPos;//start position in tile coords
		sf::Vector2f endPos;
		//may need one for picture type
	};
	
	void SetDimensions(int w, int h);
public:
	TileMap(int w, int h);
	~TileMap();
	
	void AddTile(int x, int y, Tile* tile);
	Tile* GetTile(int x, int y);

	void LoadLevel(std::string filename, TextureManager& textureMan);
	void LoadLightMap(std::string filename, LightEngine& lightEngine, int tileSize);

	int GetWidth();
	int GetHeight();
	std::vector<NPC_ATTRIBUTES> npcs;
};

