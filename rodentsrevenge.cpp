#define UNICODE
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
int catXPositions[NUM_CATS], catYPositions[NUM_CATS];
int trapX, trapY;
int cheeseX, cheeseY;
int bombX, bombY;
bool hasCheese = false;
bool hasBomb = false;
int score = 0;
DWORD startTime;

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
        CW_USEDEFAULT, CW_USEDEFAULT, GRID_SIZE * CELL_SIZE, GRID_SIZE * CELL_SIZE,

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

                    // DEBUG statement to print info about entering the drawgrid function
                    DebugPrint("Entering Drawgrid function....");


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
            
                     // DEBUG to print cell coords
                     printf("Cell (%d, %d\n", i, j);

            // Draw the cells based on game state.
            if (i == playerX && j == playerY) {
                // Draw the player
                Rectangle(hdc, cellRect.left, cellRect.top, cellRect.right, cellRect.bottom);

                     // DEBUG to print player position
                     DebugPrint("Drawing the player...");
            }

            for(int k = 0; k < NUM_CATS; k++) {
                if (i == catXPositions[k] && j == catYPositions[k]) {
                    // Draw a cat
                    Ellipse(hdc, cellRect.left, cellRect.top, cellRect.right, cellRect.bottom);
                }
            }

            if (i == cheeseX && j == cheeseY && hasCheese) {
                // Draw cheese
                Rectangle(hdc, cellRect.left, cellRect.top, cellRect.right, cellRect.bottom);
            }

            if (i == bombX && j == bombY && hasBomb) {
                // Draw a bomb
                Rectangle(hdc, cellRect.left, cellRect.top, cellRect.right, cellRect.bottom);
            
                        // DEBUG statement to print info about exiting DrawGrid
                        DebugPrint("Exiting DrawGrid function....");
            
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
    }
}

void CALLBACK BombTimerCallback(HWND hwnd, UINT message, UINT_PTR idEvent, DWORD dwTime) {
    if (idEvent == BOMB_TIMER_DURATION) {
        bombX = rand() % GRID_SIZE;
        bombY = rand() % GRID_SIZE;
        hasBomb = true;
    }
}

void CALLBACK TimeLimitTimerCallback(HWND hwnd, UINT message, UINT_PTR idEvent, DWORD dwTime) {
    if (idEvent == TIME_LIMIT) {
        MessageBoxW(hwnd, L"Game Over! Time limit reached.", L"Game Over", MB_OK | MB_ICONINFORMATION);
        PostQuitMessage(0);
    }
}

// Code is fixed and compile ready, however white screen appears with nothing on screen, more work must be done other than just logic behind game itself.
//lazy 