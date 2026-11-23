#include <iostream>
#include <limits>
#include <cctype>
using namespace std;

char board[3][3];
char player1 = 'X', player2 = 'O';
bool vsComputer = true;

//------------------------//
// UTILITY FUNCTIONS //
//------------------------//

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void initializeBoard() {
    char c = '1';
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = c++;
}

void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; ++i) {
        cout << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2)
            cout << " | ";
        }

        if (i < 2)
    cout << "\n-----------\n";
    }

    cout << "\n\n";
}

bool isMoveValid(int cell) {
    if (cell < 1 || cell > 9)
        return false;
    int row = (cell - 1) / 3;
    int col = (cell - 1) % 3;
    return (board[row][col] != 'X' && board[row][col] != 'O');
}

void playerMove(char symbol) {
    int cell;
    while (true) {
        cout << "Player " << symbol << " move (1-9): ";

        if (!(cin >> cell)) {
            cout << "Invalid input! Please enter numbers only.\n";
            clearInput();
            continue;
        }

        if (isMoveValid(cell)) {
            int row = (cell - 1) / 3;
            int col = (cell - 1) % 3;
            board[row][col] = symbol;
            break;
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }
}

bool checkWin(char symbol) {
    for (int i = 0; i < 3; ++i)
        if ((board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) ||
            (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)){
            return true;
            }
    if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
        (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol))
       {
           return true;
       }
    return false;
}

bool isDraw() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] != 'X' && board[i][j] != 'O')
               {
            return false;
               }
    return true;
}

//------------------------//
// SIMPLE AI LOGIC //
//------------------------//

void makeBestMove() {
    // 1. Try to win
    for (int i = 1; i <= 9; ++i) {
        if (isMoveValid(i)) {
            int row = (i - 1) / 3;
            int col = (i - 1) % 3;

            char backup = board[row][col];
            board[row][col] = player2;

            if (checkWin(player2))
                return;

            board[row][col] = backup; // undo
        }
    }

    // 2. Block opponent
    for (int i = 1; i <= 9; ++i) {
        if (isMoveValid(i)) {
            int row = (i - 1) / 3;
            int col = (i - 1) % 3;

            char backup = board[row][col];
            board[row][col] = player1;

            if (checkWin(player1)) {
                board[row][col] = player2; // block
                return;
            }

            board[row][col] = backup;
        }
    }

    // 3. Pick first available
    for (int i = 1; i <= 9; ++i) {
        if (isMoveValid(i)) {
            int row = (i - 1) / 3;
            int col = (i - 1) % 3;
            board[row][col] = player2;
            return;
        }
    }
}

//------------------------//
// MAIN GAME //
//------------------------//

int main() {
    char choice;
    do {
        initializeBoard();

        cout << "TIC TAC TOE\n";
        cout << "1. Player vs Computer\n";
        cout << "2. Player vs Player\n";

        int mode;
        while (true) {
            cout << "Select mode (1 or 2): ";

            if (!(cin >> mode)) {
                cout << "Invalid input! Enter 1 or 2.\n";
                clearInput();
                continue;
            }
            if (mode == 1 || mode == 2) break;
            cout << "Invalid selection. Try again.\n";
        }

        vsComputer = (mode == 1);

        while (true) {
            printBoard();
            playerMove(player1);

            if (checkWin(player1)) {
                printBoard();
                cout << "Player X wins!\n";
                break;
            }
            if (isDraw()) {
                printBoard();
                cout << "It's a draw!\n";
                break;
            }

            printBoard();
            if (vsComputer) {
                cout << "Computer is making a move...\n";
                makeBestMove();
            } else {
                playerMove(player2);
            }

            if (checkWin(player2)) {
                printBoard();
                if (vsComputer)
                    cout << "Computer wins!\n";
                else
                    cout << "Player O wins!\n";
                break;
            }
            if (isDraw()) {
                printBoard();
                cout << "It's a draw!\n";
                break;
            }
        }

        cout << "Play again? (Y/E): ";
        cin >> choice;
        choice = toupper(choice);

    } while (choice == 'Y');

    cout << "Thank you for playing!\n";
    return 0;
}
