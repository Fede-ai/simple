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
	//to draw circle
	//sf::Image ok;
	//ok.create(1920 / 4, 1080 / 4);
	//for (int i = 0; i < 1800; i++)
	//{
	//	float xPoint = cos(i / 1800.f * 3.1415) * 250.f;
	//	float yPoint = sin(i / 1800.f * 3.1415) * 250.f;
	//
	//	int x = 1920 / 8 + xPoint;
	//	int y = 900 / 4 - yPoint;
	//	if (x >= 0 && x < 1920 / 4 && y >= 0 && y < 1080 / 4)
	//	{
	//		ok.setPixel(x, y, sf::Color::Blue);
	//	}
	//}
	//ok.saveToFile("C:/Users/matte/Desktop/ok.png");
	//while (true) {}

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

	//draw player's stats
	player.drawStats();
}