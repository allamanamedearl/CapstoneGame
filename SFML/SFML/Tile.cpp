#include "Tile.h"


Tile::Tile(sf::Texture* texture)
{
	baseSprite.setTexture(*texture, true);
}


Tile::~Tile()
{
}
void Tile::Draw(int x, int y, sf::RenderWindow* rw)
{
	baseSprite.setPosition(x, y);
	rw->draw(baseSprite);
}
