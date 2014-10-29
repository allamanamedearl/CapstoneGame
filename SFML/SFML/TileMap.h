#pragma once
#include <vector>
#include "Tile.h"
class TileMap
{
private:
	//a 2D vector/array of Tile pointers
	std::vector<std::vector<Tile*>> map;

	//width and height of level in tiles
	int w;
	int h;

	void SetDimensions(int w, int h);
public:
	TileMap(int w, int h);
	~TileMap();

	void AddTile(int x, int y, Tile* tile);
	Tile* GetTile(int x, int y);

	void LoadLevel();

	int GetWidth();
	int GetHeight();
};

