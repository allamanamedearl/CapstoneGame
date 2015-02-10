#include "Engine.h"
#include <iostream>
#include <Windows.h>
int num = 0;
Engine::Engine()
{
	tileSize = 32;
	camera = new Camera(3200, 3200, 0.2f);//map size to get bounds 100 by 100 times tile size
	screenWidth = 800;
	screenHeight = 600;
	keyDown = false;
	
	//timeSinceLastUpdate = 0;
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
	delete player;
	player = nullptr;
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
	if (!npcTexture.loadFromFile("C:/Users/Cassie/Desktop/School Stuff/Capstone/CapstoneGit/SFML/SFML/otherSprite.png"))
	{
		std::cout << "Unable to load npc texture";
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
	view = new sf::View();
	view->reset(sf::FloatRect(0, 0, screenWidth,screenHeight ));//what part is shown
	textureManager = new TextureManager();
	LoadTextures();
	//for testing
	LoadLevel();
	std::cout << "\nAfter LoadLevel() call" << std::endl;
	collisionHandling = new CollisionHandling(textureManager, currLevel);
	player = new Player(&playerTexture,collisionHandling);
	for (int i = 0; i < currLevel->npcs.size(); i++)
	{
		NPC* npc = new NPC(&npcTexture, collisionHandling, currLevel->npcs[i].startPos);
		npc->SetBehaviour(currLevel->npcs[i].behaviour);
		npc->SetEndPos(sf::Vector2f(10.0f, 10.0f));//in case it's a patrol npc
		level_NPCs.push_back(npc);
	}
	/*npc = new NPC(&npcTexture, collisionHandling, sf::Vector2f(5.0f, 5.0f));
	npc2 = new NPC(&npcTexture, collisionHandling, sf::Vector2f(10.0f, 10.0f));
	npc3 = new NPC(&npcTexture, collisionHandling, sf::Vector2f(0.0f, 5.0f));
	npc->SetBehaviour("Patrol");
	npc2->SetBehaviour("Pursue");
	npc3->SetBehaviour("Idle");*/
	//npc->SetEndPos(sf::Vector2f(10.0f, 10.0f));
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
	std::cout << currLevel->npcs.size() << std::endl;

	//initialize collisionHandling
	//collisionHandling = new CollisionHandling();
}
void Engine::RenderFrame()
{
	int camOffsetX, camOffsetY;
	Tile* tile;
	window->clear();
	//get the tile bounds needed to draw and camera bounds
	//returns camera view window as rect based on tilesizes 
	//eg. 10 tiles by 10 tiles top left is tile 5,3,
	//rect is updated when camera is moved
	sf::IntRect bounds = camera->GetTileBounds(tileSize);
	//how much to offset each tile
	camOffsetX = camera->GetTileOffset(tileSize).x;
	camOffsetY = camera->GetTileOffset(tileSize).y;

#pragma region old way nvm
	////so we don't get a vector out of bounds error
	if (bounds.width > currLevel->GetWidth())
	{
		bounds.width = currLevel->GetWidth();
	}
	if (bounds.height > currLevel->GetHeight())
	{
		bounds.height = currLevel->GetHeight();
	}
	////loop and draw each tile
	////keeping track of two variables in each loop. How many tiles
	////drawn (x and y), and which tile on the map is being drawn (tileX
	////and tileY)
	////bounds.top = y coordinate of rect
	int numDrawnTiles = 0;
#pragma region balls
	//for (int y = 0, tileY = bounds.top; y < bounds.height; y++, tileY++)
	//{
	//	for (int x = 0, tileX = bounds.left; x < bounds.width; x++, tileX++)
	//	{
	//		if (tileY >= 0 && tileX >= 0)//only rendering tiles that are seeable not offscreen shit
	//		{

	//			//Get the tile we're drawing
	//			tile = currLevel->GetTile(x, y);//(tileX, tileY);

	//			if (tile)
	//			{
	//				if (camera->CheckIfOnscreen(x, y, tileSize, screenWidth, screenHeight))//CHANGE TO VARIABLES
	//				{
	//					tile->Draw((tileX* tileSize), (tileY * tileSize), window);
	//					numDrawnTiles++;
	//				}
	//				
	//			}
	//				
	//		}
	//	}
	//}
#pragma endregion fuck

	for (int y = 0; y < currLevel->GetHeight(); y++)
	{
		for (int x = 0; x < currLevel->GetWidth(); x++)
		{		
			//Get the tile we're drawing
			tile = currLevel->GetTile(x, y);//(tileX, tileY);

			if (tile)
			{
				if (camera->CheckIfOnscreen(x, y, tileSize, screenWidth, screenHeight))//CHANGE TO VARIABLES
				{
					tile->Draw((x* tileSize), (y * tileSize), window);
					numDrawnTiles++;
				}

			}

		}
	}
	std::cout << numDrawnTiles;//I'm a genius
#pragma endregion and now for something completely different

	//window->draw(sprite);
	//testTile->Draw(10, 10, window);
	player->Draw(window);
	for (int i = 0; i < level_NPCs.size(); i++)
	{
		level_NPCs[i]->Draw(window);
	}
	//npc->Draw(window);
	/*npc2->Draw(window);
	npc3->Draw(window);*/
	
	window->setView(*view);
	window->display();
}
void Engine::ProcessInput()
{
	sf::Event evt;
	if (num >= 1000)
	{
		std::cout << "Player Pos = " << player->GetPosition().x << " " << player->GetPosition().y << std::endl;
		/*std::cout << "currtime " << currentTime << std::endl;
		std::cout << "timeStep " << timeStep << std::endl;*/
		//collisionHandling->GetWorldToTileCoords(player->GetPosition());
		num = 0;
	}
	num++;
	player->GetInput(level_NPCs);
	for (int i = 0; i < level_NPCs.size(); i++)
	{
		level_NPCs[i]->GetMovement(player->GetPosition());
	}
	/*npc->GetMovement(player->GetPosition());
	npc2->GetMovement(player->GetPosition());
	npc3->GetMovement(player->GetPosition());*/
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
			
			//view->zoom(1.0f);
			view->move(0.0f, 1.0f);
			camera->SetRenderingRange(0, -1);//bc moving down
			std::cout<<view->getTransform().getMatrix();
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
	//currentTime = clock.getElapsedTime().asMilliseconds();
	//timeStep = currentTime - timeSinceLastUpdate;
	//camera->GoToCenter((int)player->GetPosition().x, (int)player->GetPosition().y);
	
	//camera->Update();
	//camera->GoTo(0, tileSize);
	player->Update();
	
	
	for (int i = 0; i < level_NPCs.size(); i++)
	{
		level_NPCs[i]->Update();
	}
	/*npc->Update();
	npc2->Update();
	npc3->Update();*/
	//timeSinceLastUpdate = currentTime;
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