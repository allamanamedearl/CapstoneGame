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
		//adding npcs to map based on tile pos
		std::string npcString = tile->first_attribute("npc")->value();
		
		NPC_ATTRIBUTES attrib;
		if (npcString == "Idle")
		{
			attrib.behaviour = "Idle";
			attrib.startPos = sf::Vector2f(x, y);
			attrib.endPos = sf::Vector2f(x, y);
			npcs.push_back(attrib);
		}
		else if (npcString == "Patrol")
		{
			attrib.behaviour = "Patrol";
			attrib.startPos = sf::Vector2f(x, y);
			int endX = atoi(tile->first_attribute("endX")->value());
			int endY = atoi(tile->first_attribute("endY")->value());
			attrib.endPos = sf::Vector2f(endX, endY);
			npcs.push_back(attrib);
		}
		else if (npcString == "Pursue")
		{
			attrib.behaviour = "Pursue";
			attrib.startPos = sf::Vector2f(x, y);
			attrib.endPos = sf::Vector2f(x, y);
			npcs.push_back(attrib);
		}
		else if (npcString == "Guard")
		{
			attrib.behaviour = "Guard";
			attrib.startPos = sf::Vector2f(x, y);
			attrib.endPos = sf::Vector2f(x, y);
			npcs.push_back(attrib);
		}
		//is it breakable?
		std::string breakString = tile->first_attribute("breakable")->value();
		bool isBreakable = (breakString == "true") ? true : false;
		
		//create the tile and add it to the level
		Tile* newTile = new Tile(textureMan.GetTexture(baseid),isWalkable,isBreakable);
		if (breakString == "true")
		{
			//set ClearedTIle
			newTile->SetTileClearedTexture(*textureMan.GetTexture(0));//0 is floor tile
		}

		AddTile(x, y, newTile);
		
		//go to next tile
		tile = tile->next_sibling("tile");
	}
}
void TileMap::LoadLightMap(std::string filename, LightEngine& lightEngine, int tileSize)
{
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

	//go through each light
	rapidxml::xml_node<>* light = root->first_node("light");
	while (light)
	{
		//get all the attributes
		int x = atoi(light->first_attribute("x")->value());
		int y = atoi(light->first_attribute("y")->value());
		int radius = atoi(light->first_attribute("radius")->value());//length
		int arcSize = atoi(light->first_attribute("arc_size")->value());//angle spread
		int direction = atoi(light->first_attribute("angle")->value());//which direction it points in an angle 0 = right

		//std::string walkString = tile->first_attribute("walkable")->value();
		//bool isWalkable = (walkString == "true") ? true : false;//ternery yay! Phil would be proud
		//adding npcs to map based on tile pos
		//std::string npcString = tile->first_attribute("npc")->value();

		Light tmpLight;
		tmpLight.angle = direction;
		tmpLight.angleSpread = arcSize;
		tmpLight.radius = radius;
		//tmpLight.colour = sf::Color::Transparent;//for now
		tmpLight.position = sf::Vector2f((float)x*tileSize, (float)y*tileSize);
		tmpLight.dynamic = true;
		lightEngine.Lights.push_back(tmpLight);

		//go to next tile
		light = light->next_sibling("light");
	}
	//add blocks
	for (int y = 0; y < GetHeight(); y++)
	{
		for (int x = 0; x < GetWidth(); x++)
		{
			if (!GetTile(x,y)->CheckIfWalkable())
			{
				Block block;
				block.fRect = sf::FloatRect(float(x*tileSize), float(y*tileSize), float(tileSize), float(tileSize));
				block.allowBlock = true;
				lightEngine.Blocks.push_back(block);
			}
		}
	}
	
}
