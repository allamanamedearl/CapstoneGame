#include "Player.h"
#include <iostream>


Player::Player(sf::Texture *texture , CollisionHandling* collHand, sf::Texture *powers)
{
	//sprite = new sf::Sprite(*texture);
	//texture = new sf::Texture (*texture);
	speed = 0.5f;
	position = sf::Vector2f(0.0f, 256.0f);
	velocity = sf::Vector2f(0.0f, 0.0f);
	SetPosition(position);
	//sprite->setPosition(position);
	isVisible = true;
	animation = new Animation();
	powerAnim = new Animation();
	isMoving = false;

	animation->SetFrames(*texture, 32, 32, (int)texture->getSize().x, (int)texture->getSize().y);
	animation->SetPosition(position);
	powerAnim->SetFrames(*powers, 96, 96, (int)powers->getSize().x, (int)powers->getSize().y);
	powerAnim->SetPosition(position - sf::Vector2f(32.0f, 32.0f));
	pixelsToMove = 32;//tile size
	cHandler = collHand;

	//powers
	triggerMadness = false;
	psychoticRage = false;
	controlNPC = false;
	userActive = true;

	//animate bools
	animateMadness = false;
	animateControl = false;
	animateRage = false;

	nearBreakable = false;
	nearControlable = false;
	nearBreakable = false;
}


Player::~Player()
{
	//delete sprite;
	//sprite = nullptr;
	delete cHandler;
	cHandler = nullptr;
	delete animation;
	animation = nullptr;
	delete powerAnim;
	powerAnim = nullptr;
}

