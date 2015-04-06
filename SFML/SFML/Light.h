#pragma once
#include<SFML\Graphics\Color.hpp>
#include<SFML\System\Vector2.hpp>
class Light
{
public:
	Light();

	~Light();
	sf::Vector2f position;
	sf::Color colour;
	float radius;//how far light will shine to
	float angleSpread;//spread of light creating an arc
	float angle;//where the light's pointing at
	bool dynamic;
};

