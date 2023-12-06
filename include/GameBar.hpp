
#ifndef TRONGAME_GAMEBAR_H
#define TRONGAME_GAMEBAR_H

#include "SFML/Graphics.hpp"
#include "Player.hpp"

using namespace sf;

class GameBar {

public:
    Font font;
    Text p1Score;
    Text p2Score;
    Text p1Covered;
    Text p2Covered;
    Text timer;

    GameBar();

    static Font loadFont();

    void updateTexts(Player &player1, Player &player2, float time);

    void setTextProperties();
};

#endif //TRONGAME_GAMEBAR_H
