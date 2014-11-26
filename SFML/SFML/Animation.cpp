#include "Animation.h"

Animation::Animation()
{
	up = false;
	down = true;
	left = false;
	right = false;
	currentFrame = 0;
}
Animation::~Animation()
{

}
void Animation::SetFrames(sf::Texture *sheet, int sizeX,int sizeY, int row, int column)
{
	for (int y = 0; y < column; y++)
	{
		for (int x = 0; x < row; x++)
		{
			sf::Sprite temp= sf::Sprite(*sheet, sf::IntRect(x *sizeX, y*sizeY, sizeX, sizeY));
			frames.push_back(&temp);
		}
	}
}
void Animation::SetPosition(sf::Vector2f pos)
{
	frames[currentFrame]->setPosition(pos);
}
void Animation::Update()
{
	currentFrame++;
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
	
}
sf::Sprite* Animation::GetCurrentFrame()
{
	return frames[currentFrame];
}
void Animation::Left()
{
	left = true;
	right = false;
	down = false;
	up = false;
}
void Animation::Right()
{
	right = true;
	left = false;
	down = false;
	up = false;
}
void Animation::Up()
{
	up = true;
	right = false;
	down = false;
	left = false;
}
void Animation::Down()
{
	down = true;
	right = false;
	left = false;
	up = false;
}
