#include "Engine.h"
#include <iostream>
#include <Windows.h>
int num = 0;
Engine::Engine()
{
	tileSize = 32;
	camera = new Camera(720, 640, 0.2f);
	keyDown = false;
	timeSinceLastUpdate = 0;
}
Engine::~Engine()
{
	delete window;
	window = nullptr;
	delete textureManager;
	textureManager = nullptr;
	delete camera;
	camera = nullptr;
	delete currLevel;
	currLevel = nullptr;
	delete collisionHandling;
	collisionHandling = nullptr;
}
void Engine::LoadTextures()
{
	
	//OLD WAY TO LOAD TILES
	/*sprite.loadFromFile("tileset.png",sf::IntRect(0,0,32,32));//loads top left square
	textureManager->AddTexture(sprite,0);
	sprite.loadFromFile("C:/Users/Cassie/Desktop/School Stuff/Assets/tileset.png", sf::IntRect(32, 0, 32, 32));
	textureManager->AddTexture(sprite,1);
	testTile = new Tile(textureManager->GetTexture(0));*/
	//OLD TEST SPRITE
	//playerTexture.loadFromFile("C:/Users/Cassie/Pictures/race_car.jpg");
	
	if (!playerTexture.loadFromFile("C:/Users/Cassie/Desktop/School Stuff/Capstone/CapstoneGit/SFML/SFML/blondeSprite.png"))
	{
		std::cout << "Unable to load player texture";
		std::exit;
	}
	textureManager->SetTileSize(tileSize);
	std::cout << "LOAD TEXTURES" << std::endl;
	//FOR TESTING LOADING TILESET FROM XML
	/*try{
		textureManager->LoadTileset("tileset.xml");
	}
	catch(std::string msg){
		std::cout << "Failed to load.  Caught any exception." << std::endl;
	}
	*/
	
}
bool Engine::Init()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "RPG");
	textureManager = new TextureManager();
	LoadTextures();
	//for testing
	LoadLevel();
	std::cout << "\nAfter LoadLevel() call" << std::endl;
	collisionHandling = new CollisionHandling(textureManager, currLevel);
	player = new Player(&playerTexture,collisionHandling);
	if (!window)
		return false;
	return true;
}
void Engine::LoadLevel()
{
	//OLD WAY TESTING
	/*int numTiles = 40;
	currLevel = new TileMap(numTiles,numTiles);
	Tile* tile;
	for (int y = 0; y < numTiles; y++)
	{
		for (int x = 0; x < numTiles; x++)
		{
			//every 4th row will be the dirt tile
			if (y % 4 == 0)
			{
				tile = new Tile(textureManager->GetTexture(1));
			}
			else
			{
				tile = new Tile(textureManager->GetTexture(0));
			}
			currLevel->AddTile(x, y, tile);
		}
	}*/

	std::cout << "LOADING LEVEL" << std::endl;
	currLevel = new TileMap(20, 20);//values don't matter, going to be changed in load level
	currLevel->LoadLevel("level.xml", *textureManager);

	//initialize collisionHandling
	//collisionHandling = new CollisionHandling();
}
void Engine::RenderFrame()
{
	int camOffsetX, camOffsetY;
	Tile* tile;
	window->clear();
	//get the tile bounds needed to draw and camera bounds
	sf::IntRect bounds = camera->GetTileBounds(tileSize);
	//how much to offset each tile
	camOffsetX = camera->GetTileOffset(tileSize).x;
	camOffsetY = camera->GetTileOffset(tileSize).y;

	//so we don't get a vector out of bounds error
	if (bounds.width > currLevel->GetWidth())
	{
		bounds.width = currLevel->GetWidth();
	}
	if (bounds.height > currLevel->GetHeight())
	{
		bounds.height = currLevel->GetHeight();
	}
	//loop and draw each tile
	//keeping track of two variables in each loop. How many tiles
	//drawn (x and y), and which tile on the map is being drawn (tileX
	//and tileY)
	//bounds.top = y coordinate of rect
	for (int y = 0, tileY = bounds.top; y < bounds.height; y++, tileY++)
	{
		for (int x = 0, tileX = bounds.left; x < bounds.width; x++, tileX++)
		{
			if (tileY >= 0 && tileX >= 0)
			{

				//Get the tile we're drawing
				tile = currLevel->GetTile(tileX, tileY);

				if (tile)
					tile->Draw((x * tileSize), (y * tileSize), window);
			}
		}
	}
	//window->draw(sprite);
	//testTile->Draw(10, 10, window);
	player->Draw(window);
	window->display();
}
void Engine::ProcessInput()
{
	sf::Event evt;
	if (num >= 1000)
	{
		std::cout << "Player Pos = " << player->GetPosition().x << " " << player->GetPosition().y << std::endl;
		//collisionHandling->GetWorldToTileCoords(player->GetPosition());
		num = 0;
	}
	num++;
	player->GetInput();
	//loop through all window events
	while (window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed)
			window->close();
		if (evt.type == sf::Event::KeyPressed && keyDown ==false)
		{
			/*int x = camera->GetPosition().x;
			int y = camera->GetPosition().y + 1;
			camera->GoToCenter(x, y);*/
			//player->GetInput();
			keyDown = true;
			std::cout << "KeyPressed" << std::endl;
		}
		if (evt.type == sf::Event::KeyReleased)
		{
			keyDown = false;
			//player->SetVelocity(sf::Vector2f(0.0f, 0.0f));
		}
	}
	//player->GetInput(window);
}
void Engine::Update()
{
	currentTime = GetTickCount64();
	timeStep = currentTime - timeSinceLastUpdate;
	//camera->GoToCenter((int)player->GetPosition().x, (int)player->GetPosition().y);
	camera->Update();
	player->Update(timeStep);
	timeSinceLastUpdate = currentTime;
}
void Engine::MainLoop()
{
	//loop until the window is closed
	while (window->isOpen())
	{
		ProcessInput();
		Update();
		RenderFrame();
	}

}
void Engine::Start()
{
	if (!Init())
		throw "Could not initialize engine";
	MainLoop();
}