#include "tictactwo.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm> // For sorting

using namespace std;

TicTacToe::TicTacToe() : lastMatchID(0) {
    readMatchHistory();
}

void TicTacToe:: saveMatchRecord(const MatchInfo& match) {
    ofstream outfile("match_data_two.txt", ios::app);

    if(outfile.is_open()) {
        outfile << "Match ID: " << match.matchID << "\n";
        outfile << match.player1 << " vs. " << match.player2 << "\n";
        for (int i = 0; i < 9; ++i) {
            outfile << setw(4) << match.gameBoard[i];
            if ((i + 1) % 3 == 0) outfile << "\n";
        }
            outfile << "--------------------------------------------\n";
            outfile.close();
            cout << "Watch record saved. \n";
    } else {
        cout << "Failed to open the file for writing.\n";
    }
}

void TicTacToe::readMatchHistory() {
    ifstream infile("match_data.txt");

    if (infile.is_open()) {
        matchHistory.clear(); // Clear the previous history
        string line;
        while (getline(infile,line)) {
            if (line.substr(0, 9) == "Match ID:") {
                int currentID = stoi(line.substr(10));
                MatchInfo match;
                match.matchID = currentID;
                getline(infile, line); // Read player names live
                stringstream ss(line);
                ss >> match.player1 >> ws >> ws >> match.player2;
                match.gameBoard.clear();
                char cell;
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        infile >> cell;
                        match.gameBoard.push_back(cell);
                    }
                }
                    matchHistory.push_back(match);
            }
        }
        infile.close();
    } else {
        cout << "Failed to open the file for reading. \n";
    }
}

void TicTacToe::displayMatchByID(int matchID) {
    for (const auto& match : matchHistory) {
        if (match.matchID == matchID) {
            cout << "Match ID: " << match.matchID << " vs. " << match.player2 <<"\n";
            cout << match.player1 << " vs. " << match.player2 << "\n";
            for (int i = 0; i < 3; ++i) {
                cout << setw(3) << match.gameBoard[i];
                if ((i + 1) % 3 == 0) cout << "\n";
            }
            cout << "---------------------------------\n";
            return;
        }
    }
        cout << "Match with ID " << matchID << " not found. \n"; 
}

void TicTacToe::displayBoard(const vector<char>& board) {
    for (int i = 0; i < 9; ++i) {
        cout << setw(3) << board[i];
        if ((i + 1) % 3 == 0) cout << "\n";
    }
}

void TicTacToe::playGame() {
    matchHistory.clear(); // clears match history before starting a new game in the menu

    vector<char> board(9, ' '); // Initialize the game board
    int currentPlayer = 1; // Player 1 starts
    bool isGameDraw = false;
    int moveCount = 0;

    while (!isGameDraw && moveCount < 9) {
        // Display board
        cout << "Current Board: \n";
        displayBoard(board);

        // Get the current player's move
        int move;
        cout << "Player " << currentPlayer << ", enter your move (1-9):";
        cin >> move;

        // map the numpad input to the corresponding position on the board 
        int mappedMove;
        switch (move) {
            case 1: mappedMove = 6; break;
            case 2: mappedMove = 7; break;
            case 3: mappedMove = 8; break;
            case 4: mappedMove = 3; break;
            case 5: mappedMove = 4; break;
            case 6: mappedMove = 5; break;
            case 7: mappedMove = 0; break;
            case 8: mappedMove = 1; break;
            case 9: mappedMove = 2; break;
                default:
                cout << "Invalid move. Please re enter a number 1 - 9 ";
                continue;
        }

        // Check if the move is valid
        if (board[mappedMove] != ' ') {
            cout << "Invalid move. The cell is already occupied. Please re enter a number 1 - 9";
            continue;
        }

        // Update the board with the player's move
        board[mappedMove] = (currentPlayer == 1) ? 'X' : 'O';

        // Check for a win
        if ((board[0] == board[1] && board[1] == board[2] && board[0] != ' ') ||
            (board[3] == board[4] && board[4] == board[5] && board[3] != ' ') ||
            (board[6] == board[7] && board[7] == board[8] && board[6] != ' ') ||
            (board[0] == board[3] && board[3] == board[6] && board[0] != ' ') ||
            (board[1] == board[4] && board[4] == board[7] && board[1] != ' ') ||
            (board[2] == board[5] && board[5] == board[8] && board[2] != ' ') ||
            (board[0] == board[4] && board[4] == board[8] && board[0] != ' ') ||
            (board[2] == board[4] && board[4] == board[6] && board[2] != ' ')) {
            cout << "Player " << currentPlayer << " wins!\n";
            break; // End the loop since there is a winner
    }

    // Switch players for the next turn
    currentPlayer = (currentPlayer == 1) ? 2 : 1;

    // Increment move count
    moveCount++;

    // Check if the game is a draw
    isGameDraw = (moveCount == 9);
}

    // Display the final board
    cout << "Final Board: \n";
    displayBoard(board);

    // Display the game result
    if (!isGameDraw) {
        cout << "Congratulations, Player " << currentPlayer << " wins \n";
    } else {
        cout << "It's a draw game. \n";
    }

    // Save the match record
    MatchInfo match;
    match.matchID = ++lastMatchID;
    match.player1 = "Player 1";
    match.player2 = "Player 2";
    match.gameBoard = board;
    saveMatchRecord(match);
}

    void TicTacToe::displayMatchHistory() {
        cout << "Match History: \n";
        for (const auto& match: matchHistory) {
            cout << "Match ID: " << " vs. " << match.player2 << "\n";
            displayBoard(match.gameBoard);
            cout << "-------------------------\n:";
        }
    }
    void TicTacToe::displayAllMatchHistory() {
        for (const auto& match : matchHistory) {
            cout << "Match ID: " << match.matchID << "_____\n" << match.player1 << " vs. " << match.player2 << "\n";
            displayBoard(match.gameBoard);
            cout << "-------------------------\n";
        }
    }