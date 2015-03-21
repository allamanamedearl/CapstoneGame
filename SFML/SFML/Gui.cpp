#include "Gui.h"
#include <iostream>


Gui::Gui(sf::Texture *texture,int screenWidth, int screenHeight)
{
	background.setTexture(*texture, true);
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	//powers
	triggerMadness=false;
	psychoticRage= false;
	controlNPC= false;

	madnessLength = 5000;//milliseconds = 5 seconds
	controlLength = 10000;
	rageLength = 5000;

}


Gui::~Gui()
{
}
void Gui::Init()
{//-100 height of texture
	guiView.reset(sf::FloatRect(0, screenHeight - background.getTextureRect().height, screenWidth, background.getTextureRect().height));
	guiView.setViewport(sf::FloatRect(0.0f, 0.8f, 1.0f, 0.2f));
	background.setPosition(sf::Vector2f(0, screenHeight - background.getTextureRect().height));
	
	madBar = Bar(sf::Vector2f(background.getTextureRect().width - 50.0f, screenHeight - 80.0f), sf::Vector2f(15.0f, 60.0f), sf::Color::Yellow);
	//madBar.SetScale(0.0f);

	rageBar = Bar(sf::Vector2f(background.getTextureRect().width - 280.0f, screenHeight - 80.0f), sf::Vector2f(15.0f, 60.0f), sf::Color::Red);
	controlBar = Bar(sf::Vector2f(background.getTextureRect().width - 490.0f, screenHeight - 80.0f), sf::Vector2f(15.0f, 60.0f), sf::Color::Cyan);
}
void Gui::Update(std::string activePows)
{
	if (activePows.find("c") != std::string::npos)//if there's a c in it
	{
		if (!controlNPC)
		{
			controlNPC = true;
			controlClock.restart();
		}
	}
	if (activePows.find("m") != std::string::npos)
	{
		if (!triggerMadness)
		{
			triggerMadness = true;
			madClock.restart();
		}
	}
	if (activePows.find("p") != std::string::npos)
	{
		if (!psychoticRage)
		{
			psychoticRage = true;
			rageClock.restart();
		}
	}
	if (controlNPC)//if control npc is reloading
	{
		controlTime = controlClock.getElapsedTime();
		if (controlTime.asMilliseconds() < controlLength)//so long as it's not over the reload time
		{
			controlBar.SetScale((float)controlTime.asMilliseconds() / (float)controlLength);
		}
		else
		{
			controlNPC = false; //control npc is fully reloaded
			controlBar.SetScale(1.0f);
		}
		controlBar.Update();
	}
	if (triggerMadness)//if madness is reloading
	{
		madTime = madClock.getElapsedTime();
		if (madTime.asMilliseconds() < madnessLength)//so long as it's not over the reload time
		{
			madBar.SetScale((float)madTime.asMilliseconds() / (float)madnessLength);	
		}
		else
		{
			triggerMadness = false; //trigger madness fully reloaded
			madBar.SetScale(1.0f);
		}
		madBar.Update();
	}
	if (psychoticRage)//if control npc is reloading
	{
		rageTime = rageClock.getElapsedTime();
		if (rageTime.asMilliseconds() < rageLength)//so long as it's not over the reload time
		{
			rageBar.SetScale((float)rageTime.asMilliseconds() / (float)rageLength);
		}
		else
		{
			psychoticRage = false; //control npc is fully reloaded
			rageBar.SetScale(1.0f);
		}
		rageBar.Update();
	}
	
	
	
}
void Gui::Draw(sf::RenderWindow *window)
{
	window->setView(guiView);
	window->draw(background);
	madBar.Draw(window);
	rageBar.Draw(window);
	controlBar.Draw(window);
}
