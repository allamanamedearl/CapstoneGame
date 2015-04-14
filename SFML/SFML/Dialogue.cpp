#include "Dialogue.h"


Dialogue::Dialogue()
{
	rectangle.setPosition(sf::Vector2f(0.0f, 500.0f));
	rectangle.setFillColor(sf::Color(255, 255, 255, 100));
	rectangle.setSize(sf::Vector2f(780.0f, 80.0f));
	font.loadFromFile("C:/Windows/Fonts/OLDENGL.ttf");
	rectangle.setOutlineThickness(10.0f);
	rectangle.setOutlineColor(sf::Color::Black);
	text.setCharacterSize(18);
	text.setColor(sf::Color::Black);
	text.setPosition(0.0f, 510.0f);
	text.setFont(font);
	//text.setStyle(sf::Text::Bold);
	
}

Dialogue::Dialogue(std::string source,sf::Vector2f pos)
{
	this->source = source;
	rectangle.setSize(sf::Vector2f(780.0f, 80.0f));
	rectangle.setPosition(pos);
	rectangle.setFillColor(sf::Color(255, 255, 255, 200));
	rectangle.setOutlineThickness(10.0f);
	rectangle.setOutlineColor(sf::Color::Black);
	
	if (!font.loadFromFile("C:/Windows/Fonts/OLDENGL.ttf"))
	{
		std::exit(EXIT_FAILURE);
	}
	text.setCharacterSize(18);
	//text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Black);
	text.setPosition(pos.x + 5.0f, pos.y + 10.0f);
	text.setFont(font);
	
}
Dialogue::~Dialogue()
{
}
void Dialogue::LoadDialogue(int id)
{
	std::string dialogue;
	std::ifstream inFile(this->source);

	if (!inFile)
		throw "Could not load level " + source;
	//Dump contents of file into a string
	std::string xmlContents;

	std::string line;
	
	while (std::getline(inFile, line))
		xmlContents += line;
	//convert string to rapidxml readable char
	std::vector<char> xmlData = std::vector<char>(xmlContents.begin(), xmlContents.end());
	xmlData.push_back('\0');

	//create a parsed document
	rapidxml::xml_document<> doc;
	doc.parse<rapidxml::parse_no_data_nodes>(&xmlData[0]);

	//get root node
	rapidxml::xml_node<>* root = doc.first_node();

	//go through each light
	rapidxml::xml_node<>* character = root->first_node("character");
	while (character)
	{
		int currId = atoi(character->first_attribute("id")->value());
		if (currId != id)//if id doesn't match go to next character
		{
			character = character->next_sibling("character");
		}
		else
		{
			rapidxml::xml_node<>* words = character->first_node("dialogue");
			dialogue = words->first_attribute("text")->value();
			break;
		}
	}
	
	//std::string dialogue = character->first_attribute("dialogue")->value();

	text.setString(dialogue);
	//return dialogue;
	
}
void Dialogue::RenderDialogue(sf::RenderWindow* window)
{
	//text.setString(dialogue);
	window->draw(rectangle);
	window->draw(text);
	
}
