#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>

using namespace std;

const int width = 30;
const int height = 20;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class TronGame {
private:
    int player1X, player1Y;
    int player2X, player2Y;
    char trail[width][height];
    Direction player1Dir, player2Dir;
    int player1Score, player2Score;

public:
     TronGame() {
        player1X = width / 4;
        player1Y = height / 2;
        player2X = 3 * width / 4;
        player2Y = height / 2;
        player1Dir = RIGHT;  // Direccion inicial del jugador 1
        player2Dir = LEFT;   // Direccion inicial del jugador 2
        player1Score = player2Score = 0; // Inicializar puntajes
        // Inicializar el camino como vacío
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                trail[i][j] = false;
            }
        }
    }

    void SetConsoleColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void ResetConsoleColor() {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); // Restaurar el color predeterminado
    }

    void Draw() {
        system("cls");
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    cout << "#";

                if (i == player1Y && j == player1X) {
                    SetConsoleColor(9); // Azul
                    cout << "1";
                    ResetConsoleColor();
                    trail[j][i] = 'x';
                } else if (i == player2Y && j == player2X) {
                    SetConsoleColor(14); // Naranja
                    cout << "2";
                    ResetConsoleColor();
                    trail[j][i] = 'E';
                } else if (trail[j][i] == 'x') {
                    SetConsoleColor(9); // Azul
                    cout << "x";
                    ResetConsoleColor();
                } else if (trail[j][i] == 'E') {
                    SetConsoleColor(14); // Naranja
                    cout << "E";
                    ResetConsoleColor();
                } else {
                    cout << " ";
                }

                if (j == width - 1)
                    cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        cout << "Player 1 Score: " << player1Score << "   Player 2 Score: " << player2Score << endl;
    }

       void Input() {
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
            case 'a':
                player1Dir = LEFT;
                break;
            case 'd':
                player1Dir = RIGHT;
                break;
            case 'w':
                player1Dir = UP;
                break;
            case 's':
                player1Dir = DOWN;
                break;
            case 'i':
                player2Dir = UP;
                break;
            case 'j':
                player2Dir = LEFT;
                break;
            case 'l':
                player2Dir = RIGHT;
                break;
            case 'k':
                player2Dir = DOWN;
                break;
            }
        }
    }

    void MovePlayers() {
        // Mover al jugador 1 según la dirección
        switch (player1Dir) {
        case LEFT:
            player1X--;
            break;
        case RIGHT:
            player1X++;
            break;
        case UP:
            player1Y--;
            break;
        case DOWN:
            player1Y++;
            break;
        }

        // Mover al jugador 2 según la dirección
        switch (player2Dir) {
        case LEFT:
            player2X--;
            break;
        case RIGHT:
            player2X++;
            break;
        case UP:
            player2Y--;
            break;
        case DOWN:
            player2Y++;
            break;
        }

        // Si algún jugador choca con la pared o con el camino, actualizar puntajes
        if (player1X < 0 || player1X >= width || player1Y < 0 || player1Y >= height || trail[player1X][player1Y]) {
            player2Score++;
            player1Dir = STOP;
        }

        if (player2X < 0 || player2X >= width || player2Y < 0 || player2Y >= height || trail[player2X][player2Y]) {
            player1Score++;
            player2Dir = STOP;
        }

        // Actualizar el camino marcado con 'x'
        trail[player1X][player1Y] = true;
        trail[player2X][player2Y] = true;
    }

    bool IsGameOver() {
        return player1Dir == STOP || player2Dir == STOP;
    }

    int getPlayer1Score() const {
        return player1Score;
    }

    int getPlayer2Score() const {
        return player2Score;
    }

    void ResetGame() {
        player1X = width / 4;
        player1Y = height / 2;
        player2X = 3 * width / 4;
        player2Y = height / 2;
        player1Dir = RIGHT;
        player2Dir = LEFT;
        // Inicializar el camino como vacío
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                trail[i][j] = false;
            }
        }
    }
};

int main() {
    char playAgain;
    TronGame game;

    do {
        while (!game.IsGameOver()) {
            game.Draw();
            game.Input();
            game.MovePlayers();

            // Agregar un retraso para reducir la velocidad de movimiento
#ifdef _WIN32
            Sleep(500);
#else
            usleep(500000);
#endif
        }

        cout << "Game Over!" << endl;
        cout << "Player 1 Score: " << game.getPlayer1Score() << "   Player 2 Score: " << game.getPlayer2Score() << endl;

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

        if (playAgain == 'y' || playAgain == 'Y') {
            game.ResetGame();
        }

    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

enum Direction {
    STOP,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class TronGame {
private:
    const int width = 20;
    const int height = 20;
    int player1X;
    int player1Y;
    int player2X;
    int player2Y;
    int player1Dir;
    int player2Dir;
    int player1Score;
    int player2Score;
    bool trail[20][20];

public:
    TronGame() {
        player1X = width / 4;
        player1Y = height / 2;
        player2X = 3 * width / 4;
        player2Y = height / 2;
        player1Dir = RIGHT;
        player2Dir = LEFT;
        player1Score = 0;
        player2Score = 0;
        // Inicializar el camino como vacío
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                trail[i][j] = false;
            }
        }
    }

    void Draw() {
        // Código para dibujar el juego
    }

    void Input() {
        // Código para capturar la entrada del usuario
    }

    void MovePlayers() {
        // Código para mover a los jugadores
    }

    bool IsGameOver() {
        return player1Dir == STOP || player2Dir == STOP;
    }

    int getPlayer1Score() const {
        return player1Score;
    }

    int getPlayer2Score() const {
        return player2Score;
    }

    void ResetGame() {
        player1X = width / 4;
        player1Y = height / 2;
        player2X = 3 * width / 4;
        player2Y = height / 2;
        player1Dir = RIGHT;
        player2Dir = LEFT;
        // Inicializar el camino como vacío
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                trail[i][j] = false;
            }
        }
    }
};

int main() {
    char playAgain;
    TronGame game;

    do {
        while (!game.IsGameOver()) {
            game.Draw();
            game.Input();
            game.MovePlayers();

            // Agregar un retraso para reducir la velocidad de movimiento
#ifdef _WIN32
            Sleep(500);
#else
            usleep(500000);
#endif
        }

        cout << "Game Over!" << endl;
        cout << "Player 1 Score: " << game.getPlayer1Score() << "   Player 2 Score: " << game.getPlayer2Score() << endl;

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

        if (playAgain == 'y' || playAgain == 'Y') {
            game.ResetGame();
        }

    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}
//comentario de prueba 
//comentario de prueba 2
//comentario de prueba 3

// comentario prueba 4 jmn