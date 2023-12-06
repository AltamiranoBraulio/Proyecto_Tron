#pragma once
#include "Player.hpp"

void Player::changePosition(int newX, int newY)
{
    this->xPosition = newX;
    this->yPosition = newY;
}
