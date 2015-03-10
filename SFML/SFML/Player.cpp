#include "Player.h"
#include <iostream>


Player::Player(sf::Texture *texture , CollisionHandling* collHand, sf::Texture *powers)
{
	//sprite = new sf::Sprite(*texture);
	//texture = new sf::Texture (*texture);
	speed = 2.0f;
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
		//*******POWERS***********
		//trigger others's madness
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && !triggerMadness)
		{
			std::cout << "TRIGGER SOMEONE'S MADNESS" << std::endl;
			sf::Vector2f playerTilePos = cHandler->GetWorldToTileCoords(position);
			for (int i = 0; i < NPCs.size(); i++)
			{
				sf::Vector2f npcTilePos = cHandler->GetWorldToTileCoords(NPCs[i]->GetPosition());
				//check to see if any of the npcs are in range
				if (npcTilePos.x >= (playerTilePos.x - 1) && npcTilePos.x <= (playerTilePos.x + 1) &&
					npcTilePos.y >= (playerTilePos.y - 1) && npcTilePos.y <= (playerTilePos.y + 1))
				{
					//if they are set a bool to true
					triggerMadness = true;
					//play power animation
					powerAnim->Madness();
					//set ai to freakout
					NPCs[i]->SetSpeed(NPCs[i]->GetSpeed() * 2.0f);
					NPCs[i]->SetBehaviour("Idle");//idle for now
					
					break;
				}
				
				//have a delay so that you can't keep triggering power, also so that there is a recharge time
			}
		}
		//trigger psychotic rage
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && !psychoticRage)
		{
			sf::Vector2f playerTilePos = cHandler->GetWorldToTileCoords(position);
			//set psychotic rage to true
			psychoticRage = true;
			powerAnim->Rage();
			
			cHandler->CheckBreakableTiles(playerTilePos);

		}
	}
	else//so you can;t get input while player is still moving
	{
		sf::Vector2f playerTilePos = cHandler->GetWorldToTileCoords(position);
		std::cout << "PLayer tile pos: " << playerTilePos.x << " " << playerTilePos.y <<std::endl;
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
void Player::Update()
{

	position += velocity;// *timeStep;
	SetPosition(position);

	animation->Update();
	powerAnim->Update();
	//sprite->setPosition(position);
	animation->SetPosition(position);
	powerAnim->SetPosition(position - sf::Vector2f(32.0f, 32.0f));//so animation is always centered on player
	
	
}
void Player::Draw(sf::RenderWindow *rw)
{
	
	//rw->draw(*sprite);
	rw->draw(*animation->GetCurrentFrame());
	if (triggerMadness || controlNPC || psychoticRage)
	{
		rw->draw(*powerAnim->GetCurrentFrame());
	}
	
	//rw->draw(*te);
}
