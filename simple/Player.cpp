#include "Player.h"
#include <math.h>
#include <iostream>

Player::Player()
{
	body.setFillColor(sf::Color::Red);
	body.setSize(sf::Vector2f(40, 60));
	body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
	body.setPosition(1920 / 2, 1080 - 280);
	lastPos = body.getPosition();

	dashMeterBg.setSize(sf::Vector2f(420, 60));
	dashMeterBg.setPosition(30, 1080 - 30 - dashMeterBg.getSize().y);
	dashMeterBg.setFillColor(sf::Color::Black);
	dashMeter.setSize(sf::Vector2f(400 - (float)dashCdLeft / dashCd * 400, 40));
	dashMeter.setFillColor(sf::Color(255 * (1 - dashMeter.getSize().x / 400), 255 * dashMeter.getSize().x / 400, 0));
	dashMeter.setPosition(40, 1080 - 40 - dashMeter.getSize().y);

	hitbox.loadFromFile("resources/hitbox.png");
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

	dashMeter.setSize(sf::Vector2f(400 - (float)dashCdLeft / dashCd * 400, 40));
	dashMeter.setFillColor(sf::Color(255 * (1 - dashMeter.getSize().x / 400), 255 * dashMeter.getSize().x / 400, 0));

	body.move(movement);	
	collide();

	lastPos = body.getPosition();
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(body);

	window.draw(dashMeterBg);
	window.draw(dashMeter);
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

	if (body.getPosition().y + body.getSize().y / 2 > 1080)
	{
		body.setPosition(body.getPosition().x, 1080 - body.getSize().y / 2);
	}
	else if (body.getPosition().y - body.getSize().y / 2 < 0)
	{
		body.setPosition(body.getPosition().x, body.getSize().y / 2);
	}

	/*collideLeft = false;
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
	}*/

	int left = (body.getPosition().x - body.getSize().x / 2) / 4;
	int top = (body.getPosition().y - body.getSize().y / 2) / 4;

	while (hitbox.getPixel(left, top).r > 250)
	{
		float xBlock = left * 4;
		float yBlock = top * 4;
		float lastTop = (lastPos.y - body.getSize().y / 2);
		float lastLeft = (lastPos.x - body.getSize().x / 2);

		float xDiff = abs(xBlock - lastLeft);
		float yDiff = abs(yBlock - lastTop);

		if (xDiff > yDiff)
		{
			body.setPosition(xBlock + 4 + body.getSize().x / 2, body.getPosition().y);
		}
		else
		{
			body.setPosition(body.getPosition().x, yBlock + 4 + body.getSize().y / 2);
		}

		left = (body.getPosition().x - body.getSize().x / 2) / 4;
		top = (body.getPosition().y - body.getSize().y / 2) / 4;
	}
	
	/*
	you start from the unmoved position, you move one block towards the moved position, you se if it's empty. 
	if it is, you try mooving one more block, if it isnt, you return to the previus position, to the nearest multiple of 4
	*/
}