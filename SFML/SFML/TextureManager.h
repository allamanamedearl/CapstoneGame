#include <SFML\Graphics.hpp>
#include <vector>
#include <fstream>
#include "rapidxml.hpp"

class TextureManager
{
private:
	 std::vector <sf::Texture> textureList;
	 std::map<int, int> imageIDs;

	 int tileSize;//another tileSize in engine.h
public:
	TextureManager();
	~TextureManager();
	
	void AddTexture(sf::Texture& image,int id);
	sf::Texture* GetTexture(int id);
	void SetTileSize(int tileSize){ this->tileSize = tileSize; }
	int GetTileSize(){ return this->tileSize; }
	//load tileset from xml 
	void LoadTileset(std::string file);
};