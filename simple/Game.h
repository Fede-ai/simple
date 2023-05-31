#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"

class Game
{
public:
	Game();
	void run();

private:
	int update();
	void draw();

	sf::Vector2i screenDim = sf::Vector2i(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	sf::RenderWindow window;
	bool isFullscreen = false;
	bool canFullscreen = false;

	sf::CircleShape arena;
	Player player;
};