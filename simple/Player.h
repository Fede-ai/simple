#pragma once
#include "SFML/Graphics.hpp"

class Player
{
public:
	Player();
	void update();
	void draw(sf::RenderWindow& window);

private:
	void collide();
	sf::RectangleShape body;
	sf::Vector2f lastPos;
	sf::Image hitbox;

	bool collideLeft = false;
	bool collideRight = false;

	const int speed = 6;
	const int dashSpeed = 25;
	const int framesDash = 10;
	const int dashCd = 60;
	int dashCdLeft = 0;
	bool canDash = false;
	int framesToEndDash = 0;
	char dashDirection = ' '; //'w', 'a', 's', 'd'

	sf::RectangleShape dashMeter;
	sf::RectangleShape dashMeterBg;
};