#define _UNICODE
#define UNICODE
#include <windows.h>

// Global variables
HINSTANCE hInst;
LPCWSTR szTitle = L"Moveable Rectangle";
LPCWSTR szWindowClass = L"MoveableRectangleClass";
int rectX = 100;
int rectY = 100;

// Function to draw the rectangle 
void DrawRectangle(HDC hdc, int x, int y) {
    RECT rect = { x, y, x + 50, y + 50 };
    HBRUSH hBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
    FillRect(hdc, &rect, hBrush); 
}

// Window Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_PAINT:
        {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        DrawRectangle(hdc, rectX, rectY);
        EndPaint(hWnd, &ps);
        break;
}
case WM_KEYDOWN:
    switch (wParam) {
        case VK_LEFT:
            rectX -= 10;
            break;
        case VK_RIGHT:
            rectX += 10;
            break;
        case VK_UP:
            rectY += 10;
            break;
        case VK_DOWN:
            rectY += 10;
            break;
    }
    // Redraw the window to update the rectangles position
    InvalidateRect(hWnd, NULL, TRUE);
    break;
case WM_CLOSE:
    PostQuitMessage(0);
    break;
default:
    return DefWindowProc(hWnd, message, wParam, lParam);
    }
        return 0;
}

// Entry point
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
        WNDCLASSEX wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = szWindowClass;
        wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

        if (!RegisterClassEx(&wcex)) {
            MessageBox(NULL, L"Call to RegisterClassEx failed!", szTitle, 0);
            return 1;
        }

        hInst = hInstance;
        HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600, NULL, NULL, hInstance, NULL);

        if (!hWnd) {
            MessageBoxW(NULL, L"Call to CreateWindow failed!", szTitle, 0);
            return 1;
        }

        ShowWindow(hWnd, nCmdShow);
        UpdateWindow(hWnd);

        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return (int)msg.wParam;
    }