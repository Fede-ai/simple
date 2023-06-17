#pragma once
#include "SFML/Graphics.hpp"
#include "Weapon.h"

class Player
{
public:
	Player(sf::RenderWindow& inWindow);
	int update();
	void drawBody();
	void drawWeapons();
	void drawStats();

private:
	std::vector<Weapon> weapons;
	void collide();
	sf::RectangleShape body;
	sf::RenderWindow& window;

	const int speed = 6;
	const int dashSpeed = 25;
	const int framesDash = 10;
	const int dashCd = 60;
	int dashCdLeft = 0;
	bool canDash = false;
	int framesToEndDash = 0;
	char dashDirection = ' '; //w, a, s, d, q, e, z, c

	sf::RectangleShape dashMeter;
	sf::RectangleShape dashMeterBg;
};