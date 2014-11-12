#include "Tile.h"


Tile::Tile(sf::Texture* texture, bool walkable)
{
	baseSprite.setTexture(*texture, true);
	this->walkable = walkable;
}


Tile::~Tile()
{
}
void Tile::Draw(int x, int y, sf::RenderWindow* rw)
{
	baseSprite.setPosition(x, y);
	rw->draw(baseSprite);
}
