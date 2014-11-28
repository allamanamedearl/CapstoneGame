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
	sf::Clock clock;
	float speed;
	bool isMoving;
	float pixelsToMove;

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

	void SetBehaviour(std::string b);
	void GetMovement();
	void Draw(sf::RenderWindow *rw);
	void Update();
};

