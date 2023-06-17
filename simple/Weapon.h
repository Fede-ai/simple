#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

class Weapon
{
public:
    Weapon(int inType);
    int update();
    void draw(sf::RenderWindow& window);

private:
    int type;
    std::vector<sf::RectangleShape> projectiles;
};