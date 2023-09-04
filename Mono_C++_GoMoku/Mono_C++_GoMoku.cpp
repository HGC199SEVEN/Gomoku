#include <iostream>
#include <string>
using namespace std;

const int BOARD_SIZE = 20;
char board[BOARD_SIZE][BOARD_SIZE];

void initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = '.';
        }
    }
}

void displayBoard() {
    cout << "   ";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        string temp = to_string(i);
        if (temp.size() < 2) {
            cout << to_string(i) << " ";
        }
        else {
            cout << to_string(i);
        }
    }
    cout << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        string temp = to_string(i);
        if (temp.size() < 2) {
            cout << to_string(i) << "  ";
        }
        else {
            cout << to_string(i)<<" ";
        }
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isValidMove(int row, int col) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }
    if (board[row][col] != '.') {
        return false;
    }
    return true;
}

bool isWinningMove(int row, int col, char player) {
    int dx[] = { 0, 1, 1, 1 };
    int dy[] = { 1, 0, 1, -1 };

    for (int i = 0; i < 4; i++) {
        int count = 1;
        int newRow = row + dx[i];
        int newCol = col + dy[i];

        while (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE &&
            board[newRow][newCol] == player) {
            count++;
            newRow += dx[i];
            newCol += dy[i];
        }

        newRow = row - dx[i];
        newCol = col - dy[i];
        while (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE &&
            board[newRow][newCol] == player) {
            count++;
            newRow -= dx[i];
            newCol -= dy[i];
        }

        if (count >= 5) {
            return true;
        }
    }

    return false;
}

bool isBoardFull() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == '.') {
                return false;
            }
        }
    }
    return true;
}

void playGame() {
    char currentPlayer = 'X';
    int row, col;
    initializeBoard();
    while (true) {
        displayBoard();
        cout << "It's Player " << currentPlayer << "'s turn. Enter the row and column (0-" << BOARD_SIZE - 1 << "): ";
        cin >> row >> col;

        if (isValidMove(row, col)) {
            board[row][col] = currentPlayer;

            if (isWinningMove(row, col, currentPlayer)) {
                displayBoard();
                cout << "Player " << currentPlayer << " wins!" << endl;
                break;
            }

            if (isBoardFull()) {
                displayBoard();
                cout << "The game ended in a tie!" << endl;
                break;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
        else {
            cout << "Invalid move. Try again." << endl;
        }
    }
}

int main() {
    playGame();
    return 0;
}