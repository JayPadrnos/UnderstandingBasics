#define UNICODE
#define _UNICODE

#include <windows.h>

int CALLBACK WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
) {
    // TODO creates window
    // Step 1 Register a window class
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MusicVisualizerClass";
    RegisterClass(&wc);

    // Step 2: Create a window
    HWND hwnd = CreateWindow(L"MusicVisualizerClass", L"Music Visualizer",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, L"Window Creation Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    // Step 3: Show and update the window
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 4: Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}