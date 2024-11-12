#define UNICODE
#include <Windows.h>

// Game variables
int paddleX = 300;
int paddleY = 500;
int paddleWidth = 100;
int paddleHeight = 10;

int ballX = 400;
int ballY = 200;
int ballRadius = 10;
int ballSpeedX = 5;
int ballSpeedY = 5;

// Double buffering
HDC hdcBuffer;
HBITMAP hBitmapBuffer;

// Function to handle window messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            {
                // Create a compatible DC for double buffering
                HDC hdc = GetDC(hwnd);
                hdcBuffer = CreateCompatibleDC(hdc);
                hBitmapBuffer = CreateCompatibleBitmap(hdc, 800, 600);
                SelectObject(hdcBuffer, hBitmapBuffer);
                ReleaseDC(hwnd, hdc);
            }
            return 0;

        case WM_DESTROY:
            // Cleanup resources
            DeleteDC(hdcBuffer);
            DeleteObject(hBitmapBuffer);
            PostQuitMessage(0);
            return 0;

        // Handle other messages as needed

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

// Function to update the game state
void UpdateGame() {
    // Update ball position
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Simple collision with walls
    if (ballX - ballRadius < 0 || ballX + ballRadius > 800) {
        ballSpeedX = -ballSpeedX;
    }

    if (ballY - ballRadius < 0 || ballY + ballRadius > 600) {
        ballSpeedY = -ballSpeedY;
    }

    // Collision with paddle
    if (ballY + ballRadius > paddleY && ballX > paddleX && ballX < paddleX + paddleWidth) {
        ballSpeedY = -ballSpeedY;
    }
}

// Function to draw the game
void DrawGame(HDC hdc) {
    // Clear the buffer
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
    RECT clientRect = {0, 0, 800, 600}; // Temporary RECT variable
    FillRect(hdcBuffer, &clientRect, hBrush);
    DeleteObject(hBrush);

    // Draw paddle
    Rectangle(hdc, paddleX, paddleY, paddleX + paddleWidth, paddleY + paddleHeight);

    // Draw ball
    Ellipse(hdc, ballX - ballRadius, ballY - ballRadius, ballX + ballRadius, ballY + ballRadius);

    // Copy buffer to window
    BitBlt(hdc, 0, 0, 800, 600, hdcBuffer, 0, 0, SRCCOPY);
}

// Main function
int main() {
    // Register the window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"MyWindowClass";
    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindow(
        L"MyWindowClass", // Window class name
        L"Pong Game",     // Window Title
        WS_OVERLAPPEDWINDOW, // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, // Window position and size
        NULL, NULL, GetModuleHandle(NULL), NULL);

    // Display the window
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg = {};
    while(GetMessage(&msg, NULL, 0, 0)) {
        // Update and draw the game
        UpdateGame();
        DrawGame(hdcBuffer);

        // Process window messages
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}