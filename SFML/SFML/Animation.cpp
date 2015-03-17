#include "Animation.h"
#include <iostream>

Animation::Animation()
{
	up = false;
	down = false;
	left = false;
	right = false;
	pause = true;

	triggerMadness = false;
	psychoticRage = false;
	controlNPC = false;
	currentFrame = 0;
}
Animation::~Animation()
{

}
void Animation::SetFrames(sf::Texture sheet, int sizeX,int sizeY, int width, int height)
{
	spriteSheet = sheet;//save the sheet so I don't lose the texture!!!
	
	for (int y = 0; y < height/sizeY; y++)
	{
		for (int x = 0; x < width/sizeX; x++)//row width
		{
			sf::Sprite *temp= new sf::Sprite(spriteSheet, sf::IntRect(x *sizeX, y*sizeY, sizeX, sizeY));
			temp->setPosition(sf::Vector2f(0.0f, 0.0f));//initialize position
			frames.push_back(temp);
			
		}
	}
}
void Animation::SetPosition(sf::Vector2f pos)
{
	frames[currentFrame]->setPosition(pos);
}
void Animation::Update()
{
	if (clock.getElapsedTime().asMilliseconds() >= 100)
	{
		if (!pause)
		{
			currentFrame++;
		}
		// check to make sure not going to next set of frames
		//if top row is down, second row left, third row right, forth row up
		if (up)//9-11
		{
			if (currentFrame == 12)
			{
				currentFrame = 9;
			}
		}
		else if (down)//0-2
		{
			if (currentFrame == 3)//that would be next row
			{
				currentFrame = 0;
			}
		}
		else if (left)//3-5
		{
			if (currentFrame == 6)
			{
				currentFrame = 3;
			}
		}
		else if (right)//6-8
		{
			if (currentFrame == 9)
			{
				currentFrame = 6;
			}
		}
		else if (controlNPC)//0-5
		{
			if (currentFrame == 6)
			{
				currentFrame = 0;
			}
		}
		else if (psychoticRage)//6-11
		{
			if (currentFrame == 12)
			{
				currentFrame = 6;
			}
		}
		else if (triggerMadness)//12-17
		{
			if (currentFrame == 18)
			{
				currentFrame = 12;
				//pause = true;
			}
		}
		
		clock.restart();
	}
	
	
}
sf::Sprite* Animation::GetCurrentFrame()
{
	return frames[currentFrame];
}
void Animation::Control()
{
	currentFrame = 0;
	pause = false;
	controlNPC = true;
	psychoticRage = false;
	triggerMadness = false;
}
void Animation::Rage()
{
	currentFrame = 6;
	pause = false;
	controlNPC = false;
	psychoticRage = true;
	triggerMadness = false;
}
void Animation::Madness()
{
	currentFrame = 12;//was 12
	pause = false;
	controlNPC = false;
	psychoticRage = false;
	triggerMadness = true;
}
void Animation::Left()
{
	currentFrame = 3;
	left = true;
	right = false;
	down = false;
	up = false;
	pause = false;
}
void Animation::Right()
{
	currentFrame = 6;
	right = true;
	left = false;
	down = false;
	up = false;
	pause = false;
}
void Animation::Up()
{
	currentFrame = 9;
	up = true;
	right = false;
	down = false;
	left = false;
	pause = false;
}
void Animation::Down()
{
	currentFrame = 0;
	down = true;
	right = false;
	left = false;
	up = false;
	pause = false;
}
void Animation::Pause()
{
	pause = true;
}
