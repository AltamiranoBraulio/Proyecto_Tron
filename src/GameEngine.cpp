
#include <iostream>
#include "GameEngine.hpp"

using namespace sf;

void GameEngine::run(int mode) {

    //set board and bar
    setBoardAndBar();

    //sprites for background and players textures
    Sprite Background(board.background);
    Sprite Player1(board.color1);
    Sprite Player2(board.color2);
    Player1.setScale((float) board.size / 16, (float) board.size / 16);
    Player2.setScale((float) board.size / 16, (float) board.size / 16);
    Background.setScale((float) board.size / 16, (float) board.size / 16);

    //create window and init players
    RenderWindow window(VideoMode(board.W * board.size, board.H * board.size), "TronGame");
    initPlayers();

    //delay for keyboard presses
    float timer = 0, delay = 0.075;
    Clock clock;
    float countdown = gameTime;

    int x1 = board.size, y1 = 0, x2 = -board.size, y2 = 0;

    while (window.isOpen()) {

        Event event{};
        while (window.pollEvent(event)) { if (event.type == Event::Closed) { window.close(); }}

        //update wins, covered tiles and timer
        bar.updateTexts(player1, player2, countdown);

        if (mode == 0) { x1 = 0, y1 = 0, x2 = 0, y2 = 0; }

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        countdown -= time;

        if (mode == 0 && countdown <= 0) {
            checkWinner();
            nextRound(x1, x2, y1, y2, mode);
            clock.restart();
            countdown = gameTime;
            continue;
        }
        updateMove(x1, x2, y1, y2);

        if (timer > delay) {
            moveHandle(x1, x2, y1, y2);
            if (checkCollision(x1, x2, y1, y2)) {
                nextRound(x1, x2, y1, y2, mode);
                countdown = gameTime;
            }
            saveTrace();
            timer = 0;
        }

        window.clear();

        //drawing background
        for (int i = 0; i < board.H; i++) {
            for (int k = 0; k < board.W; k++) {
                if (board.traceArray[i][k] == 0) {
                    Background.setPosition((float) (k * board.size), (float) (i * board.size));
                    window.draw(Background);
                } else if (board.traceArray[i][k] == 1) {
                    Player1.setPosition((float) (k * board.size), (float) (i * board.size));
                    window.draw(Player1);
                } else if (board.traceArray[i][k] == 2) {
                    Player2.setPosition((float) (k * board.size), (float) (i * board.size));
                    window.draw(Player2);
                }

            }
        }
        //drawing players
        Player1.setPosition((float) player1.xPosition, (float) player1.yPosition);
        window.draw(Player1);
        Player2.setPosition((float) player2.xPosition, (float) player2.yPosition);
        window.draw(Player2);

        window.draw((this->bar.p1Score));
        window.draw((this->bar.p2Score));
        if (mode == 0) {
            window.draw((this->bar.p1Covered));
            window.draw((this->bar.p2Covered));
            window.draw((this->bar.timer));
        }
        window.display();
    }
}

//listening if players using keys for moving
void GameEngine::updateMove(int &x1, int &x2, int &y1, int &y2) const {

    //printf("test");
    //player1 moves with WSDA keys
    if (Keyboard::isKeyPressed(Keyboard::A) && x1 != board.size) { x1 = -board.size, y1 = 0; }
    if (Keyboard::isKeyPressed(Keyboard::D) && x1 != -board.size) { x1 = board.size, y1 = 0; }
    if (Keyboard::isKeyPressed(Keyboard::W) && y1 != board.size) { x1 = 0, y1 = -board.size; }
    if (Keyboard::isKeyPressed(Keyboard::S) && y1 != -board.size) { x1 = 0, y1 = board.size; }

    //player2 moves with arrow keys
    if (Keyboard::isKeyPressed(Keyboard::Left) && x2 != board.size) { x2 = -board.size, y2 = 0; }
    if (Keyboard::isKeyPressed(Keyboard::Right) && x2 != -board.size) { x2 = board.size, y2 = 0; }
    if (Keyboard::isKeyPressed(Keyboard::Up) && y2 != board.size) { x2 = 0, y2 = -board.size; }
    if (Keyboard::isKeyPressed(Keyboard::Down) && y2 != -board.size) { x2 = 0, y2 = board.size; }

}

//random player start positions
void GameEngine::initPlayers() {
    this->player1.changePosition(board.W * board.size / 5, board.H * board.size / 2);
    this->player2.changePosition(board.W * board.size - board.W * board.size / 5, board.H * board.size / 2);
    this->player1.covered = 0;
    this->player2.covered = 0;
}

bool GameEngine::checkCollision(int &x1, int &x2, int &y1, int &y2) {
    //handle collisions
    if (board.traceArray[player1.yPosition / board.size][player1.xPosition / board.size] == 1 && x1 + y1 != 0 ||
        board.traceArray[player1.yPosition / board.size][player1.xPosition / board.size] == 2) {
        player2.score++;
        return true;
    }
    if (board.traceArray[player2.yPosition / board.size][player2.xPosition / board.size] == 2 && x2 + y2 != 0 ||
        board.traceArray[player2.yPosition / board.size][player2.xPosition / board.size] == 1) {
        player1.score++;
        return true;
    }
    //handle frontal collision == both get score
    if (player1.xPosition == player2.xPosition && player1.yPosition == player2.yPosition) {
        player1.score++;
        player2.score++;
        return true;
    }

    return false;
}

void GameEngine::saveTrace() {
    //filling array for drawing player's traces
    if (board.traceArray[player1.yPosition / board.size][player1.xPosition / board.size] == 0) {
        board.traceArray[player1.yPosition / board.size][player1.xPosition / board.size] = 1;
        player1.covered++;
    }

    if (board.traceArray[player2.yPosition / board.size][player2.xPosition / board.size] == 0) {
        board.traceArray[player2.yPosition / board.size][player2.xPosition / board.size] = 2;
        player2.covered++;
    }
}

void GameEngine::checkWinner() {
    //check who won by covering more board tiles
    //*checked only in covered mode*
    if (player1.covered > player2.covered) { player1.score++; }
    else if (player2.covered > player1.covered) { player2.score++; }
}

void GameEngine::nextRound(int &x1, int &x2, int &y1, int &y2, int mode) {
    //reset data for next round
    //sleep(seconds(3));
    initPlayers();
    if (mode == 0) {
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
    }
    board.traceArray = Board::create2DArray(board.W, board.H);
}

void GameEngine::moveHandle(int &x1, int &x2, int &y1, int &y2) {
    //change position
    player1.xPosition += x1;
    player1.yPosition += y1;
    player2.xPosition += x2;
    player2.yPosition += y2;

    board.boardWrapping(player1, player2);

}

void GameEngine::setBoardAndBar() {
    //set board and bar properties
    board.loadTextures();
    bar.setTextProperties();
    bar.p1Score.setPosition(20, 0);
    bar.p2Score.setPosition((float) (board.W * board.size - 120), 0);
    bar.p1Covered.setPosition(15, 30);
    bar.p2Covered.setPosition((float) (board.W * board.size - 115), 30);
    bar.timer.setPosition((float) (board.W * board.size / 2.0 - 65), 0);
}














