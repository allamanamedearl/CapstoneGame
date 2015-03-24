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

	hintAnger = false;
	hintMad = false;
	hintControl = false;

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
	if (hintAnger)
	{
		
		hintBox2.setFillColor(sf::Color::Transparent);
		hintBox2.setOutlineColor(sf::Color::Yellow);
		hintBox2.setOutlineThickness(5.0f);
		hintBox2.setPosition(sf::Vector2f(rageBar.GetPosition().x - 150, rageBar.GetPosition().y-5.0f));
		hintBox2.setSize(sf::Vector2f(200.0f, rageBar.GetSize().y+10.0f));
	}
	if (hintControl)
	{
		hintBox1.setFillColor(sf::Color::Transparent);
		hintBox1.setOutlineColor(sf::Color::Yellow);
		hintBox1.setOutlineThickness(5.0f);
		hintBox1.setPosition(sf::Vector2f(controlBar.GetPosition().x - 150, controlBar.GetPosition().y - 5.0f));
		hintBox1.setSize(sf::Vector2f(200.0f, controlBar.GetSize().y + 10.0f));
	}
	if (hintMad)
	{
		hintBox3.setFillColor(sf::Color::Transparent);
		hintBox3.setOutlineColor(sf::Color::Yellow);
		hintBox3.setOutlineThickness(5.0f);
		hintBox3.setPosition(sf::Vector2f(madBar.GetPosition().x - 150, madBar.GetPosition().y - 5.0f));
		hintBox3.setSize(sf::Vector2f(200.0f, madBar.GetSize().y + 10.0f));
	}		   
	
	
	
}
void Gui::Draw(sf::RenderWindow *window)
{
	window->setView(guiView);
	window->draw(background);
	madBar.Draw(window);
	rageBar.Draw(window);
	controlBar.Draw(window);
	if (hintAnger)
	{
		window->draw(hintBox2);
	}
	if (hintControl)
	{
		window->draw(hintBox1);
	}
	if (hintMad)
	{
		window->draw(hintBox3);
	}
}
