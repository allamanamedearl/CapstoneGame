#include <cmath>
#include "AIBehaviour.h"


AIBehaviour::AIBehaviour(CollisionHandling *collHandling)
{
	cHandler = collHandling;
	prevPlayerPos = sf::Vector2f(0.0f, 0.0f);
	currPlayerPos = sf::Vector2f(0.0f, 0.0f);
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
char AIBehaviour::PatrolAI(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f start, sf::Vector2f end)
{
	int regG = 10;//north east south west g cost
	int obstacleG = 1000;//g for non walkable
	//start and end are tile coordinates
	
	//similar to pursue, once npc reaches end they head toward start
	//std::vector<sf::Vector2f> openList;
	

	std::vector<int> costs;
	//costs.resize(4);
	//get current position
	//get north, east, south and west
	sf::Vector2f north = sf::Vector2f(start.x, start.y - 1);
	sf::Vector2f east = sf::Vector2f(start.x + 1, start.y);
	sf::Vector2f south = sf::Vector2f(start.x, start.y + 1);
	sf::Vector2f west = sf::Vector2f(start.x - 1, start.y);
	
	//f=g+h
	int northCost;
	int eastCost;
	int southCost;
	int westCost;
	//checks to see if we've already been there
	//north
	if (CheckIfInClosedList(north))
	{
		northCost = obstacleG;
	}
	else{
		//check if walkable, if true g = 10 //have to pass world coordinates
		if (cHandler->PlayerCollisionDetection('u', cHandler->GetTileToWorldCoords(start), vel))
		{
			northCost = regG + ManhattanDistance(north, end);
		}
		else if (!cHandler->PlayerCollisionDetection('u', cHandler->GetTileToWorldCoords(start), vel))
		{
			northCost = obstacleG + ManhattanDistance(north, end);
		}
	}
	//eastCost
	if (CheckIfInClosedList(east))
	{
		eastCost = obstacleG;
	}
	else
	{
		if (cHandler->PlayerCollisionDetection('r', cHandler->GetTileToWorldCoords(start), vel))
		{
			eastCost = regG + ManhattanDistance(east, end);
		}
		else if (!cHandler->PlayerCollisionDetection('r', cHandler->GetTileToWorldCoords(start), vel))
		{
			eastCost = obstacleG + ManhattanDistance(east, end);
		}
	}
	//southcost
	if (CheckIfInClosedList(south))
	{
		southCost = obstacleG;
	}
	else
	{
		if (cHandler->PlayerCollisionDetection('d', cHandler->GetTileToWorldCoords(start), vel))
		{
			southCost = regG + ManhattanDistance(south, end);
		}
		else if (!cHandler->PlayerCollisionDetection('d', cHandler->GetTileToWorldCoords(start), vel))
		{
			southCost = obstacleG + ManhattanDistance(south, end);
		}
	}
	//westCost
	if (CheckIfInClosedList(west))
	{
		westCost = obstacleG;
	}
	else
	{
		if (cHandler->PlayerCollisionDetection('l', cHandler->GetTileToWorldCoords(start), vel))
		{
			westCost = regG + ManhattanDistance(west, end);
		}
		else if (!cHandler->PlayerCollisionDetection('l', cHandler->GetTileToWorldCoords(start), vel))
		{
			westCost = obstacleG + ManhattanDistance(west, end);
		}
	}
	costs.push_back(northCost);
	costs.push_back(eastCost);
	costs.push_back(southCost);
	costs.push_back(westCost);


	int leastCost;//cheapest option
	leastCost = northCost;
	for (int i = 0; i < costs.size();i++)
	{
		if (leastCost >= costs[i])
		{
			leastCost = costs[i];
		}
	}

	if (leastCost == northCost)
	{
		//add to closed list
		closedList.push_back(north);
		return 'u';
	}
	else if (leastCost == eastCost)
	{
		//add to closed list
		closedList.push_back(east);
		return 'r';
	}
	else if (leastCost == southCost)
	{
		//add to closed list
		closedList.push_back(south);
		return 'd';
	}
	else if (leastCost == westCost)
	{
		//add to closed list
		closedList.push_back(west);
		return 'l';
	}
	//calculate heuristic using Manhattan distance  Mathf.RoundToInt(Mathf.Abs(point.x - goal.x) + Mathf.Abs(point.y - goal.y));
	//g value will be 10 for alldirections except diagonals and non walkable tiles
	//return 'r';
}
char AIBehaviour::PursueAI(sf::Vector2f pos, sf::Vector2f vel,sf::Vector2f end)
{
	currPlayerPos = cHandler->GetWorldToTileCoords(end);
	//for when player position changes, that way you can walk on previously walked on tiles
	if (currPlayerPos != prevPlayerPos)
	{
		ClearClosedList();
	}
	prevPlayerPos = currPlayerPos;
	//check if npc is in same position as player
	if (cHandler->GetWorldToTileCoords(end) == cHandler->GetWorldToTileCoords(pos) - sf::Vector2f(0,1) ||
		cHandler->GetWorldToTileCoords(end) == cHandler->GetWorldToTileCoords(pos) - sf::Vector2f(1,0)||
		cHandler->GetWorldToTileCoords(end) == cHandler->GetWorldToTileCoords(pos) - sf::Vector2f(0,-1)||
		cHandler->GetWorldToTileCoords(end) == cHandler->GetWorldToTileCoords(pos) - sf::Vector2f(-1,0))
	{
		return 's';//s for stop
	}
	else
	{
		//pass npc position, velocity, start which is pos converted to tile coords, end is playerPos converted to tileCoords
		return PatrolAI(pos, vel, cHandler->GetWorldToTileCoords(pos), cHandler->GetWorldToTileCoords(end));
	}
	
}
char AIBehaviour::GuardAI(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f end)
{
	//end is player position
	if (pos.x > end.x) //if ur to the right of the player
	{
		return 'r';//face right
	}
	else
	{
		return 'l';
	}
}
int AIBehaviour::ManhattanDistance(sf::Vector2f point, sf::Vector2f goal)
{
	
	return (int)(fabsf(point.x - goal.x) + fabsf(point.y - goal.y));
	//Mathf.RoundToInt(Mathf.Abs(point.x - goal.x) + Mathf.Abs(point.y - goal.y));
}
bool AIBehaviour::CheckIfInClosedList(sf::Vector2f pos)
{
	if (std::find(closedList.begin(), closedList.end(), pos) != closedList.end())
	{
		return true;//value is in closed List
	}
	else
	{
		return false;
	}
}
void AIBehaviour::ClearClosedList()
{
	closedList.clear();
}