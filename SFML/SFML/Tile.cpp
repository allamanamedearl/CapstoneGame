#include "Tile.h"


Tile::Tile(sf::Texture* texture, bool walkable, bool breakable)
{
	baseSprite.setTexture(*texture, true);
	this->walkable = walkable;
	this->breakable = breakable;
}


Tile::~Tile()
{
}
void Tile::Draw(int x, int y, sf::RenderWindow* rw)
{
	baseSprite.setPosition(x, y);
	rw->draw(baseSprite);
}
