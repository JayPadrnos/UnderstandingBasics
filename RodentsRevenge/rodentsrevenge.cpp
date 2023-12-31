#define UNICODE
#include <windows.h>
#include <wingdi.h>
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
int catXPositions[NUM_CATS], catYPositions[NUM_CATS];
int trapX, trapY;
int cheeseX, cheeseY;
int bombX, bombY;
bool hasCheese = false;
bool hasBomb = false;
int score = 0;
DWORD startTime;
COLORREF playerColor = RGB(128, 128, 255);  // Blueish grey
COLORREF cheeseColor = RGB(200, 200, 0); // Yellowish
COLORREF bombColor = RGB(150, 150, 150); // Grey to black

// Function declarations
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM mParam, LPARAM lParam);
void DrawGrid(HDC hdc);
void MoveCatRandom();
void CheckCollision();
void CollectCheese();
void TriggerBomb();
void HandleKeyPress(WPARAM key);
void CALLBACK CheeseTimerCallback(HWND hwnd, UINT message, UINT_PTR idEvent, DWORD dwTime);
void CALLBACK BombTimerCallback(HWND hwnd, UINT message, UINT_PTR idEvent, DWORD doTime);
void CALLBACK TimeLimitTimerCallback(HWND hwnd, UINT message, UINT_PTR idEvent, DWORD dwTime);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register the window class
    const wchar_t CLASS_NAME[] = L"RodentsRevengeClass";

    WNDCLASS wc = {0};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.
    HWND hwnd = CreateWindowExW(
        0,                      // Optional window styles.
        CLASS_NAME,             // Window Class
        L"Rodent's Revenge",    // Window text
        WS_OVERLAPPEDWINDOW,    // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, GRID_SIZE * CELL_SIZE + 15, GRID_SIZE * CELL_SIZE + 37.5,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,   // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Initialize game variables
    srand(static_cast<unsigned int>(time(0)));
    playerX = rand() % GRID_SIZE;
    playerY = rand() % GRID_SIZE;
    for (int i = 0; i < NUM_CATS; ++i) {
        catXPositions[i] = rand() % GRID_SIZE;
        catYPositions[i] = rand() % GRID_SIZE;
    }

    // Set up timers for cheese, bomb, and time limit
    SetTimer(hwnd, CHEESE_TIMER_DURATION, CHEESE_TIMER_DURATION, CheeseTimerCallback);
    SetTimer(hwnd, BOMB_TIMER_DURATION, BOMB_TIMER_DURATION, BombTimerCallback);
    SetTimer(hwnd, TIME_LIMIT, TIME_LIMIT, TimeLimitTimerCallback);

    startTime = GetTickCount();

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up timers
    KillTimer(hwnd, CHEESE_TIMER_DURATION);
    KillTimer(hwnd, BOMB_TIMER_DURATION);
    KillTimer(hwnd, TIME_LIMIT);

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Draw game grid
            DrawGrid(hdc);

            EndPaint(hwnd, &ps);
        } break;

        case WM_KEYDOWN:
        HandleKeyPress(wParam);
        break;

        default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void DrawGrid(HDC hdc) {
    // CLear the entire window
    RECT clientRect;
    GetClientRect(GetActiveWindow(), &clientRect);
    FillRect(hdc, &clientRect, (HBRUSH)GetStockObject(WHITE_BRUSH));

    // Game state
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            RECT cellRect;
            cellRect.left = i * CELL_SIZE;
            cellRect.top = j * CELL_SIZE;
            cellRect.right = (i + 1) * CELL_SIZE;
            cellRect.bottom = (j + 1) * CELL_SIZE;

            // Clear the previous player position
            if (i == playerX && j == playerY) {
                FillRect(hdc, &cellRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
            }

            // Draw the cells based on game state.
            if (i == playerX && j == playerY) {
                // Draw the player
                // Rectangle(hdc, cellRect.left, cellRect.top, cellRect.right, cellRect.bottom);

                // Draw the player with specified color
                HBRUSH playerBrush = CreateSolidBrush(playerColor);
                FillRect(hdc, &cellRect, playerBrush);
                DeleteObject(playerBrush);
            }

            for(int k = 0; k < NUM_CATS; k++) {
                if (i == catXPositions[k] && j == catYPositions[k]) {
                    // Draw a cat
                    Ellipse(hdc, cellRect.left, cellRect.top, cellRect.right, cellRect.bottom);
                }
            }

            if (i == cheeseX && j == cheeseY && hasCheese) {
                // Draw cheese
                // Rectangle(hdc, cellRect.left, cellRect.top, cellRect.right, cellRect.bottom);

                // Draw cheese with specified color
                HBRUSH cheeseBrush = CreateSolidBrush(cheeseColor);
                FillRect(hdc, &cellRect, cheeseBrush);
                DeleteObject(cheeseBrush);
            }

            if (i == bombX && j == bombY && hasBomb) {
                // Draw a bomb
                // Rectangle(hdc, cellRect.left, cellRect.top, cellRect.right, cellRect.bottom);
                HBRUSH bombBrush = CreateSolidBrush(bombColor);
                FillRect(hdc, &cellRect, bombBrush);
                DeleteObject(bombBrush);
                // make classes for shapes allowing for code to be saved and take the logic to different ideas for mechanics of game
                
            }
        }
    }
}

