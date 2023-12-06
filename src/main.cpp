#include <iostream>
#include "GameEngine.hpp"
#include "Menu.hpp"

int main() {
    std::cout << "Welcome in Tron Game !!!" << std::endl;
    //set board parameters
    Board board = Board(60, 34, 20);
    Menu menu((float) (board.size * board.W), (float) (board.size * board.H));
    //run menu window
    int mode = menu.startMenu();
    if (mode == -1 ) {printf("Menu closed!") ;return 0;}
    //init players and start game with selected mode
    Player player1 = Player();
    Player player2 = Player();
    GameEngine game = GameEngine(board, player1, player2, 40.f);
    game.run(mode);

    return 0;
}
