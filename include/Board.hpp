

#ifndef TRONGAME_BOARD_H
#define TRONGAME_BOARD_H

#include "SFML/Graphics.hpp"
#include "Player.hpp"

using namespace sf;

class Board
{

public:
    // board parameters
    int W{};
    int H{};
    int size{};
    int **traceArray{};

    // textures
    Texture background;
    Texture color1;
    Texture color2;

    Board() = default;
    ;

    Board(int width, int height, int size);

    void loadTextures();

    static int **create2DArray(int width, int height);

    void boardWrapping(Player &player1, Player &player2) const;
};

#endif // TRONGAME_BOARD_H
