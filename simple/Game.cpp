#include "Game.h"

Game::Game()
{
	window.create(sf::VideoMode(screenDim.x / 2, screenDim.x * 9 / 32), "simple", sf::Style::Close);
	window.setFramerateLimit(60);
	sf::View view(sf::Vector2f(1920/2, 1080/2), sf::Vector2f(1920, 1080));
	window.setView(view);

	arena.setRadius(1000);
	arena.setOrigin(arena.getRadius(), arena.getRadius());
	arena.setPosition(1920/2, 900);
}

void Game::run() 
{
	while (window.isOpen())
	{
		sf::Event windowEvents;
		while (window.pollEvent(windowEvents))
		{
			switch (windowEvents.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					if (canFullscreen)
					{
						if (isFullscreen)
						{
							window.create(sf::VideoMode(screenDim.x / 2, screenDim.x * 9 / 32), "simple", sf::Style::Close);
							window.setFramerateLimit(60);
							sf::View view(sf::Vector2f(1920 / 2, 1080 / 2), sf::Vector2f(1920, 1080));
							window.setView(view);
						}
						else
						{	
							window.create(sf::VideoMode(0, 0), "simple", sf::Style::Fullscreen);
							window.setFramerateLimit(60);
							sf::View view(sf::Vector2f(1920 / 2, 1080 / 2), sf::Vector2f(1920, 1080));
							window.setView(view);
						}
						isFullscreen = !isFullscreen;
					}
					canFullscreen = false;
				}
				else
				{
					canFullscreen = true;
				}
			}
		}

		window.clear();

		update();
		draw();

		window.display();
	}
}

int Game::update()
{
	int state = 0;

	player.update();

	
	return state;
}

void Game::draw()
{
	window.draw(arena);
	player.draw(window);
}