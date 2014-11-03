#include "Player.h"


Player::Player(sf::Texture *texture)
{
	sprite = new sf::Sprite(*texture);
	position = sf::Vector2f(0.0f, 0.0f);
	velocity = sf::Vector2f(0.0f, 0.0f);
	sprite->setPosition(position);
	isVisible = true;
}


Player::~Player()
{
	delete sprite;
	sprite = nullptr;
}
void Player::GetInput()
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.x = 0.0f;
		velocity.y = -0.2f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.x = 0.0f;
		velocity.y = 0.2f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x = -0.2f;
		velocity.y = 0.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x = 0.2f;
		velocity.y = 0.0f;
	}
	
	
}
void Player::Update(float timeStep)
{
	position += velocity*timeStep;
	sprite->setPosition(position);
	
}
void Player::Draw(sf::RenderWindow *rw)
{
	rw->draw(*sprite);
}