void MoveCatRandom() {
    for (int i = 0; i < NUM_CATS; i++) {
        int move = rand() % 4; // 0:left, 1: up, 2: right, 3: down
        switch (move) {
            case 0:
            catXPositions[i] = std::max(0, catXPositions[i] - 1);
            break;
            case 1:
            catYPositions[i] = std::max(0, catYPositions[i] - 1);
            break;
            case 2:
            catXPositions[i] = std::min(GRID_SIZE - 1, catXPositions[i] + 1);
            break;
            case 3:
            catYPositions[i] = std::min(GRID_SIZE -1, catYPositions[i] + 1);
            break;
        }
    }
}

void CheckCollision() {
    // TODO: Implement colliion logic (e.g. check if player collides with a cat)
}

void CollectCheese() {
    if (playerX == cheeseX && playerY == cheeseY) {
        hasCheese = false;
        score += 10;
        // TODO: Display a message or update the score label
    }
}

void TriggerBomb() {
    if (hasBomb && playerX == bombX && playerY == bombY) {
        // TODO: Implement bomb logic
    }
}

void HandleKeyPress(WPARAM key) {
    switch (key) {
        case 'W':
        // Move player up
        playerY = std::max(0, playerY - 1);
        break;
        case 'A':
        // Move player left
        playerX = std::max(0, playerX - 1);
        break;
        case 'S':
        // Move player down
        playerY = std::min(GRID_SIZE - 1, playerY + 1);
        break;
        case 'D':
        playerX = std::min(GRID_SIZE - 1, playerX + 1);
        break;
        case 'T':
        // Place trap at player's position
        trapX = playerX;
        trapY = playerY;
        break;
        //case 'C' 
        // Collect cheese at player's position
            // CollectCheese();
            //break;
        //case 'B':
        // Set bomb at player's position
        //bombX = playerX;
        //bombY = playerY;
        //hasBomb = true;
        //break;
        //case 'G'
        // Trigger bomb at player's position
            // TriggerBomb();
            // break;
    }

    // TODO: Update game logic (e.g., move cats, check collision, etc.)
    MoveCatRandom();
    CheckCollision();

    // TODO: Update game state and score

    // Redraw the window
    InvalidateRect(GetActiveWindow(), NULL, TRUE);
}

void CALLBACK CheeseTimerCallback(HWND hwnd, UINT message, UINT_PTR idEvent, DWORD dwTime) {
    if (idEvent == CHEESE_TIMER_DURATION) {
        cheeseX = rand() % GRID_SIZE;
        cheeseY = rand() % GRID_SIZE;
        hasCheese = true;
        // Redraw the window after updating cheese position
        InvalidateRect(GetActiveWindow(), NULL, TRUE);
    }
}

void CALLBACK BombTimerCallback(HWND hwnd, UINT message, UINT_PTR idEvent, DWORD dwTime) {
    if (idEvent == BOMB_TIMER_DURATION) {
        bombX = rand() % GRID_SIZE;
        bombY = rand() % GRID_SIZE;
        hasBomb = true;
        // Redraw window after updating bomb position
        InvalidateRect(GetActiveWindow(), NULL, TRUE);
    }
}

void CALLBACK TimeLimitTimerCallback(HWND hwnd, UINT message, UINT_PTR idEvent, DWORD dwTime) {
    if (idEvent == TIME_LIMIT) {
        MessageBoxW(hwnd, L"Game Over! Time limit reached.", L"Game Over", MB_OK | MB_ICONINFORMATION);
        PostQuitMessage(0);
    }
}

// Code is fixed and compile ready, however white screen appears with nothing on screen, more work must be done other than just logic behind game itself.


// Game auto closes when time limit is reached
// Keep exploring how to easier identify objects for users who launch the program


// Add a Timer to the game so the user can see view time left
// Save player score to a Top 10 position with a 3 Character (ASS) and a scoring***
// 

// too many RECT spawns after an alloted time with an extended timer
// scoring system

// OFFSET THE GRID BY AN ODD NUMBER OVER EVEN IN ORDER FOR USER TO SPAWN CENTER
//