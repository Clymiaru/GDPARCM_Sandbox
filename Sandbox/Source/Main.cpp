#include "pch.h"

#include "Utils/Log/ConsoleLog.h"
#include "Utils/Log/FileLog.h"

#include "SFML/Graphics.hpp"
#include "glad.h"

#include "Utils/Log/Assert.h"

auto main(int argc, char** argv) -> int
{
	Utils::ConsoleLog::Init();

	sf::Window window(sf::VideoMode(1280, 720),
		"SFML OpenGL(glad) Integration!",
		sf::Style::Default,
		sf::ContextSettings(24));
	window.setVerticalSyncEnabled(true);

	ASSERT(window.setActive(true), "Window cannot be set to active!");
	
	gladLoadGL();

	bool isRunning = true;
	while (isRunning)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		glClearColor(1.0f, 0.0f, 0.0f ,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		window.display();
	}

}
