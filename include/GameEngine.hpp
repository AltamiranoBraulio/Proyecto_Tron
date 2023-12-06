#pragma once
#ifndef TRONGAME_GAMEENGINE_H
#define TRONGAME_GAMEENGINE_H

#include <ctime>
#include <utility>
#include "Board.hpp"
#include "Player.hpp"
#include "GameBar.hpp"
#include "SFML/Graphics.hpp"

using namespace sf;

class GameEngine
{

    GameBar bar;
    Board board{};
    Player player1{};
    Player player2{};
    float gameTime;

public:
    explicit GameEngine(Board board, Player p1, Player p2, float time)
    {
        this->board = std::move(board);
        this->player1 = p1;
        this->player2 = p2;
        this->bar = GameBar();
        this->gameTime = time;
    }

    void run(int mode);

    void initPlayers();

    void updateMove(int &x1, int &x2, int &y1, int &y2) const;

    bool checkCollision(int &x1, int &x2, int &y1, int &y2);

    void saveTrace();

    void checkWinner();

    void nextRound(int &x1, int &x2, int &y1, int &y2, int mode);

    void moveHandle(int &x1, int &x2, int &y1, int &y2);

    void setBoardAndBar();
};

#endif // TRONGAME_GAMEENGINE_H
