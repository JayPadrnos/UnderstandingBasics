#ifndef TICTACTWO_HPP
#define TICTACTWO_HPP

#include <vector> 
#include <string>

using namespace std;

class TicTacToe {
    private:
    struct MatchInfo {
        int matchID;
        string player1;
        string player2;
        vector<char> gameBoard;
    };

    vector<MatchInfo> matchHistory;
    int lastMatchID;

    void saveMatchRecord(const MatchInfo& match);
    void readMatchHistory();
    void displayMatchByID(int matchID);
    void displayBoard(const vector<char>& board);

    public:
    TicTacToe();
    void playGame();
    void displayMatchHistory();
};

#endif