#pragma once
#include <iostream>
#include "CollisionHandling.h"

class AIBehaviour
{

public:
	AIBehaviour(CollisionHandling *collHandling);
	~AIBehaviour();
	enum Behaviour { Idle, Patrol, Pursue };
	Behaviour GetCurrentAI(){ return this->currentAI; }
	void SetCurrentAI(Behaviour AI){ this->currentAI = AI; }
	char IdleAI(sf::Vector2f pos,sf::Vector2f vel);
	char PatrolAI(sf::Vector2f pos,sf::Vector2f vel,int start,int end);
	char PursueAI(sf::Vector2f pos,sf::Vector2f vel);
private:
	Behaviour currentAI;
	CollisionHandling* cHandler;
};

