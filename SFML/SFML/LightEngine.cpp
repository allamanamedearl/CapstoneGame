#include "LightEngine.h"


LightEngine::LightEngine()
{
}


LightEngine::~LightEngine()
{
}
LightEngine::FindDistance::FindDistance()
{
	start = false;
	shortest = 0;
}
const sf::Vector2f LightEngine::GetCenter(const sf::FloatRect &fr)
{
	return sf::Vector2f(fr.left + (fr.width / 2), fr.top + (fr.height / 2));
}
const float LightEngine::Distance(const sf::Vector2f &p1, const sf::Vector2f &p2)
{
	//We need to look at this as a triangle


	float a = p2.x - p1.x;  //width length
	float b = p2.y - p1.y; //height length
	float c = sqrt((a * a) + (b * b)); //Pythagorean Theorem. (c� = a� + b�). c = squareroot(a� + b�)

	return c;
}
void LightEngine::InitLights()
{
	for (unsigned i = 0; i < Lights.size(); i++)
	{
		ShineLight(Lights[i]);
	}
}
void LightEngine::ShineLight(Light &l)
{
	

	//http://math2.org/math/geometry/circles.htm
	float current_angle = l.angle - (l.angleSpread / 2); //This will rotate the angle back far enough to get a desired arc

	/*
	Lights Angle (if it was at 0):

	-------------

	Current_Angle:
	/
	/
	/
	(slanted)

	*/

	float dyn_len = l.radius; //dynamic length of the light. This will be changed in the function LightHitsBlock()

	float addto = 1.f / l.radius;
	bool firstHitofBlock = false;//so it doesn't change blocked angle to the next line's angle
	//need to add to the current angle, until it reaches the end of the arc. divide 1.f by radius for a more solid shape. Otherwise you could see lines seperating
	for (current_angle; current_angle < l.angle + (l.angleSpread / 2); current_angle += addto * (180.f / 3.14f)) 
	{
		dyn_len = l.radius; //Reset the length
		findDis.start = true; //Start of finding a light, need to reset
		findDis.shortest = 0; //Reset the shortest.



		if (l.dynamic) //can this change?
		{
			
			for (unsigned i = 0; i < Blocks.size(); i++)
			{
				if (findDis.LightHitsBlock(l, Blocks[i], current_angle, dyn_len)&&!firstHitofBlock)
				{
					l.getsBlocked = true;
					l.blockAngle = current_angle;
					firstHitofBlock = true;
				}
			}
		}


		float radians = current_angle * (3.14f / 180); //Convert to radians for trig functions

		sf::Vector2f end = l.position;
		end.x += cos(radians) * dyn_len;
		end.y += sin(radians) * dyn_len;
		sf::Vertex startLine = sf::Vertex(l.position);
		startLine.color = sf::Color(255, 255, 255, 10);
		sf::Vertex endLine = sf::Vertex(end);
		endLine.color = sf::Color(255, 255, 255, 10);
		sf::Vertex line[] =
		{
			/*sf::Vertex(l.position),
			sf::Vertex(end)*/
			startLine,
			endLine
		};
		
		/*sf::RectangleShape line;
		line.setFillColor(sf::Color(255, 255, 255, 100));
		line.setPosition(l.position);
		line.setSize(sf::Vector2f(end.x - l.position.x,2.0f));
		rt.draw(line);*/
		//allLights.push_back();
		allLights.append(startLine);
		allLights.append(endLine);
		//rt.draw(line, 2, sf::Lines);// sf::RenderStates::RenderStates());
		//rt.Draw(sf::Shape(sf::Shape::Line(l.position, end, 1, l.color)));
	}
	allLights.setPrimitiveType(sf::Lines);
	//rt.draw(allLights);

}
bool LightEngine::CheckForPlayerCollision(sf::Vector2f playerPos)
{
	//http://stackoverflow.com/questions/13652518/efficiently-find-points-inside-a-circle-sector
	for (int i = 0; i < Lights.size(); i++)//for each light
	{
		//check if player is within radius of light
		if (Distance(playerPos, Lights[i].position) < Lights[i].radius)
		{
			//check if within start and end lines of light cone

			float current_angle = Lights[i].angle - (Lights[i].angleSpread / 2);
			
			sf::Vector2f startLine = CalculateStartLine(Lights[i], current_angle);

			float end_angle = Lights[i].angle + (Lights[i].angleSpread / 2);

			sf::Vector2f endLine = CalculateEndLine(Lights[i], end_angle);
			//isClockwise---player pos is a point, needs to be vector from start of light to player
			//one needs to be false and the other true, player needs to be clockwise to one vector and counter clockwise to another
			if (Lights[i].getsBlocked)
			{
				//if light gets blocked at somepoint gotta check to see if player is standing in 'shadow'
				//check to see if pos is within shadow cone
				//calculate the shorter length cone that's based off the modified radius
				//if player is in shadow cone and not in shorter length cone then player is not in light
			}
			if (isClockwise(startLine, playerPos - Lights[i].position) && !isClockwise(endLine, playerPos - Lights[i].position))//&&!Lights[i].getsBlocked)
				return true;
			else
				return false;
		}

	}
	return false;
}
sf::Vector2f LightEngine::CalculateStartLine(Light l, float angle)
{
	
	float radians = angle * (3.14f / 180); //Convert to radians for trig functions
	sf::Vector2f end = l.position;
	sf::Vector2f start = l.position;
	end.x += cos(radians) * l.radius;//dyn_len;
	end.y += sin(radians) * l.radius;//dyn_len;
	
	return sf::Vector2f(end.x - start.x, end.y - start.y);
}
sf::Vector2f LightEngine::CalculateEndLine(Light l, float angle)
{
	float radians = angle * (3.14f / 180); //Convert to radians for trig functions
	sf::Vector2f endEnd = l.position;
	sf::Vector2f start = l.position;
	//sf::Vector2f startEnd = Lights[i].position;
	endEnd.x += cos(radians) * l.radius;//dyn_len;
	endEnd.y += sin(radians) * l.radius;//dyn_len;
	
	return sf::Vector2f(endEnd.x - start.x, endEnd.y - start.y);
}
bool LightEngine::isClockwise(sf::Vector2f a, sf::Vector2f b)
{
	//find normal
	sf::Vector2f normA = sf::Vector2f(-a.y, a.x);
	//scaler projection
	float proj = b.x*normA.x + b.y*normA.y;

	
	if (proj > 0)
		return true;
	else
		return false;

}
void LightEngine::DrawLights(sf::RenderTarget &rt)
{
	rt.draw(allLights);
}
bool LightEngine::FindDistance::LightHitsBlock(Light &l, Block &b, float cur_ang, float &refleng)
{
	if (b.allowBlock) //can this even block?
	{
		float distance = Distance(l.position, GetCenter(b.fRect));

		if (l.radius >= distance) //check if it's radius is even long enough to hit a block
		{
			float radians = cur_ang * (3.14f / 180); //convert cur_ang to radians for trig functions
			sf::Vector2f pointpos = l.position;

			pointpos.x += cos(radians) * distance;
			pointpos.y += sin(radians) * distance;
			//By doing this, check if the angle is in the direciton of the block.

			if (b.fRect.contains(pointpos)) //If it was, than the point would be intersecting the rectangle of the block
			{
				if (start || distance < shortest) //If this is the first block, or it has a shorter distance
				{
					start = false; //definitely not the start so other blocks can't automatically set the distance
					shortest = distance; //shortest is set to this
					refleng = distance; //This is where the dynamic comes in, it changes the length of the reference towhere it's going to stop after it hits the distance from the point to the block
				}
				return true;
			}
		}
	}
	return false;
}
