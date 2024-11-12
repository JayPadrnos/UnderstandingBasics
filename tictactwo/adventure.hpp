#ifndef ADVENTURE_HPP
#define ADVENTURE_HPP

#include<vector>
#include <chrono> // For time related functionality
#include <string>

using namespace std;

class Adventure {
    private:
        int playerLife; 
        bool hasSword; 
        bool hasKey;
        chrono::steady_clock::time_point startTime; // Start time of the game
        chrono::steady_clock::time_point endTime;

    public:
        Adventure(); // Constructor

        void startGame(); 
        string getTimeDuration(); // Function to calculate time duration 

        // Add other member functions as needed for the adventure game

};

#endif