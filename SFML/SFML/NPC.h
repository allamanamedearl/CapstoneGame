#pragma once
#include <SFML\Graphics.hpp>

#include "CollisionHandling.h"
#include "Animation.h"
#include "AIBehaviour.h"
class NPC
{
private:
	sf::Vector2f position;
	sf::Vector2f pastPos;
	sf::Vector2f targetPos;//tile npc is moving to
	sf::Vector2f velocity;
	sf::Vector2f start;//start position is tile coordinates
	sf::Vector2f end;//also tile coords
	sf::Clock clock;
	float speed;
	bool isMoving;
	float pixelsToMove;
	bool playerCaught;

	int id;//for dialogue

	sf::Texture controlEffect;//power effect on npc
	sf::Texture madnessEffect;
	sf::Sprite spriteEffect;
	bool userActive;//for whether npc is being controlled by player

	CollisionHandling *cHandler;
	Animation *animation;
	AIBehaviour *behaviour;
	std::string originalAI;//first behaviour starting off
public:
	NPC(sf::Texture *texture, CollisionHandling* collHand, sf::Vector2f startPos);//start pos maybe in tileCoord eg x=3 y=5
	~NPC();

	sf::Vector2f GetPosition(){ return this->position; }
	void SetPosition(sf::Vector2f pos){ this->position = pos; }
	sf::Vector2f GetVelocity(){ return this->velocity; }
	void SetVelocity(sf::Vector2f vel){ this->velocity = vel; }

	int GetId(){ return this->id; }
	void SetId(int id){ this->id = id; }
	
	float GetSpeed(){ return this->speed; }
	void SetSpeed(float val){ this->speed = val; }
	void SetStartPos(sf::Vector2f startPos){ this->start = startPos; }
	void SetEndPos(sf::Vector2f endPos){ this->end = endPos; }

	sf::Vector2f GetStartPos(){ return this->start; }
	sf::Vector2f GetEndPos(){ return this->end; }

	bool GetUserActive(){return this->userActive;}
	bool GetIfPlayerCaught(){ return this->playerCaught; }
	void SetUserActive(bool active){ this->userActive = active; }
	void SetBehaviour(std::string b);
	void SetOriginalBehaviour(std::string b);
	void GetMovement(sf::Vector2f playerPos);
	void Draw(sf::RenderWindow *rw);
	void Update(float timeStep);
};

