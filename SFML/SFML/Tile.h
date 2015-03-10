#pragma once
#include <SFML\Graphics.hpp>
class Tile
{
private:
	sf::Sprite baseSprite;
	bool walkable;
	bool breakable;
public:
	Tile(sf::Texture* texture, bool walkable, bool breakable);
	~Tile();
	bool CheckIfWalkable(){ return this->walkable; }
	bool CheckIfBreakable(){ return this->breakable; }
	void SetWalkable(bool walkable){ this->walkable = walkable; }
	void Draw(int x, int y, sf::RenderWindow* rw);
};

