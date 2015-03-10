#pragma once
#include <SFML\Graphics.hpp>
class Bar
{
public:
	Bar();
	Bar(sf::Vector2f pos,sf::Vector2f size, sf::Color colour);
	~Bar();
	void Update();
	void Draw(sf::RenderWindow *rw);
	
	sf::Vector2f GetPosition(){ return this->position; }
	sf::Vector2f GetSize(){ return this->size; }
	float GetScale(){ return this->scale; }

	void SetColour(sf::Color c){ this->colour = c; }
	void SetScale(float scale){ this->scale = scale; }
private:
	sf::RectangleShape insideRect;
	sf::RectangleShape outlineRect;
	sf::Vector2f position;
	sf::Vector2f size;
	float scale;
	sf::Color colour;
};

