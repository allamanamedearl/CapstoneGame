#pragma once
#include <SFML\Graphics.hpp>
#include "Tile.h"
class Camera
{
private:
	//absolute position of camera
	//(number of pixels grom origin of level map
	sf::Vector2f position;
	//target position camera is moving towards
	sf::Vector2f target;
	//size of camera
	sf::Vector2i size;
	//speed of camera, a value between 0.0 and 1.0
	float speed;
public:
	Camera(int w, int h, float speed);
	~Camera();
	//moves camera immediately to coordinates
	void Move(int x, int y);
	void MoveCenter(int x, int y);

	//sets camera target
	void GoTo(int x, int y);
	void GoToCenter(int x, int y);

	//updates camera position
	void Update();

	inline sf::Vector2i GetPosition()
	{
		return sf::Vector2i((int)position.x, (int)position.y);
	}
	//helper function for retrieving camera's
	//offset from nearest tile
	inline sf::Vector2i GetTileOffset(int tileSize)
	{
		return sf::Vector2i((int)(position.x) % tileSize, (int)(position.y) % tileSize);
	}
	//helper function for retrieving
	//a rectangle defining which tiles
	//are visible through camera
	sf::IntRect GetTileBounds(int tileSize);
};