void Player::GetInput(std::vector<NPC*>& NPCs)
{
	
	if (!controlNPC)
	{
		userActive = true;
		for (int i = 0; i < NPCs.size(); i++)
		{
			if (NPCs[i]->GetUserActive())//if npc is user active
			{
				NPCs[i]->SetUserActive(false);
				NPCs[i]->SetSpeed(speed / 2);
			}
		}
	}
	if (!triggerMadness)
	{
		//set back to original behaviour
		NPCs[numMadNPC]->SetSpeed(speed / 2);
	}
	if (userActive){
		sf::Vector2f playerTilePos = cHandler->GetWorldToTileCoords(position);
		if (cHandler->CheckBreakableTilesHint(playerTilePos))
		{
			nearBreakable = true;
		}
		else
		{
			nearBreakable = false;
		}
		//Check to see if close to NPC that you can CONTROL or TRIGGERMADNESS
		for (int i = 0; i < NPCs.size(); i++)
		{
			sf::Vector2f npcTilePos = cHandler->GetWorldToTileCoords(NPCs[i]->GetPosition());
			//check to see if any of the npcs are in range
			nearControlable = false;
			nearTriggerable = false;
			if (npcTilePos.x >= (playerTilePos.x - 1) && npcTilePos.x <= (playerTilePos.x + 1) &&
				npcTilePos.y >= (playerTilePos.y - 1) && npcTilePos.y <= (playerTilePos.y + 1))
			{
				nearControlable = true;
				nearTriggerable = true;
				break;
			}
		}
		
		
		
		if (!isMoving){
			animation->Pause();//no idle animation so when sprite is stopped it stays on currentFrame
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				animation->Up();
				bool isWalkable = cHandler->PlayerCollisionDetection('u', position, velocity);
				if (isWalkable)
				{
					endPos = sf::Vector2f(GetPosition().x,GetPosition().y - pixelsToMove);//end position target is up
					pastPos = GetPosition();
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
					endPos = sf::Vector2f(GetPosition().x,GetPosition().y + pixelsToMove);
					pastPos = GetPosition();
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
					endPos = sf::Vector2f(GetPosition().x - pixelsToMove, GetPosition().y);
					pastPos = GetPosition();
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
					endPos = sf::Vector2f(GetPosition().x + pixelsToMove, GetPosition().y);
					pastPos = GetPosition();
					isMoving = true;
					velocity.x = speed;
					velocity.y = 0.0f;
				}
				else//if next tile isn't walkable
				{
					velocity.x = 0.0f;
					//velocity.y = 0.0f;
				}
			}
			//*******POWERS***********
			//trigger others's madness
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && !triggerMadness)
			{
				std::cout << "TRIGGER SOMEONE'S MADNESS" << std::endl;
				
				for (int i = 0; i < NPCs.size(); i++)
				{
					sf::Vector2f npcTilePos = cHandler->GetWorldToTileCoords(NPCs[i]->GetPosition());
					//check to see if any of the npcs are in range
					if (npcTilePos.x >= (playerTilePos.x - 1) && npcTilePos.x <= (playerTilePos.x + 1) &&
						npcTilePos.y >= (playerTilePos.y - 1) && npcTilePos.y <= (playerTilePos.y + 1))
					{
						//play power animation
						powerAnim->Madness();
						//if they are set a bool to true
						triggerMadness = true;
						animateMadness = true;
						
						//set ai to freakout
						NPCs[i]->SetSpeed(NPCs[i]->GetSpeed() * 4.0f);
						NPCs[i]->SetBehaviour("Idle");//idle for now
						numMadNPC = i;
						madClock.restart();//startclock for reload time
						break; //maybe take this out so it affects all surounding enemies
					}

					//have a delay so that you can't keep triggering power, also so that there is a recharge time
				}
			}
			//trigger psychotic rage
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && !psychoticRage)
			{
				powerAnim->Rage();
				//sf::Vector2f playerTilePos = cHandler->GetWorldToTileCoords(position);
				//set psychotic rage to true
				psychoticRage = true;
				animateRage = true;
				
				rageClock.restart();
				cHandler->CheckBreakableTiles(playerTilePos);

			}
			//trigger control
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && !controlNPC)
			{
				
				//sf::Vector2f playerTilePos = cHandler->GetWorldToTileCoords(position);
				for (int i = 0; i < NPCs.size(); i++)
				{
					sf::Vector2f npcTilePos = cHandler->GetWorldToTileCoords(NPCs[i]->GetPosition());
					//check to see if any of the npcs are in range
					if (npcTilePos.x >= (playerTilePos.x - 1) && npcTilePos.x <= (playerTilePos.x + 1) &&
						npcTilePos.y >= (playerTilePos.y - 1) && npcTilePos.y <= (playerTilePos.y + 1))
					{
						SetVelocity(sf::Vector2f(0.0f, 0.0f));
						powerAnim->Control();//need to change animation so it shows it just affects npc infront of you maybe
						controlClock.restart();
						userActive = false;
						NPCs[i]->SetUserActive(true);
						NPCs[i]->SetSpeed(speed);
						controlNPC = true;
						animateControl = true;
						
						
						break; //maybe take this out so it affects all surounding enemies
					}
				}
			}
		}
		else//so you can;t get input while player is still moving
		{
			//sf::Vector2f playerTilePos = cHandler->GetWorldToTileCoords(position);
			//std::cout << "PLayer tile pos: " << playerTilePos.x << " " << playerTilePos.y << std::endl;
			if (pastPos.x - position.x >= pixelsToMove || pastPos.x - position.x <= -pixelsToMove || pastPos.y - position.y >= pixelsToMove || pastPos.y - position.y <= -pixelsToMove)
			{
				isMoving = false;
				velocity.x = 0.0f;
				velocity.y = 0.0f;
				position = endPos;//set position to the target end position
				//pastPos = sf::Vector2f(NULL,NULL);
			}
			/*pixelsToMove -= speed;
			if (pixelsToMove <= 0)
			{
				isMoving = false;
				pixelsToMove = 32;
				velocity.x = 0;
				velocity.y = 0;
			}*/
			/*if ((int)position.x % (int)pixelsToMove == 0 || (int)position.y % (int)pixelsToMove ==0)
			{
				isMoving = false;
				velocity.x = 0.0f;
				velocity.y = 0.0f;
			}*/

		}
	}
	
}
std::string Player::CheckActivePowers()
{
	std::string activePows;
	if (controlNPC&&triggerMadness&&psychoticRage)
	{
		activePows = "cmp"; //c- control npc, m- trigger madness, p - psychotic rage
	}
	else if (controlNPC&&triggerMadness&&!psychoticRage)//control and trigger madness
	{
		activePows = "cm";
	}
	else if (controlNPC&& !triggerMadness && psychoticRage)//control and psychotic rage
	{
		activePows = "cp";
	}
	else if (controlNPC &&!triggerMadness && !psychoticRage)//just control
	{
		activePows = "c";
	}
	else if (!controlNPC&&triggerMadness&&psychoticRage)//madness and rage
	{
		activePows = "mp";
	}
	else if (!controlNPC&&triggerMadness&&!psychoticRage)//just madness
	{
		activePows = "m";
	}
	else if (!controlNPC&&!triggerMadness&&psychoticRage)//just rage
	{
		activePows = "p";
	}
	else if (!controlNPC&&!triggerMadness&&!psychoticRage)//none active
	{
		activePows = "0";
	}
	return activePows;
}
void Player::Update(float timeStep)
{
	
	position += velocity*timeStep;
	SetPosition(position);

	animation->Update();
	powerAnim->Update();
	//sprite->setPosition(position);
	animation->SetPosition(position);
	powerAnim->SetPosition(position - sf::Vector2f(32.0f, 32.0f));//so animation is always centered on player

	madTime = madClock.getElapsedTime();
	if (madTime.asMilliseconds() >= 2000)//2 seconds
	{
		animateMadness = false;
	}
	rageTime = rageClock.getElapsedTime();
	if (rageTime.asMilliseconds() >= 2000)//2 seconds
	{
		animateRage = false;
	}
	controlTime = controlClock.getElapsedTime();
	if (controlTime.asMilliseconds()>=2000)//2 seconds
	{
		animateControl = false;
	}
	
	
}
void Player::Draw(sf::RenderWindow *rw)
{
	
	//rw->draw(*sprite);
	rw->draw(*animation->GetCurrentFrame());
	if (animateMadness || animateControl || animateRage)
	{
		rw->draw(*powerAnim->GetCurrentFrame());
	}
	
	//rw->draw(*te);
}
