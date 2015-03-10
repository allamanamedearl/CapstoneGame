#pragma once
#include <SFML\Graphics.hpp>
#include "Bar.h"
class Gui
{
public:
	Gui(sf::Texture *texture, int screenWidth, int screenHeight);
	~Gui();
	void Init();
	void Update();
	void Draw(sf::RenderWindow *window);

	sf::Sprite background;
	sf::View guiView;

	sf::Vector2f GetPosition(){ return this->position; }
	void SetPosition(sf::Vector2f pos){ this->position = pos; }

	void SetHintMad(bool isMad){ this->hintMad = isMad; }
	void SetHintControl(bool isControl){ this->hintControl = isControl; }
	void SetHintAnger(bool isAnger){ this->hintAnger = isAnger; }
private:
	//bools to set whether to highlight powers to use
	//if true will draw a highlight behind key symbol
	bool hintMad;
	bool hintControl;
	bool hintAnger;
	sf::Vector2f position;
	int screenWidth;
	int screenHeight;
	Bar madBar;//madness
	Bar rageBar;
	Bar controlBar;
	
};

