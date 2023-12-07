#pragma once
#ifndef TRONGAME_PLAYER_H
#define TRONGAME_PLAYER_H

class Player
{

public:
    int xPosition;
    int yPosition;
    int score;
    int covered;

    Player() = default;
    ;

    void changePosition(int x, int y);
};

#endif // TRONGAME_PLAYER_H
