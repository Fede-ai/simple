#include "Game.h"
#include <iostream>

Game::Game()
	:
	player(window)
{
	window.create(sf::VideoMode(screenDim.x / 2, screenDim.x * 9 / 32), "simple", sf::Style::Close);
	window.setFramerateLimit(60);
	sf::View view(sf::Vector2f(1920/2, 1080/2), sf::Vector2f(1920, 1080));
	window.setView(view);

	fieldTexture.loadFromFile("resources/field.png");
	field.setTexture(fieldTexture);
	field.setScale(4, 4);

	castleTexture.loadFromFile("resources/castle.png");
	castle.setTexture(castleTexture);
	castle.setScale(4, 4);
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
							window.create(sf::VideoMode(), "simple", sf::Style::Fullscreen);
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

	int playerState = player.update();
	
	return state;
}

void Game::draw()
{
	//draw field (grass)
	window.draw(field);

	//draw player
	player.drawBody();

	//draw castle
	window.draw(castle);

	//draw potential weapons/pojectiles
	player.drawWeapons();

	//draw player's stats
	player.drawStats();
}