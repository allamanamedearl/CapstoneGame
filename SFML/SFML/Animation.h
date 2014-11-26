#pragma once
#include <SFML\Graphics.hpp>
class Animation
{
private:
	std::vector<sf::Sprite*> frames;
	bool left;
	bool right;
	bool up;
	bool down;
	int currentFrame;
	//sf::Vector2f tileSize;
	//int row;
	//int column;
public:
	Animation();
	~Animation();
	void SetFrames(sf::Texture *sheet, int sizeX,int sizeY, int row, int column);
	void Left();
	void Right();
	void Up();
	void Down();
	void SetPosition(sf::Vector2f pos);
	void Update();
	sf::Sprite* GetCurrentFrame();
};

