#include "Player.h"
#include <iostream>


Player::Player(sf::Texture *texture , CollisionHandling* collHand)
{
	//sprite = new sf::Sprite(*texture);
	position = sf::Vector2f(0.0f, 0.0f);
	velocity = sf::Vector2f(0.0f, 0.0f);
	SetPosition(position);
	//sprite->setPosition(position);
	isVisible = true;
	animation = new Animation();
	isMoving = false;

	animation->SetFrames(texture, 32, 32, (int)texture->getSize().x, (int)texture->getSize().y);
	animation->SetPosition(position);
	pixelsToMove = 32;//tile size
	cHandler = collHand;
}


Player::~Player()
{
	delete sprite;
	sprite = nullptr;
	delete cHandler;
	cHandler = nullptr;
	delete animation;
	animation = nullptr;
}

void Player::GetInput()
{
	
	if (!isMoving){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			animation->Up();
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
			animation->Down();
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
			animation->Left();
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
			animation->Right();
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
	else//so you can;t get input while player is still moving
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

	animation->Update();
	//sprite->setPosition(position);
	animation->SetPosition(position);
	
	
}
void Player::Draw(sf::RenderWindow *rw)
{
	//rw->draw(*sprite);
	rw->draw(*(animation->GetCurrentFrame()));
}
