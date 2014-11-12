#pragma once
#include <SFML\Graphics.hpp>
class Tile
{
private:
	sf::Sprite baseSprite;
	bool walkable;
public:
	Tile(sf::Texture* texture, bool walkable);
	~Tile();
	bool CheckIfWalkable(){ return this->walkable; }
	void Draw(int x, int y, sf::RenderWindow* rw);
};

