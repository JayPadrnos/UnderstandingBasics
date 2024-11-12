#define UNICODE
#include <windows.h>
#include <time.h>

// Global variations
int ballCup = -1; // Cup containing the ball
int guessedCup = -1; // Users guessed cup
bool hasGuessed = false; // Flag to check if the user has guessed
bool gameWon = false; // Flag to check if the game is won

// Function declarations
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// Entry point of the program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register the window class
    const wchar_t CLASS_NAME[] = L"CupsGameClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                      // Optional window style
        CLASS_NAME,             // Window class name
        L"Cups Game",           // Window title
        WS_OVERLAPPEDWINDOW,    // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,

        NULL,                   // Parent window
        NULL,                   // Menu
        hInstance,              // Instance handle
        NULL                    // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {};
    srand(time(NULL));

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
        // initialize the cups and ball position
        ballCup = rand() % 3;
        SetTimer(hwnd, 1, 100, NULL); // Timer to update cup positions
        return 0;

        case WM_TIMER:
        // move cups randomly
        int move = rand() % 3 - 1; // -1, 0, or 1
        ballCup = (ballCup + move + 3) % 3;
        InvalidateRect(hwnd, NULL, TRUE); // Redraw the window 
        return 0;

        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                // Draw the cups
                for (int i = 0; i < 3; ++i) {
                    RECT rect = {i * 120 + 50, 100, (i + 1) * 120 + 50, 200};
                    DrawText(hdc, L"Cup", -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                }
                    // Display the result if the user has guessed
                    if (hasGuessed) {
                        if (guessedCup == ballCup) {
                            TextOut(hdc, 160, 30, L"You won!", 8);
                            gameWon = true;
                        } else {
                            TextOut(hdc, 160, 30, L"You lost!", 9);
                        }

                        TextOut(hdc, 140, 50, L"Do you want to play again?", 26);
                    }

                    EndPaint(hwnd, &ps);
                }
                return 0;

                case WM_LBUTTONDOWN:
                if (!hasGuessed) {
                    guessedCup = LOWORD(lParam) / 120;
                    hasGuessed = true;
                    KillTimer(hwnd, 1);
                    InvalidateRect(hwnd, NULL, TRUE);
                }
                return 0;

                case WM_DESTROY:
                PostQuitMessage(0);
                return 0;

                case WM_KEYDOWN:
                if (gameWon) {
                    // Reset the game
                    ballCup = rand() % 3;
                    hasGuessed = false;
                    gameWon = false;
                    SetTimer(hwnd, 1, 100, NULL); // Restart cup movement
                    InvalidateRect(hwnd, NULL, TRUE); // Redraw the window
                }
                return 0;
            }

            return DefWindowProc(hwnd, message, wParam, lParam);
    }