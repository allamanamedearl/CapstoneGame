#ifndef ENGINE_H
#define ENGINE_H

#include <SFML\Graphics.hpp>
#include <string>
#include "CollisionHandling.h"
//#include "TileMap.h"
#include "Camera.h"
#include "Player.h"
#include "Gui.h"
#include "Dialogue.h"
//#include "NPC.h"
class Engine
{
private:
	enum GameState {Menu,Play,End};
	GameState currentState;
	//testing stuff
	TextureManager* textureManager;
	sf::Texture sprite;
	void LoadTextures();
	void LoadLevel();
	Tile* testTile;
	bool keyDown;
	//SFML Render Window
	sf::RenderWindow* window;
	sf::Font guiFont;

	//GUI STUFF
	sf::Texture guiTexture;
	sf::Sprite guiSprite;
	Gui* mainGUI;

	//Dialogue Stuff
	Dialogue* dialogue;

	//camera
	Camera* camera;
	int screenWidth;
	int screenHeight;
	sf::View* view;
	//map
	TileMap* currLevel;
	int tileSize;

	LightEngine* lightEng;
	bool inLight;

	//Player
	Player *player;
	sf::Texture playerTexture;
	sf::Texture powerTexture;

	std::vector<NPC*>level_NPCs;
	/*NPC *npc;
	NPC *npc2;
	NPC *npc3;*/
	sf::Texture npcTexture;

	//Time
	sf::Clock clock;
	sf::Time elapsedTime;
	//float currentTime;
	float timeSinceLastUpdate;
	float timeStep;
	

	//Collision Stuff
	CollisionHandling* collisionHandling;

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