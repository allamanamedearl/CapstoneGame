#include "NPC.h"


NPC::NPC(sf::Texture *texture, CollisionHandling* collHand, sf::Vector2f startPos)
{

	speed = 0.5f;
	SetPosition(collHand->GetTileToWorldCoords(startPos));
	SetStartPos(startPos);
	velocity = sf::Vector2f(0.0f, 0.0f);
	isMoving = false;
	animation = new Animation();
	animation->SetFrames(*texture, 32, 32, (int)texture->getSize().x, (int)texture->getSize().y);
	cHandler = collHand;
	behaviour = new AIBehaviour(collHand);
	pixelsToMove = 32;//tile size
	userActive = false;
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
void NPC::GetMovement(sf::Vector2f playerPos)
{
	char direction;
	if (!userActive){
		if (!isMoving){

			if (behaviour->GetCurrentAI() == AIBehaviour::Behaviour::Patrol)
			{
				//for when npc reaches end of patrol, reverse patrol
				if (cHandler->GetWorldToTileCoords(position) == end)
				{
					sf::Vector2f temp = start;
					SetStartPos(end);
					SetEndPos(temp);
					behaviour->ClearClosedList();
				}
				direction = behaviour->PatrolAI(position, velocity, cHandler->GetWorldToTileCoords(position), end);
				//std::cout << "Direction: " << direction << std::endl;
				//std::cout << "StartPos: " << GetStartPos().x << " " << GetStartPos().y << " EndPos: " << GetEndPos().x << " " << GetEndPos().y << std::endl;
			}
			if (behaviour->GetCurrentAI() == AIBehaviour::Behaviour::Pursue)
			{
				//Pursue ai will convert playerPos to tile coords
				direction = behaviour->PursueAI(position, velocity, playerPos);
			}

			if (behaviour->GetCurrentAI() == AIBehaviour::Behaviour::Idle)
			{
				direction = behaviour->IdleAI(position, velocity);
			}
			switch (direction)
			{
			case 'l':
			{
						//std::cout << "left left left" << std::endl;
						bool isWalkable = cHandler->PlayerCollisionDetection('l', position, velocity);
						//std::cout << "*******ISWALKABLE LEFT = " << isWalkable << std::endl;
						animation->Left();
						if (isWalkable)
						{
							velocity.x = -speed;
							velocity.y = 0.0f;
							isMoving = true;
						}
						else//if next tile isn't walkable
						{
							//std::cout << "********TILE NOT WALKABLE" << std::endl;
							velocity.x = 0.0f;
						}
						break;
			}

			case 'r':
			{
						//std::cout << "right right right" << std::endl;
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
						//std::cout << "up up up" << std::endl;
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
						//std::cout << "down down down" << std::endl;
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
			case 's':
			{
						animation->Pause();
						velocity.x = 0.0f;
						velocity.y = 0.0f;
						break;
			}
			}
		}
		else//so you can;t get input while player is still moving
		{
			sf::Vector2f npcTilePos = cHandler->GetWorldToTileCoords(position);
			//std::cout << "NPC tile pos: " << npcTilePos.x << " " << npcTilePos.y << std::endl;
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
	else
	{
		if (!isMoving){
			animation->Pause();//no idle animation so when sprite is stopped it stays on currentFrame
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				animation->Up();
				bool isWalkable = cHandler->PlayerCollisionDetection('u', position, velocity);
				if (isWalkable)
				{
					isMoving = true;
					velocity.x = 0.0f;
					velocity.y = -speed;
				}
				else//if next tile isn't walkable
				{
					velocity.y = 0.0f;
				}

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				animation->Down();
				bool isWalkable = cHandler->PlayerCollisionDetection('d', position, velocity);
				if (isWalkable)
				{
					isMoving = true;
					velocity.x = 0.0f;
					velocity.y = speed;
				}
				else//if next tile isn't walkable
				{
					velocity.y = 0.0f;
				}

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				animation->Left();
				bool isWalkable = cHandler->PlayerCollisionDetection('l', position, velocity);
				if (isWalkable)
				{
					isMoving = true;
					velocity.x = -speed;
					velocity.y = 0.0f;
				}
				else//if next tile isn't walkable
				{
					velocity.x = 0.0f;
				}

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				animation->Right();
				bool isWalkable = cHandler->PlayerCollisionDetection('r', position, velocity);
				if (isWalkable)
				{
					isMoving = true;
					velocity.x = speed;
					velocity.y = 0.0f;
				}
				else//if next tile isn't walkable
				{
					velocity.x = 0.0f;
					velocity.y = 0.0f;
				}
			}
		}
		else//so you can;t get input while player is still moving
		{
			sf::Vector2f npcTilePos = cHandler->GetWorldToTileCoords(position);
			//std::cout << "NPC tile pos: " << npcTilePos.x << " " << npcTilePos.y << std::endl;
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
	
}
void NPC::Update()
{
	//if (clock.getElapsedTime().asMilliseconds() >= 1000)//so he doesn't spaz out
	//{
		//GetMovement();
	position += velocity;//*time;// *timeStep;
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
