#include "Player.h"
#include <math.h>
#include <iostream>

Player::Player()
{
	body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(50, 70));
	body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
	body.setPosition(1920 / 2, 1080 - 280);
}

void Player::update()
{
	sf::Vector2f movement(0, 0);	
	
	//continue dash
	if (framesToEndDash > 0)
	{
		framesToEndDash -= 1;
		switch (dashDirection)
		{
		case 'w':
			if (!collideLeft && !collideRight)
			{
				movement.y = -dashSpeed;
			}
			else
			{
				framesToEndDash = 0;
			}
			break;
		case 's':
			movement.y = dashSpeed;
			break;
		case 'a':
			if (!collideLeft)
			{
				movement.x = -dashSpeed;
			}
			else
			{
				framesToEndDash = 0;
			}
			break;
		case 'd':
			if (!collideRight)
			{
				movement.x = dashSpeed;
			}
			else
			{
				framesToEndDash = 0;
			}
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

		if (collideLeft)
		{
			movement.x = std::max(movement.x, 0.f);
			movement.y = std::max(movement.y, 0.f);
		}
		else if (collideRight)
		{
			movement.x = std::min(movement.x, 0.f);
			movement.y = std::max(movement.y, 0.f);
		}

		//start dash
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (canDash && abs(movement.x) + abs(movement.y) != 0 && dashCdLeft == 0)
			{
				dashCdLeft = dashCd;
				framesToEndDash = framesDash;
				if (movement.x == 0)
				{
					framesToEndDash *= 0.8;
					if (movement.y > 0)
					{
						dashDirection = 's';
					}
					else
					{
						dashDirection = 'w';
					}
				}
				else if (movement.x > 0)
				{
					dashDirection = 'd';
				}
				else
				{
					dashDirection = 'a';
				}
			}
			canDash = false;
		}
		else
		{
			canDash = true;
		}
	}

	//apply movement
	body.move(movement);	
	
	//collide
	collide();
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::collide()
{
	if (body.getPosition().x + body.getSize().x / 2 > 1920)
	{
		body.setPosition(1920 - body.getSize().x/2, body.getPosition().y);
	}
	else if (body.getPosition().x - body.getSize().x / 2 < 0)
	{
		body.setPosition(body.getSize().x / 2, body.getPosition().y);
	}

	if (body.getPosition().y + body.getSize().y / 2 > 900)
	{
		body.setPosition(body.getPosition().x, 900 - body.getSize().y / 2);
	}
	else if (body.getPosition().y - body.getSize().y / 2 < 0)
	{
		body.setPosition(body.getPosition().x, body.getSize().y / 2);
	}

	collideLeft = false;
	collideRight = false;
	//collide with arena left and right part
	if (body.getPosition().x < 1920/2)
	{
		sf::Vector2f topLeft = body.getPosition() - sf::Vector2f(body.getSize().x / 2, body.getSize().y / 2);
		float distTopLeft = sqrt(std::pow(1920 / 2 - topLeft.x, 2) + std::pow(900 - topLeft.y, 2));
		if (distTopLeft > 1000)
		{
			collideLeft = true;
			if (distTopLeft > 1010)
			{				
				float bodyToVertex = sqrt(pow(body.getSize().x / 2, 2) + pow(body.getSize().y / 2, 2));
				float angTopLeft = atan((900 - topLeft.y) / (1920 / 2 - topLeft.x));
				body.setPosition(1920/2 - cos(angTopLeft) * (1000 - bodyToVertex), 900 - sin(angTopLeft) * (1000 - bodyToVertex));
			}
		}
	}
	else
	{
		sf::Vector2f topRight = body.getPosition() - sf::Vector2f(-body.getSize().x / 2, body.getSize().y / 2);
		float distTopRight = sqrt(std::pow(1920 / 2 - topRight.x, 2) + std::pow(900 - topRight.y, 2));
		if (distTopRight > 1000)
		{
			collideRight = true;
			if (distTopRight > 1010)
			{
				float bodyToVertex = sqrt(pow(body.getSize().x / 2, 2) + pow(body.getSize().y / 2, 2));
				float angTopRight = atan((900 - topRight.y) / (1920 / 2 - topRight.x));
				body.setPosition(1920 / 2 - cos(angTopRight) * (1000 - bodyToVertex), 900 - sin(angTopRight) * (1000 - bodyToVertex));
			}
		}
	}
}