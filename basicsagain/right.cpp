#define UNICODE
#define _Unicode

#include <windows.h>
#include <math.h>

double rotationAngle = 0.0;
const double rotationSpeed = 0.02;
const UINT timerId = 1;

   // Translate to the center of the rectangle
            int centerX = 125; // (50 + 200) / 2
            int centerY = 125;
            int width = 200 - 50;
            int height = 200 - 50;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;

    switch (msg) {
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            SetGraphicsMode(hdc, GM_ADVANCED);
            XFORM xForm;
            xForm.eM11 = (FLOAT)cos(rotationAngle);
            xForm.eM12 = (FLOAT)sin(rotationAngle);
            xForm.eM21 = -xForm.eM12;
            xForm.eM22 = xForm.eM11;
            xForm.eDx = (FLOAT)(centerX * (1 - xForm.eM11) - centerY * xForm.eM12);
            xForm.eDy = (FLOAT)(centerY * (1 - xForm.eM11) - centerX * xForm.eM12);
            SetWorldTransform(hdc, &xForm);

            // Draw the rotated rectangle
            Rectangle(hdc, 50, 50, 50 + width, 50 + height);

            EndPaint(hwnd, &ps);
            break;

            // GDI functions to draw shapes, lines, text

        case WM_CLOSE:
            PostQuitMessage(0);
            break;

        case WM_TIMER:
        rotationAngle += rotationSpeed;
        if (rotationAngle >= 2 * M_PI) {
            rotationAngle -= 2 * M_PI;
        }
        InvalidateRect(hwnd, NULL, TRUE);

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WindowProc, 0, 0, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"2D Visualization", NULL };
    RegisterClassEx(&wc);

    HWND hwnd = CreateWindow(wc.lpszClassName, TEXT("2D Visualization"), WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, wc.hInstance, NULL);

    SetTimer(hwnd, timerId, 50, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnregisterClass(wc.lpszClassName, wc.hInstance);
    return 0;
}