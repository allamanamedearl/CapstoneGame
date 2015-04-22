#include "NPC.h"


NPC::NPC(sf::Texture *texture, CollisionHandling* collHand, sf::Vector2f startPos)
{

	speed = 0.125;//0.25f;
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
	playerCaught = false;

	controlEffect.loadFromFile("controlEffect.png");
	madnessEffect.loadFromFile("madnessEffect.png");
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
	else if (b == "Guard")
	{
		behaviour->SetCurrentAI(AIBehaviour::Behaviour::Guard);
	}
	
}
void NPC::SetOriginalBehaviour(std::string b)
{
	originalAI = b;
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
				
				//if player in EYE SIGHT
				if (behaviour->CheckPlayerInSight(direction, position, velocity, playerPos))
				{
					SetBehaviour("Pursue");
					//direction = behaviour->PursueAI(position, velocity, playerPos);//left out bc pursue comes right after in if statements
				}
				//std::cout << "Direction: " << direction << std::endl;
				//std::cout << "StartPos: " << GetStartPos().x << " " << GetStartPos().y << " EndPos: " << GetEndPos().x << " " << GetEndPos().y << std::endl;
			}
			if (behaviour->GetCurrentAI() == AIBehaviour::Behaviour::Pursue)
			{
				//Pursue ai will convert playerPos to tile coords
				direction = behaviour->PursueAI(position, velocity, playerPos);
				//if player is out of EYE SIGHT
				if (!behaviour->CheckPlayerInSight(direction, position, velocity, playerPos))
				{
					SetBehaviour(originalAI);
				}
			}

			if (behaviour->GetCurrentAI() == AIBehaviour::Behaviour::Idle)
			{
				direction = behaviour->IdleAI(position, velocity);
				
				spriteEffect.setTexture(madnessEffect);
			}
			if (behaviour->GetCurrentAI() == AIBehaviour::Behaviour::Stand)
			{
				velocity = sf::Vector2f(0.0f, 0.0f);
				animation->FaceLeft();
			}
			if (behaviour->GetCurrentAI() == AIBehaviour::Behaviour::Guard)
			{
				velocity = sf::Vector2f(0.0f, 0.0f);
				direction = behaviour->GuardAI(position, velocity, playerPos);
				if (direction == 'r')
				{
					//face right
					animation->FaceRight();

				}
				if (direction == 'l')
				{
					//face left
					animation->FaceLeft();
				}
				//if player in EYE SIGHT
				if (behaviour->CheckPlayerInSight(direction, position, velocity, playerPos))
				{
					SetBehaviour("Pursue");
					direction = behaviour->PursueAI(position, velocity, playerPos);
				}
			}
			if (behaviour->GetCurrentAI() != AIBehaviour::Behaviour::Guard && behaviour->GetCurrentAI() !=AIBehaviour::Behaviour::Stand)
			{
				sf::Vector2f playerTilePos = cHandler->GetWorldToTileCoords(playerPos);
				sf::Vector2f npcTilePos = cHandler->GetWorldToTileCoords(position);
				switch (direction)
				{
				case 'l':
				{
							//std::cout << "left left left" << std::endl;
							bool isWalkable = cHandler->PlayerCollisionDetection('l', position, velocity);
							//std::cout << "*******ISWALKABLE LEFT = " << isWalkable << std::endl;
							animation->Left();
							if (playerTilePos.x >= npcTilePos.x - 1.0f && playerTilePos.x<= npcTilePos.x && playerTilePos.y == npcTilePos.y)
							{
								playerCaught = true;
							}
							if (isWalkable)
							{
								pastPos = GetPosition();
								targetPos = sf::Vector2f(GetPosition().x-pixelsToMove, GetPosition().y);
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
							if (playerTilePos.x <= npcTilePos.x + 1.0f && playerTilePos.x >= npcTilePos.x && playerTilePos.y == npcTilePos.y)
							{
								playerCaught = true;
							}
							if (isWalkable)
							{
								pastPos = GetPosition();
								targetPos = sf::Vector2f(GetPosition().x+pixelsToMove, GetPosition().y);
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
							if (playerTilePos.y >= npcTilePos.y - 1.0f && playerTilePos.y<= npcTilePos.y&& playerTilePos.x == npcTilePos.x)
							{
								playerCaught = true;
							}
							if (isWalkable)
							{
								pastPos = GetPosition();
								targetPos = sf::Vector2f(GetPosition().x, GetPosition().y-pixelsToMove);
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
							if (playerTilePos.y <= npcTilePos.y + 1.0f && playerTilePos.y >= npcTilePos.y && playerTilePos.x == npcTilePos.x)
							{
								playerCaught = true;
							}
							if (isWalkable)
							{
								pastPos = GetPosition();
								targetPos = sf::Vector2f(GetPosition().x, GetPosition().y + pixelsToMove);
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
			
		}
		else//so you can;t get input while player is still moving
		{
			//sf::Vector2f npcTilePos = cHandler->GetWorldToTileCoords(position);
			//std::cout << "NPC tile pos: " << npcTilePos.x << " " << npcTilePos.y << std::endl;
			/*pixelsToMove -= speed;
			if (pixelsToMove <= 0)
			{
				isMoving = false;
				pixelsToMove = 32;
				velocity.x = 0;
				velocity.y = 0;
			}*/
			if (pastPos.x - position.x >= pixelsToMove || pastPos.x - position.x <= -pixelsToMove || pastPos.y - position.y >= pixelsToMove || pastPos.y - position.y <= -pixelsToMove)
			{
				isMoving = false;
				velocity.x = 0.0f;
				velocity.y = 0.0f;
				position = targetPos;
			}

		}
	}
	else
	{
		spriteEffect.setTexture(controlEffect);
		if (!isMoving){
			animation->Pause();//no idle animation so when sprite is stopped it stays on currentFrame
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				animation->Up();
				bool isWalkable = cHandler->PlayerCollisionDetection('u', position, velocity);
				if (isWalkable)
				{
					pastPos = GetPosition();
					targetPos = sf::Vector2f(GetPosition().x, GetPosition().y - pixelsToMove);
					isMoving = true;
					velocity.x = 0.0f;
					velocity.y = -speed;
				}
				else//if next tile isn't walkable
				{
					velocity.y = 0.0f;
				}

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				animation->Down();
				bool isWalkable = cHandler->PlayerCollisionDetection('d', position, velocity);
				if (isWalkable)
				{
					pastPos = GetPosition();
					targetPos = sf::Vector2f(GetPosition().x, GetPosition().y+pixelsToMove);
					isMoving = true;
					velocity.x = 0.0f;
					velocity.y = speed;
				}
				else//if next tile isn't walkable
				{
					velocity.y = 0.0f;
				}

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				animation->Left();
				bool isWalkable = cHandler->PlayerCollisionDetection('l', position, velocity);
				if (isWalkable)
				{
					pastPos = GetPosition();
					targetPos = sf::Vector2f(GetPosition().x-pixelsToMove, GetPosition().y);
					isMoving = true;
					velocity.x = -speed;
					velocity.y = 0.0f;
				}
				else//if next tile isn't walkable
				{
					velocity.x = 0.0f;
				}

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				animation->Right();
				bool isWalkable = cHandler->PlayerCollisionDetection('r', position, velocity);
				if (isWalkable)
				{
					pastPos = GetPosition();
					targetPos = sf::Vector2f(GetPosition().x+pixelsToMove, GetPosition().y);
					isMoving = true;
					velocity.x = speed;
					velocity.y = 0.0f;
				}
				else//if next tile isn't walkable
				{
					velocity.x = 0.0f;
				}
			}
		}
		else//so you can;t get input while player is still moving
		{
			
			if (pastPos.x - position.x >= pixelsToMove || pastPos.x - position.x <= -pixelsToMove || pastPos.y - position.y >= pixelsToMove || pastPos.y - position.y <= -pixelsToMove)
			{
				isMoving = false;
				velocity.x = 0.0f;
				velocity.y = 0.0f;
				position = targetPos;
			}

		}
	}
	
}
void NPC::Update(float timeStep)
{
	//if (clock.getElapsedTime().asMilliseconds() >= 1000)//so he doesn't spaz out
	//{
		//GetMovement();
	position += velocity*timeStep;
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
	spriteEffect.setPosition(position);
}
void NPC::Draw(sf::RenderWindow *rw)
{
	rw->draw(*animation->GetCurrentFrame());
	if (userActive || behaviour->GetCurrentAI() == AIBehaviour::Behaviour::Idle)
	{
		rw->draw(spriteEffect);	
	}
	
}
