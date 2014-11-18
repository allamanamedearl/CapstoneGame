#include "Player.h"
#include <iostream>


Player::Player(sf::Texture *texture , CollisionHandling* collHand)
{
	sprite = new sf::Sprite(*texture);
	position = sf::Vector2f(0.0f, 0.0f);
	velocity = sf::Vector2f(0.0f, 0.0f);
	SetPosition(position);
	sprite->setPosition(position);
	isVisible = true;

	cHandler = collHand;
}


Player::~Player()
{
	delete sprite;
	sprite = nullptr;
	delete cHandler;
	cHandler = nullptr;
}
bool isMoving = false;
float pixelsToMove = 32;
void Player::GetInput()
{
	
	if (!isMoving){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			bool isWalkable = cHandler->PlayerCollisionDetection('u', position, velocity);
			if (isWalkable)
			{
				isMoving = true;
				velocity.x = 0.0f;
				velocity.y = -2.0f;
			}
			else//if next tile isn't walkable
			{
				velocity.y = 0.0f;
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			bool isWalkable = cHandler->PlayerCollisionDetection('d', position, velocity);
			if (isWalkable)
			{
				isMoving = true;
				velocity.x = 0.0f;
				velocity.y = 2.0f;
			}
			else//if next tile isn't walkable
			{
				velocity.y = 0.0f;
			}
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			bool isWalkable = cHandler->PlayerCollisionDetection('l', position, velocity);
			if (isWalkable)
			{
				isMoving = true;
				velocity.x = -2.0f;
				velocity.y = 0.0f;
			}
			else//if next tile isn't walkable
			{
				velocity.x = 0.0f;
			}
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			bool isWalkable = cHandler->PlayerCollisionDetection('r', position, velocity);
			if (isWalkable)
			{
				isMoving = true;
				velocity.x = 2.0f;
				velocity.y = 0.0f;
			}
			else//if next tile isn't walkable
			{
				velocity.x = 0.0f;
				velocity.y = 0.0f;
			}
		}
	}
	else
	{
		sf::Vector2f playerTilePos = cHandler->GetWorldToTileCoords(position);
		std::cout << "PLayer tile pos: " << playerTilePos.x << " " << playerTilePos.y <<std::endl;
		pixelsToMove -= 2;
		if (pixelsToMove <= 0)
		{
			isMoving = false;
			pixelsToMove = 32;
			velocity.x = 0;
			velocity.y = 0;
		}
		//if position is on tile--reached destination
		/*if (playerTilePos.x - floor(playerTilePos.x) == 0 && playerTilePos.y - floor(playerTilePos.y)==0)
		{
			isMoving = false;
			velocity.x = 0;
			velocity.y = 0;
		}*/
	}
	
}
void Player::Update(float timeStep)
{

	position += velocity;// *timeStep;
	SetPosition(position);
	sprite->setPosition(position);
	
	
}
void Player::Draw(sf::RenderWindow *rw)
{
	rw->draw(*sprite);
}
