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
	char PatrolAI(sf::Vector2f pos,sf::Vector2f vel,sf::Vector2f start,sf::Vector2f end);
	char PursueAI(sf::Vector2f pos,sf::Vector2f vel);

	bool CheckIfInClosedList(sf::Vector2f pos);
	void ClearClosedList();

	int ManhattanDistance(sf::Vector2f point, sf::Vector2f goal);
private:
	std::vector<sf::Vector2f> closedList;
	Behaviour currentAI;
	CollisionHandling* cHandler;
};

