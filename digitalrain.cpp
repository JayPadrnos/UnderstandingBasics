#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;
const int NUM_RAIN_CHARS = 100;

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    srand(time(0));
    char rainChars[NUM_RAIN_CHARS];
    int rainPositions[NUM_RAIN_CHARS];

    for (int i = 0; i < NUM_RAIN_CHARS; ++i) {
        rainChars[i] = rand() % 94 + 33;
        rainPositions[i] = rand() % SCREEN_WIDTH;
    }

    while (true) {

        for (int i = 0; i < NUM_RAIN_CHARS; ++i) {
            rainPositions[i]++;
            if (rainPositions[i] >= SCREEN_HEIGHT) {
                rainPositions[i] = 0;
            }
        }

        system("cls");

        for (int i = 0; i < NUM_RAIN_CHARS; ++i) {
            setCursorPosition(rainPositions[i], i);
            cout << rainChars[i];
        }

        Sleep(50);
    }

    return 0;
}

// character line through center and at bottom along with random letter characters.
// flashes for animation.
// moves from left to right when we want from top to bottom
// all characters move at the same time with no trail
// we want for the characters to be specified lettering or even words