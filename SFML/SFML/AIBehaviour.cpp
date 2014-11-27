#include "AIBehaviour.h"


AIBehaviour::AIBehaviour(CollisionHandling *collHandling)
{
	cHandler = collHandling;
}


AIBehaviour::~AIBehaviour()
{
	delete cHandler;
	cHandler = nullptr;
}
char AIBehaviour::IdleAI(sf::Vector2f pos,sf::Vector2f vel)
{
	/*char direction = ' ';
	while (direction = ' ')
	{*/
		int randNum = rand() % 4;//random num between 0 and 3
		std::cout << "randNum " << randNum << std::endl;
		if (randNum == 0) //left
		{
			//bool isWalkable = cHandler->PlayerCollisionDetection('l', pos, vel);
			//if (isWalkable)
			//{
				return 'l';
			//}
			//else
			//{
				//direction = ' ';
			//}
		}
		else if (randNum == 1)//right
		{
			/*bool isWalkable = cHandler->PlayerCollisionDetection('r', pos, vel);
			if (isWalkable)
			{*/
				return 'r';
			/*}
			else
			{*/
				//direction = ' ';
			//}
		}
		else if (randNum == 2)//up
		{
			//bool isWalkable = cHandler->PlayerCollisionDetection('u', pos, vel);
			//if (isWalkable)
			//{
				return 'u';
			/*}
			else
			{
				direction = ' ';
			}*/
		}
		else if (randNum == 3)//down
		{
			/*bool isWalkable = cHandler->PlayerCollisionDetection('d', pos, vel);
			if (isWalkable)
			{*/
				return 'd';
			/*}
			else
			{
				direction = ' ';
			}*/
		}
	//}

}
char AIBehaviour::PatrolAI(sf::Vector2f pos, sf::Vector2f vel, int start, int end)
{
	return 'r';
}
char AIBehaviour::PursueAI(sf::Vector2f pos, sf::Vector2f vel)
{
	return 'r';
}
