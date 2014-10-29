#include "Engine.h"

Engine::Engine()
{
	tileSize = 32;
	camera = new Camera(720, 480, 0.2f);
	keyDown = false;
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
}
void Engine::LoadTextures()
{
	//loads top left square
	sprite.loadFromFile("C:/Users/Cassie/Desktop/School Stuff/Assets/tileset.png",sf::IntRect(0,0,32,32));
	textureManager->AddTexture(sprite);
	sprite.loadFromFile("C:/Users/Cassie/Desktop/School Stuff/Assets/tileset.png", sf::IntRect(32, 0, 32, 32));
	textureManager->AddTexture(sprite);
	testTile = new Tile(textureManager->GetTexture(0));
}
bool Engine::Init()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "RPG");
	textureManager = new TextureManager();
	LoadTextures();
	//for testing
	LoadLevel();
	
	if (!window)
		return false;
	return true;
}
void Engine::LoadLevel()
{
	int numTiles = 40;
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
	}

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
	window->display();
}
void Engine::ProcessInput()
{
	sf::Event evt;
	//loop through all window events
	while (window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed)
			window->close();
		if (evt.type == sf::Event::KeyPressed && keyDown ==false)
		{
			int x = camera->GetPosition().x;
			int y = camera->GetPosition().y + 1;
			camera->GoToCenter(x, y);
			keyDown = true;

		}
		if (evt.type == sf::Event::KeyReleased)
			keyDown = false;
	}
}
void Engine::Update()
{
	camera->Update();
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