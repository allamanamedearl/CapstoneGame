#include "Bar.h"

Bar::Bar()
{
	position = sf::Vector2f(0, 0);
	size = sf::Vector2f(10.0f, 10.0f);
	colour = sf::Color::Black;
}
Bar::Bar(sf::Vector2f pos, sf::Vector2f size, sf::Color colour)
{
	this->position = pos;
	this->size = size;
	this->colour = colour;
	scale = 1.0f;
	insideRect.setPosition(this->position);
	insideRect.setSize(this->size);
	insideRect.setFillColor(colour);
	//insideRect.setOutlineColor(colour);
	//5.0f will be outline thickness
	outlineRect.setPosition(pos.x-2.5f,pos.y-2.5f);//sf::Vector2f(pos.x + 5.0f, pos.y + 5.0f));
	outlineRect.setSize(sf::Vector2f(size.x + 5.0f, size.y + 5.0f));
	outlineRect.setFillColor(sf::Color::Black);
	//outlineRect.setOutlineThickness(0.0f);
	//insideRect.setOutlineColor(colour);
	insideRect.setOrigin(insideRect.getSize().x / 2, insideRect.getSize().y); //sets origin to middle of bottom?sure...it works
	insideRect.setPosition(sf::Vector2f(pos.x + insideRect.getSize().x / 2, pos.y + insideRect.getSize().y));
	//insideRect.setRotation(180);
}


Bar::~Bar()
{
}
void Bar::Update()
{
	//  _
	// | | x=10 y=10
	// | |
	// |_|
	
	insideRect.setScale(sf::Vector2f(1.0f, scale));
}
void Bar::Draw(sf::RenderWindow *rw)
{
	rw->draw(outlineRect);
	rw->draw(insideRect);
}
