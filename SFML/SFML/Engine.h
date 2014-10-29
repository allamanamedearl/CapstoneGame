#ifndef ENGINE_H
#define ENGINE_H

#include <SFML\Graphics.hpp>
#include "TextureManager.h"
#include "TileMap.h"
#include "Camera.h"
class Engine
{
private:
	//testing stuff
	TextureManager* textureManager;
	sf::Texture sprite;
	void LoadTextures();
	void LoadLevel();
	Tile* testTile;
	bool keyDown;
	//SFML Render Window
	sf::RenderWindow* window;

	//camera
	Camera* camera;
	//map
	TileMap* currLevel;
	int tileSize;

	//initializes the engine
	bool Init();
	//main game loop
	void MainLoop();
	//Renders One Frame
	void RenderFrame();
	//processes user input
	void ProcessInput();
	//Updates all engine internals
	void Update();
public:
	Engine();
	~Engine();

	void Start();//starts engine
};
#endif