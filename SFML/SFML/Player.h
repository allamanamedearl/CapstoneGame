#pragma once
#include<SFML\Graphics.hpp>//may need to remove this later if player inherits
#include<SFML\System\Clock.hpp>
#include "CollisionHandling.h"
#include "Animation.h"
#include "NPC.h"
class Player
{
public:
	Player(sf::Texture *texture, CollisionHandling* collHand, sf::Texture *powers);
	~Player();
	
	sf::Vector2f GetPosition(){ return this->position; }
	void SetPosition(sf::Vector2f pos){ this->position = pos; }
	sf::Vector2f GetVelocity(){ return this->velocity; }
	void SetVelocity(sf::Vector2f vel){ this->velocity = vel; }
	
	void GetInput(std::vector<NPC*> &NPCs);
	void Draw(sf::RenderWindow *rw);
	void Update(float timeStep);

	void SetUserActive(bool active){ this->userActive = active; }
	bool CheckActive(){ return this->userActive; }//returns whether player is active
	std::string CheckActivePowers();

	//set powers to true or false
	void SetRage(bool active){ this->psychoticRage = active; }
	void SetMadness(bool active){ this->triggerMadness = active; }
	void SetControl(bool active){ this->controlNPC = active; }

	//hints stuff
	bool GetIfNearBreakable(){ return this->nearBreakable; }
	bool GetIfNearControlable(){ return this->nearControlable; }
	bool GetIfNearTriggerable(){ return this->nearTriggerable; }
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	float speed;
	bool isVisible;
	float awareness;
	//sf::Sprite *sprite;
	//sf::Texture* texture;
	bool isMoving;
	float pixelsToMove;
	sf::Vector2f endPos;//target end position
	sf::Vector2f pastPos;//starting position before moving

	//Time stuff for power animations
	sf::Clock madClock;
	sf::Clock rageClock;
	sf::Clock controlClock;
	sf::Time madTime;
	sf::Time rageTime;
	sf::Time controlTime;

	CollisionHandling* cHandler;
	//NPC targetNPC;
	
	//NPC GetNearbyNPC();

	Animation* animation;
	Animation* powerAnim;

	//powers
	bool triggerMadness;
	bool psychoticRage;
	bool controlNPC;

	int numMadNPC;
	//bools for animation
	bool animateMadness;
	bool animateRage;
	bool animateControl;

	//bools for hints
	bool nearBreakable;
	bool nearControlable;
	bool nearTriggerable;
	
	bool userActive;//for whether npc is being controlled by player
};

