#pragma once
#include<SFML\Graphics\Rect.hpp>
class Block
{
public:
	Block();
	~Block();
	sf::FloatRect fRect;//area blocking light
	bool allowBlock;//keep a block but don't block until certain point
};

