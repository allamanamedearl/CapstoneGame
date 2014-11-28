#include "NPC.h"


NPC::NPC(sf::Texture *texture, CollisionHandling* collHand, sf::Vector2f startPos)
{

	speed = 1.0f;
	SetPosition(collHand->GetTileToWorldCoords(startPos));
	velocity = sf::Vector2f(0.0f, 0.0f);
	isMoving = false;
	animation = new Animation();
	animation->SetFrames(*texture, 32, 32, (int)texture->getSize().x, (int)texture->getSize().y);
	cHandler = collHand;
	behaviour = new AIBehaviour(collHand);
	pixelsToMove = 32;//tile size
}


NPC::~NPC()
{
	delete cHandler;
	cHandler = nullptr;
	delete animation;
	animation = nullptr;
	delete behaviour;
	behaviour = nullptr;
}
void NPC::SetBehaviour(std::string b)
{
	if (b == "Idle")
	{
		behaviour->SetCurrentAI(AIBehaviour::Behaviour::Idle);
	}
	else if (b == "Patrol")
	{
		behaviour->SetCurrentAI(AIBehaviour::Behaviour::Patrol);
	}
	else if (b == "Pursue")
	{
		behaviour->SetCurrentAI(AIBehaviour::Behaviour::Pursue);
	}
	
}
void NPC::GetMovement()
{
	char direction;
	if (behaviour->GetCurrentAI() == AIBehaviour::Behaviour::Idle)
	{
		direction = behaviour->IdleAI(position, velocity);
	}
	if (behaviour->GetCurrentAI() == AIBehaviour::Behaviour::Patrol)
	{
		//direction = behaviour->PatrolAI();
	}
	if (behaviour->GetCurrentAI() == AIBehaviour::Behaviour::Pursue)
	{ 
		//direction = behaviour->PursueAI();
	}
	if (!isMoving){
		animation->Pause();
		switch (direction)
		{
		case 'l':
		{
					bool isWalkable = cHandler->PlayerCollisionDetection('l', position, velocity);

					animation->Left();
					if (isWalkable)
					{
						velocity.x = -speed;
						velocity.y = 0.0f;
						isMoving = true;
					}
					else//if next tile isn't walkable
					{
						velocity.x = 0.0f;
					}
					break;
		}
		
		case 'r':
		{
					bool isWalkable = cHandler->PlayerCollisionDetection('r', position, velocity);
					animation->Right();
					if (isWalkable)
					{
						velocity.x = speed;
						velocity.y = 0.0f;
						isMoving = true;
					}
					else//if next tile isn't walkable
					{
						velocity.x = 0.0f;
					}
					break;
		}
		case 'u':
		{
					bool isWalkable = cHandler->PlayerCollisionDetection('u', position, velocity);
					animation->Up();
					if (isWalkable)
					{
						velocity.x = 0.0f;
						velocity.y = -speed;
						isMoving = true;
					}
					else//if next tile isn't walkable
					{
						velocity.y = 0.0f;
					}
					break;
		}
		case 'd':
		{
					bool isWalkable = cHandler->PlayerCollisionDetection('d', position, velocity);
					animation->Down();
					if (isWalkable)
					{
						velocity.x = 0.0f;
						velocity.y = speed;
						isMoving = true;
					}
					else//if next tile isn't walkable
					{
						velocity.y = 0.0f;
					}
					break;
		}
		}
	}
	else//so you can;t get input while player is still moving
	{
		sf::Vector2f npcTilePos = cHandler->GetWorldToTileCoords(position);
		std::cout << "NPC tile pos: " << npcTilePos.x << " " << npcTilePos.y << std::endl;
		pixelsToMove -= speed;
		if (pixelsToMove <= 0)
		{
			isMoving = false;
			pixelsToMove = 32;
			velocity.x = 0;
			velocity.y = 0;
		}

	}

	
}
void NPC::Update()
{
	//if (clock.getElapsedTime().asMilliseconds() >= 1000)//so he doesn't spaz out
	//{
		GetMovement();
		position += velocity;// *timeStep;
		//clock.restart();
	//}
	//if (clock.getElapsedTime().asMilliseconds() >= 10000)//so he doesn't spaz out
	//{
	//	
	//	clock.restart();
	//}
	SetPosition(position);

	animation->Update();
	//sprite->setPosition(position);
	animation->SetPosition(position);
}
void NPC::Draw(sf::RenderWindow *rw)
{
	rw->draw(*animation->GetCurrentFrame());
}
