#include <iostream>
#include <vector>

using namespace std;

// Funtion to draw the tic-tac-toe board
void drawBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j =0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if player has won
bool checkWin(const vector<vector<char>>& board, char player) {
    //cheecks rows
    for (int i = 0; i <3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    }

    // Check colums
        for (int j = 0; j < 3; j++) {
            if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
                return true;
        }
    
    // Check diagnals
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
            return true;

        if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
            return true;

        return false;
}

    // Function to play the tic tac toe game
    void playGame() {
        vector<vector<char>> board(3, vector<char>(3, ' ')); // Creates a 3x3 empty board
        char currentPlayer = 'X';
        int row, col;

        while (true) {
            cout << "Player " << currentPlayer << ", enter your move (row and colum): ";
            cin >> row >> col;

            if (row < 0 || row >= 3 || col < 0 || col >= 3) {
                cout << "Invalid move. Try again!" << endl;
                continue;
            }

            if (board[row][col] != ' ') {
                cout << "That position is already occupied. Try again!" << endl;
                continue;
            }

            board[row][col] = currentPlayer;
            drawBoard(board);

            if (checkWin(board, currentPlayer)) {
                cout << "Player " << currentPlayer << " wins!" << endl;
                break;
            }

            // Check for draw
            bool isBoardFull = true;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        isBoardFull = false;
                        break;
                    }
                }
                if (!isBoardFull) {
                    break;
                }
            }
            if (isBoardFull) {
                cout << "It's a draw!" << endl;
                break;
            }

            // Switch players
            currentPlayer = (currentPlayer == 'X') ? '0' : 'X';
        }
    }

    int main() {
        cout << "Welcome to the tic tac toe!" << endl;
        playGame();
        return 0;
    }