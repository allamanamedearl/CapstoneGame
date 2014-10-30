#pragma once
#include<SFML\Graphics.hpp>//may need to remove this later if player inherits
class Player
{
public:
	Player(sf::Texture *texture);
	~Player();
	
	sf::Vector2f GetPosition(){ return this->position; }
	void SetPosition(sf::Vector2f pos){ this->position = pos; }
	sf::Vector2f GetVelocity(){ return this->velocity; }
	void SetVelocity(sf::Vector2f vel){ this->velocity = vel; }
	
	void GetInput();
	void Draw(sf::RenderWindow *rw);
	void Update(float timeStep);
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	bool isVisible;
	float awareness;
	sf::Sprite *sprite;
	sf::Texture texture;
	//NPC targetNPC;
	
	//NPC GetNearbyNPC();
	
	
};

