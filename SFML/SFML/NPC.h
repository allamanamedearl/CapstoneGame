#pragma once
#include <SFML\Graphics.hpp>

#include "CollisionHandling.h"
#include "Animation.h"
#include "AIBehaviour.h"
class NPC
{
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f start;//start position is tile coordinates
	sf::Vector2f end;//also tile coords
	sf::Clock clock;
	float speed;
	bool isMoving;
	float pixelsToMove;

	bool userActive;//for whether npc is being controlled by player

	CollisionHandling *cHandler;
	Animation *animation;
	AIBehaviour *behaviour;
public:
	NPC(sf::Texture *texture, CollisionHandling* collHand, sf::Vector2f startPos);//start pos maybe in tileCoord eg x=3 y=5
	~NPC();

	sf::Vector2f GetPosition(){ return this->position; }
	void SetPosition(sf::Vector2f pos){ this->position = pos; }
	sf::Vector2f GetVelocity(){ return this->velocity; }
	void SetVelocity(sf::Vector2f vel){ this->velocity = vel; }
	
	float GetSpeed(){ return this->speed; }
	void SetSpeed(float val){ this->speed = val; }
	void SetStartPos(sf::Vector2f startPos){ this->start = startPos; }
	void SetEndPos(sf::Vector2f endPos){ this->end = endPos; }

	sf::Vector2f GetStartPos(){ return this->start; }
	sf::Vector2f GetEndPos(){ return this->end; }

	void SetUserActive(bool active){ this->userActive = active; }
	void SetBehaviour(std::string b);
	void GetMovement(sf::Vector2f playerPos);
	void Draw(sf::RenderWindow *rw);
	void Update();
};

