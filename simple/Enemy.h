#pragma once
#include "SFML/Graphics.hpp"

class Enemy {
private:
    sf::RectangleShape body; 
public:
    Enemy(int inType);
    int type;

    void update();
    void draw(); 
};