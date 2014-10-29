#include "TileMap.h"


TileMap::TileMap(int w, int h)
{
	SetDimensions(w, h);
	this->w = w;
	this->h = h;
}


TileMap::~TileMap()
{
}

int TileMap::GetHeight()
{
	return h;
}
int TileMap::GetWidth()
{
	return w;
}
void TileMap::SetDimensions(int w, int h)
{
	//w - row width (num of columns)
	map.resize(w);

	//height of map (num of rows
	for (int i = 0; i < w; i++)
	{
		//map at i column resize to h height initial value is 0
		map.at(i).resize(h, 0);
	}
}
void TileMap::AddTile(int x, int y, Tile* tile)
{
	map[x][y] = tile;
}
Tile* TileMap::GetTile(int x, int y)
{
	return map[x][y];
}
