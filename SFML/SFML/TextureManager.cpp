#include "TextureManager.h"

TextureManager::TextureManager()
{

}
TextureManager::~TextureManager()
{

}
void TextureManager::AddTexture(sf::Texture& image, int id)
{
	textureList.push_back(image);
	//map for pairing image ids and the image's index in textureList
	imageIDs[id] = textureList.size() - 1;
}
sf::Texture* TextureManager::GetTexture(int id)
{
	return &textureList[imageIDs[id]];
}
void TextureManager::LoadTileset(std::string file)//just for loading specific tile Images
{
	//load the file
	std::ifstream inFile(file);

	//checks to see if it loaded
	if (!inFile)
		throw "Coud not load tileset: " + file;
	//contents of the file in string
	std::string xmlContents;
	
	std::string line;
	//extracts a line from inFile and stores them in line
	//adds line to xmlContents
	while (std::getline(inFile, line))
		xmlContents += line;

	//convert string to rapidxml readable char
	std::vector<char>xmlData = std::vector<char>(xmlContents.begin(), xmlContents.end());
	xmlData.push_back('\0');//end of file

	//create a parse document with &xmlData[0] which is the char
	rapidxml::xml_document<> doc;
	//to parse file need to pass pointer to the beginning char
	doc.parse<rapidxml::parse_no_data_nodes>(&xmlData[0]);

	//get the root node
	rapidxml::xml_node<>* root = doc.first_node();

	std::string imagePath;
	sf::Texture tileSet;
	//go through each imageFile
	rapidxml::xml_node<>* imageFile = root->first_node("imagefile");
	while (imageFile)
	{
		//get the image file that's being parsed and load it
		imagePath = imageFile->first_attribute("path")->value();
		//tileSet.loadFromFile(imagePath);

		//go through each tile
		rapidxml::xml_node<>* tile = imageFile->first_node("tile");
		while (tile)
		{
			//get all the attributes of tile
			int x = atoi(tile->first_attribute("x")->value());
			int y = atoi(tile->first_attribute("y")->value());
			int id = atoi(tile->first_attribute("id")->value());
			
			//load from file
			//sf::Texture tileImage;
			tileSet.loadFromFile(imagePath, sf::IntRect(x*tileSize, y*tileSize, tileSize, tileSize));
			AddTexture(tileSet,id);

			//go to next tile
			tile = tile->next_sibling();
		}
	}
}