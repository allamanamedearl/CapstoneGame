#include "Light.h"


Light::Light()
{
	colour = sf::Color(255, 255, 255,200);//white
	radius = 0;
	angleSpread = 0;
	position = sf::Vector2f(0.0f, 0.0f);
	angle = 0;
	dynamic = true;
	getsBlocked = false;
	blockAngle = 0.0f;
}


Light::~Light()
{
}
