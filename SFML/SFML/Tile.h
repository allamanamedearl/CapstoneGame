#pragma once
#include <SFML\Graphics.hpp>
class Tile
{
private:
	sf::Sprite baseSprite;
	sf::Texture tileCleared;//for when a breakable tile is destroyed
	bool walkable;
	bool breakable;
public:
	Tile(sf::Texture* texture, bool walkable, bool breakable);
	~Tile();
	void SetTileClearedTexture(sf::Texture texture){ this->tileCleared = texture; };
	void ReplaceTexture(){ this->baseSprite.setTexture(this->tileCleared,true); }//replaces current tile eg. cracked wall with floor tile
	bool CheckIfWalkable(){ return this->walkable; }
	bool CheckIfBreakable(){ return this->breakable; }
	void SetWalkable(bool walkable){ this->walkable = walkable; }
	void Draw(int x, int y, sf::RenderWindow* rw);
};

