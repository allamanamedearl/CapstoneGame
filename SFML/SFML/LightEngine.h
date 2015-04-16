#pragma once
#include"Light.h"
#include"Block.h"
#include<vector>
#include<SFML\Graphics\RenderTarget.hpp>
#include<SFML\Graphics\Shape.hpp>
#include<SFML\Graphics\RectangleShape.hpp>

class LightEngine
{
public:
	LightEngine();
	~LightEngine();
	void InitLights();
	void DrawLights(sf::RenderTarget &rt);
	std::vector <Light>Lights;//container for lights
	std::vector<Block>Blocks;//container for blocks
	sf::VertexArray allLights;
private:
	void ShineLight(Light &l);
	static const float Distance(const sf::Vector2f &p1, const sf::Vector2f &p2);
	static const sf::Vector2f GetCenter(const sf::FloatRect &fr);//get center of rectangle

	struct FindDistance//if a light's radius manages to intersect multiple blocks, we need to find the sortest distance to shorten the light
	{
		FindDistance();
		float shortest;
		bool LightHitsBlock(Light &l, Block &b, const float curr_ang, float &refLength);
		bool start;//to get the first distance reference
	};
	FindDistance findDis;//haha
};

