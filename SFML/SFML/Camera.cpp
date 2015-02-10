#include "Camera.h"


Camera::Camera(int w, int h, float speed)
{
	size.x = w;
	size.y = h;
	position.x = 0.0f;
	position.y = 0.0f;

	if (speed < 0.0f)
		speed = 0.0f;
	if (speed > 1.0f)
		speed = 1.0f;
	this->speed = speed;
}


Camera::~Camera()
{
}
//Moves camera to coordinates
void Camera::Move(int x, int y)
{
	position.x = (float)x;
	position.y = (float)y;
	target.x = (float)x;
	target.y = (float)y;
}
//centers camera at coordinates
void Camera::MoveCenter(int x, int y)
{
	x = x - (size.x / 2);
	y = y - (size.y / 2);

	position.x = (float)x;
	position.y = (float)y;
	target.x = (float)x;
	target.y = (float)y;
}
//sets Target to coordinates
void Camera::GoTo(int x, int y)
{
	target.x = (float)x;
	target.y = (float)y;
}
//centers target at coordinates
void Camera::GoToCenter(int x, int y)
{
	x = x - (size.x / 2);
	y = y - (size.y / 2);

	target.x = (float)x;
	target.y = (float)y;
}
//scrolls camera, moves it to target
//over time
void Camera::Update()
{
	//x and y distance and euclidean distance
	float x, y, d;

	//velocity magnitudes
	float vx, vy, v;

	//find x and y
	x = (float)(target.x - position.x);
	y = (float)(target.y - position.y);

	//if we're within 1 pixel of the target 
	//already just snap to target and stay
	//there, otherwise continue

	if ((x*x + y*y) <= 1)
	{
		position.x = target.x;
		position.y = target.y;
	}
	else
	{
		//distnce formula c = sqrt(a^2 + b^2)
		d = sqrt(x*x + y*y);

		//set velocity to move 1/60th of the 
		//distance to target

		v = (d*speed) / 60;
		//keep v at at least 1 otherwise it will
		//never get to target
		if (v < 1.0f)
			v = 1.0f;

		vx = x * (v / d);
		vy = y * (v / d);

		//update camera position
		position.x += vx;
		position.y += vy;
	}
}
void Camera::SetRenderingRange(int x, int y)
{
	SetPosition((int)position.x + x, (int)position.y + y);
}
bool Camera::CheckIfOnscreen(int x, int y, int tileSize, int screenWidth,int screenHeight)
{
	//check to see if a tile is on screen
	//camera width and height is set to fullsize of level
	if (x*tileSize +position.x>= position.x && x*tileSize +position.x < screenWidth && y*tileSize +position.y >= position.y && y*tileSize +position.y < screenHeight)
		return true;
	else
		return false;
}
sf::IntRect Camera::GetTileBounds(int tileSize)
{
	int x = (int)(position.x / tileSize);
	int y = (int)(position.y / tileSize);

	//+1 incase size/tileSize = 0
	int w = (int)(size.x / tileSize);//+ 2;
	int h = (int)(size.y / tileSize);//+ 2;

	//may need to add +1 if offset from tile
	if(x%tileSize!=0)
		w++;
	if(y%tileSize!=0)
		h++;
	return sf::IntRect(x, y, w, h);
}