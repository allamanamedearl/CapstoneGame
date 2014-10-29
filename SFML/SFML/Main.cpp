#include <Windows.h>
#include <SFML/Graphics.hpp>
#include "Engine.h"
int main()
{
	Engine* engine = new Engine();
	try
	{
		engine->Start();
	}
	catch (char* e)
	{
		MessageBoxA(NULL, e, "Exception Occurred",MB_OK | MB_ICONERROR);
	}
	/*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;*/
}