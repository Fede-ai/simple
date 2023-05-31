#include "Player.h"
#include <math.h>

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
			movement.y = -dashSpeed;
			break;
		case 's':
			movement.y = dashSpeed;
			break;
		case 'a':
			movement.x = -dashSpeed;
			break;
		case 'd':
			movement.x = dashSpeed;
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
}