#include "pch.h"

#include "Utils/Log/ConsoleLog.h"
#include "Utils/Log/FileLog.h"

#include "SFML/Graphics.hpp"
#include "glad.h"

auto main(int argc, char** argv) -> int
{
	Utils::ConsoleLog::Init();
	Utils::ConsoleLog::Trace("Trace");
	Utils::ConsoleLog::Info("Info");
	Utils::ConsoleLog::Warn("Warn");
	Utils::ConsoleLog::Error("Error");

	Utils::FileLog::Log("temp.txt", "Testing {0}", 10);

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
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

}
