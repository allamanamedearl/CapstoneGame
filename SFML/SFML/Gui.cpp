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
	
}
void Gui::Update()
{

}
void Gui::Draw(sf::RenderWindow *window)
{
	window->setView(guiView);
	window->draw(background);
}