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
void TileMap::LoadLevel(std::string filename, TextureManager& textureMan)
{
	//loads level from xml
	//load the file
	std::ifstream inFile(filename);

	if (!inFile)
		throw "Could not load level " + filename;
	//Dump contents of file into a string
	std::string xmlContents;

	std::string line;
	while (std::getline(inFile, line))
		xmlContents += line;
	//convert string to rapidxml readable char
	std::vector<char> xmlData = std::vector<char>(xmlContents.begin(), xmlContents.end());
	xmlData.push_back('\0');

	//create a parsed document
	rapidxml::xml_document<> doc;
	doc.parse<rapidxml::parse_no_data_nodes>(&xmlData[0]);

	//get root node
	rapidxml::xml_node<>* root = doc.first_node();

	//get level attributes
	int width = atoi(root->first_attribute("width")->value());
	int height = atoi(root->first_attribute("height")->value());

	//resize level yay
	this->w = width;
	this->h = height;
	SetDimensions(width, height);

	//load each necessary tileset
	rapidxml::xml_node<>* tileset = root->first_node("tileset");
	while (tileset)
	{
		std::string path = tileset->first_attribute("path")->value();
		//load tileset
		textureMan.LoadTileset(path);
		//go to next tileset
		tileset = tileset->next_sibling("tileset");
	}

	//go through each tile
	rapidxml::xml_node<>* tile = root->first_node("tile");
	while (tile)
	{
		//get all the attributes
		int x = atoi(tile->first_attribute("x")->value());
		int y = atoi(tile->first_attribute("y")->value());
		int baseid = atoi(tile->first_attribute("baseid")->value());

		std::string walkString = tile->first_attribute("walkable")->value();
		bool isWalkable = (walkString == "true") ? true : false;//ternery yay! Phil would be proud

		//create the tile and add it to the level
		Tile* newTile = new Tile(textureMan.GetTexture(baseid));
		AddTile(x, y, newTile);
		
		//go to next tile
		tile = tile->next_sibling("tile");
	}
}
