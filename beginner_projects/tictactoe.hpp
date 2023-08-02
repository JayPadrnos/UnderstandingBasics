#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct MatchInfo {
    int matchID;
    string player1;
    string player2;
    vector<char> gameBoard;
};

class TicTacToe {
    private:
    vector<MatchInfo> matchHistory;
    int lastMatchID = 0;

    void saveMatchRecord(const MatchInfo& match);
    void readMatchHistory();

    public:
    void playGame();
    void displayMatchByID(int matchID);
};

#endif // TICTACTOE_HPP