#include "Player.h"
#include <math.h>
#include <iostream>

Player::Player(sf::RenderWindow& inWindow)
	:
	window(inWindow)
{
	body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(40, 60));
	body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
	body.setPosition(1920 / 2, 1080 - 280);

	dashMeterBg.setSize(sf::Vector2f(420, 60));
	dashMeterBg.setPosition(30, 1080 - 30 - dashMeterBg.getSize().y);
	dashMeterBg.setFillColor(sf::Color::Black);
	dashMeter.setSize(sf::Vector2f(400 - (float)dashCdLeft / dashCd * 400, 40));
	dashMeter.setFillColor(sf::Color(255 * (1 - dashMeter.getSize().x / 400), 255 * dashMeter.getSize().x / 400, 0));
	dashMeter.setPosition(40, 1080 - 40 - dashMeter.getSize().y);
}

int Player::update()
{
	int state = 0;

	sf::Vector2f movement(0, 0);	
	
	//continue dash
	if (framesToEndDash > 0)
	{
		framesToEndDash -= 1;
		switch (dashDirection)
		{
		case 'w':
			//top
			movement.y = -dashSpeed;
			break;
		case 's':
			//bot
			movement.y = dashSpeed;
			break;
		case 'a':
			//left
			movement.x = -dashSpeed;
			break;
		case 'd':
			//right
			movement.x = dashSpeed;
			break;
		case 'q':
			//top-left
			movement.x = -dashSpeed / sqrt(2);
			movement.y = -dashSpeed / sqrt(2);
			break;
		case 'e':
			//top-right
			movement.x = dashSpeed / sqrt(2);
			movement.y = -dashSpeed / sqrt(2);
			break;
		case 'z':
			//bot-left
			movement.x = -dashSpeed / sqrt(2);
			movement.y = dashSpeed / sqrt(2);
			break;
		case 'c':
			//bot-right
			movement.x = dashSpeed / sqrt(2);
			movement.y = dashSpeed / sqrt(2);
			break;
		}
	}
	//move & start dash
	else
	{
		dashCdLeft = std::max(0, dashCdLeft - 1);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			movement.y -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			movement.y += speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			movement.x -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			movement.x += speed;
		}
		if (abs(movement.x) + abs(movement.y) == 2 * speed)
		{
			movement.x /= sqrt(2);
			movement.y /= sqrt(2);
		}

		//start dash
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (canDash && abs(movement.x) + abs(movement.y) != 0 && dashCdLeft == 0)
			{
				dashCdLeft = dashCd;
				framesToEndDash = framesDash;

				//decide dash direction
				if (movement.x > 0)
				{
					if (movement.y > 0)
					{
						dashDirection = 'c';
					}
					else if (movement.y < 0)
					{
						dashDirection = 'e';
					}
					else
					{
						dashDirection = 'd';
					}
				}
				else if (movement.x < 0)
				{
					if (movement.y > 0)
					{
						dashDirection = 'z';
					}
					else if (movement.y < 0)
					{
						dashDirection = 'q';
					}
					else
					{
						dashDirection = 'a';
					}
				}
				else
				{
					if (movement.y > 0)
					{
						dashDirection = 's';
					}
					else if (movement.y < 0)
					{
						dashDirection = 'w';
					}
				}
			}
			canDash = false;
		}
		else
		{
			canDash = true;
		}
	}

	dashMeter.setSize(sf::Vector2f(400 - (float)dashCdLeft / dashCd * 400, 40));
	dashMeter.setFillColor(sf::Color(255 * (1 - dashMeter.getSize().x / 400), 255 * dashMeter.getSize().x / 400, 0));

	body.move(movement);	
	collide();
	
	return state;
}

void Player::drawBody()
{
	window.draw(body);
}

void Player::drawWeapons()
{
	weapons[0].draw(window);
}

void Player::drawStats()
{
	window.draw(dashMeterBg);
	window.draw(dashMeter);
}

void Player::collide()
{
	//collide with left/right
	if (body.getPosition().x + body.getSize().x / 2 > 1920)
	{
		body.setPosition(1920 - body.getSize().x/2, body.getPosition().y);
	}
	else if (body.getPosition().x - body.getSize().x / 2 < 0)
	{
		body.setPosition(body.getSize().x / 2, body.getPosition().y);
	}

	//collide with bot/top
	if (body.getPosition().y + body.getSize().y / 2 > 936)
	{
		body.setPosition(body.getPosition().x, 936 - body.getSize().y / 2);
	}
	else if (body.getPosition().y - body.getSize().y / 2 < 60)
	{
		body.setPosition(body.getPosition().x, 60 + body.getSize().y / 2);
	}

	//collide with curves
	float dist = sqrt(pow(1920 / 2 - body.getPosition().x, 2) + pow(900 - body.getPosition().y, 2));	
	float bodyToVertex = sqrt(pow(body.getSize().x / 2, 2) + pow(body.getSize().y / 2, 2));
	if (dist + bodyToVertex > 1000)
	{
		float angbody = atan((900 - body.getPosition().y) / (1920 / 2 - body.getPosition().x));
		if (angbody < 0)
		{
			angbody = 3.1415 + angbody;
		}
		body.setPosition(1920/2 - cos(angbody) * (1000 - bodyToVertex), 900 - sin(angbody) * (1000 - bodyToVertex));
	}
}