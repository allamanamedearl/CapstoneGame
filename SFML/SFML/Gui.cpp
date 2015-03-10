#include "Gui.h"


Gui::Gui(sf::Texture *texture,int screenWidth, int screenHeight)
{
	background.setTexture(*texture, true);
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
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
	

	rageBar = Bar(sf::Vector2f(background.getTextureRect().width - 280.0f, screenHeight - 80.0f), sf::Vector2f(15.0f, 60.0f), sf::Color::Red);
	controlBar = Bar(sf::Vector2f(background.getTextureRect().width - 490.0f, screenHeight - 80.0f), sf::Vector2f(15.0f, 60.0f), sf::Color::Cyan);
}
void Gui::Update()
{
	madBar.Update();
	rageBar.Update();
	controlBar.Update();
}
void Gui::Draw(sf::RenderWindow *window)
{
	window->setView(guiView);
	window->draw(background);
	madBar.Draw(window);
	rageBar.Draw(window);
	controlBar.Draw(window);
}
