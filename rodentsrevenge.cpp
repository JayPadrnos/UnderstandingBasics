#include <windows.h>
#include <vector>
#include <ctime>
#include <cstdlib>

// Constants
const int GRID_SIZE = 10;
const int CELL_SIZE = 30;
const int NUM_CATS = 3;
const int TRAP_DURATION = 5000; // 5 sec
const int CHEESE_TIMER_DURATION = 15000; // 15 sec
const int BOMB_TIMER_DURATION = 30000; // 30 sec
const int TIME_LIMIT = 180000; // 3 minutes

// Global variables
int playerX, playerY;
int catXPositions[NUM_CATS], catYPostions[NUM_CATS];
int trapX, trapY;
int cheeseX, cheeseY;
int bombX, bombY;
bool hasCheese = false;
bool hasBomb = false;
int score = 0;
DWORD startTime;

// Function declarations
LRESULT CALLBACK WindowProc(HWND hwnd, UINT ullsg, WPARAM mParam, LPARAM lParam);
void DrawGrid(HDC hdc);
void MoveCatRandom();
void CheckCollision();
void CollectCheese();
void TriggerBomb();
void HandleKeyPress(WPARAM key);
