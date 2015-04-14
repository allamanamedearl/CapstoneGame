#pragma once
//#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "rapidxml.hpp"
class Dialogue
{
private:
	std::string source;
	sf::Texture background;
	sf::Font font;
	sf::Text text;
	sf::RectangleShape rectangle;
public:
	Dialogue();
	Dialogue(std::string source, sf::Vector2f pos);
	~Dialogue();
	void LoadDialogue(int id);
	void RenderDialogue(sf::RenderWindow* window);
};

