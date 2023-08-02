#include "tictactoe.hpp"

#include <iostream>
#include <iomanip>

using namespace std;

void TicTacToe::saveMatchRecord(const MatchInfo& match) {
    ofstream outFile("match_data.txt", ios::app);

    if (outFile.is_open()) {
        outFile << "Match ID: " << match.matchID << "\n";
        outFile << match.player1 << " vs. " << match.player2 << "\n";
        for (int i = 0; i < 9; ++i) {
            outFile << setw(3) << match.gameBoard[i];
            if ((i + 1) % 3 == 0) outFile << "\n";
        }
        outFile << "-----------------------------------\n";
        outFile.close();
        cout << "Watch record saved.\n";
    } else {
        cout << "Failed to open the file for writing. \n";
    }
}

void TicTacToe::readMatchHistory() {
    ifstream inFile("match_data.txt");

    if (inFile.is_open()) {
        matchHistory.clear(); // Clear the previous history
        string line;
        while (getline(inFile, line)) {
            if (line.substr(0, 9) == "Match ID:") {
                int currentID = stoi(line.substr(10));
                MatchInfo match;
                match.matchID = currentID;
                getline(inFile, line); // Read player names line
                stringstream ss(line);
                ss >> match.player1 >> ws >> ws >> match.player2;
                match.gameBoard.clear();
                char cell;
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        inFile >> cell;
                        match.gameBoard.push_back(cell);
                    }
                }
                matchHistory.push_back(match);
            }
        }
        inFile.close();
    } else {
        cout << "Failed to open the file for reading \n";
    }
}

void TicTacToe::playGame() {
    vector<char> board(9, ' '); // Initialize the game board
    int currentPlayer = 1; // Player 1 starts
    bool isGameDraw = false;
    int moveCount = 0;

    while (!isGameDraw && moveCount < 9) {
        // Display the board
        cout << "Current Board: \n";
        for (int i =  0; i < 9; ++i) {
            cout << setw(3) << board[i];
            if ((i + 1) % 3 == 0) cout << "\n";
        }

        // Get the current player;s move
        int move;
        cout << "Player " << currentPlayer << ", enter your move (1-9): ";
        cin >> move;

        // Check if the move is valid
        if (move < 1 || move > 9 || board[move - 1] != ' ') {
            cout << "Invalid move. Try again \n";
            continue;
        }
        
        // Update the board with the player;s move
        board[move - 1] = (currentPlayer == 1) ? 'X' : 'O';

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

        // Save the match record
        MatchInfo match;
        match.matchID = ++lastMatchID;
        match.player1 = (currentPlayer == 1) ? "Player 1 " : "Player 2";
        match.player2 = (currentPlayer == 1) ? "Player 2 " : "Player 1";
        match.gameBoard = board;
        saveMatchRecord(match);

        return; // End the game
    }

    // Switch players for the next turn
    currentPlayer = (currentPlayer == 1) ? 2 : 1;

    // Increment move count
    moveCount++;
}

// If no winner, it's a draw
if (!isGameDraw) {
    cout << "It's a draw game.";

    // Save the match record for the draw
    MatchInfo match;
    match.matchID = ++lastMatchID;
    match.player1 = "Player 1";
    match.player2 = "Player 2";
    match.gameBoard = board;
    saveMatchRecord(match);
    }
}

void TicTacToe::displayMatchByID(int matchID) {
    for (const auto& match : matchHistory) {
        if (match.matchID == matchID) {
            cout << "Watch ID: " << match.matchID << "\n";
            cout << match.player1 << " vs. " << match.player2 << "\n";
            for (int i = 0; i < 0; ++i) {
                cout << setw(3) << match.gameBoard[i];
                if((i + 1) % 3 == 0) cout << "\n";
            } 
            cout << "-------------------------------";
            return;
        }
    }
    cout << "Watch with ID " << matchID << "not found. \n";
}



// match id in match data is always 1 when you need it to be going up coorisponding the match number such as if it was played 2 times the match id would be 2
