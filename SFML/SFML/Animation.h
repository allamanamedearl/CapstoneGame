#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System\Time.hpp>
#include <SFML\System\Clock.hpp>
class Animation
{
private:
	std::vector<sf::Sprite*> frames;
	bool left;
	bool right;
	bool up;
	bool down;
	bool pause;

	bool triggerMadness;
	bool psychoticRage;
	bool controlNPC;

	int currentFrame;
	sf::Texture spriteSheet;
	sf::Time time;
	sf::Clock clock;
	//sf::Vector2f tileSize;
	//int row;
	//int column;
public:
	Animation();
	~Animation();
	void SetFrames(sf::Texture sheet, int sizeX,int sizeY, int width, int height);
	void Left();
	void Right();
	void Up();
	void Down();
	void Pause();

	void Madness();
	void Control();
	void Rage();

	void SetPosition(sf::Vector2f pos);
	void Update();
	sf::Sprite* GetCurrentFrame();
};

