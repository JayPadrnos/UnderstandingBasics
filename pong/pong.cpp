#define UNICODE
#include <windows.h>

// Function prototype
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void UpdateGame();
void DrawGame(HDC hdc);
void ResetGame();

// Game variables
int paddleY = 250;
int ballX = 400, ballY = 300;
int ballSpeedX = 3, ballSpeedY = 3;

int main() {
    // Register the window class
    const wchar_t CLASS_NAME[] = L"Pong Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                      // Optional window styles
        CLASS_NAME,             // Window Class
        L"Pong Game",            // Window Title
        WS_OVERLAPPEDWINDOW,     // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,

        NULL,                   // Parent window
        NULL,                   // Menu
        GetModuleHandle(NULL),  // Instance handle
        NULL                    // Additional application data
        );

        if (hwnd == NULL) {
            return 0;
        }

        // Show the window
        ShowWindow(hwnd, SW_SHOWNORMAL);
        UpdateWindow(hwnd);

        // Main message loop
        MSG msg = {};
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

            case WM_KEYDOWN:
            switch (wParam) {
                case VK_UP:
                    if (paddleY > 0) paddleY -= 5;
                    break;
                case VK_DOWN:
                    if (paddleY < 500) paddleY += 5;
                    break;
            }
            return 0;

            case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                // Draw the game
                DrawGame(hdc);

                EndPaint(hwnd, &ps);
            }
            return 0;
            case WM_TIMER:
            UpdateGame();
            InvalidateRect(hwnd, NULL, FALSE);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void UpdateGame() {
    // Update ball position
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Ball collision with walls
    if (ballY <= 0 || ballY >= 590)
    ballSpeedY = -ballSpeedY;

    // Ball collision with paddle
    if (ballX <= 50 && ballY >= paddleY && ballY <= paddleY + 100)
    ballSpeedX = -ballSpeedX;

    // Check if ball is out of bounds 
    if (ballX < 0 || ballX > 800) {
        // Reset ball position
        ResetGame();
    }
}

void DrawGame(HDC hdc) {
    // Draw paddles
    Rectangle(hdc, 50, paddleY, 70, paddleY + 100);

    // Draw ball
    Ellipse(hdc, ballX - 10, ballY - 10, ballX + 10, ballY + 10);
}

void ResetGame() {
    // Reset ball position
    ballX = 400;
    ballY = 300;
}