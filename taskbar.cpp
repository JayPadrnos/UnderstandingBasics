#include <windows.h>

#define UNICODE

#define ID_FILE_NEW 1
#define ID_FILE_EXIT 2
#define ID_EDIT 3
#define ID_LOAD 4
#define ID_GAME 5

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int main() {
    // Initialize the application instance
    HINSTANCE hInstance = GetModuleHandle(NULL);

    // Register the window class
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyWindowClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    // Create Window
    HWND hWnd = CreateWindow(
        L"MyWindowClass", L"My Window",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        400, 400, NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);

    // Message loop
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
        {
            // Create the menu bar
            HMENU hMenu = CreateMenu();
            HMENU hFileMenu = CreatePopupMenu();

            AppendMenuW(hFileMenu, MF_STRING, ID_FILE_NEW, L"&New");
            AppendMenuW(hFileMenu, MF_STRING, ID_FILE_EXIT, L"&Exit");

            AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hFileMenu, L"&File");
            AppendMenu(hMenu, MF_STRING, ID_EDIT, L"&Edit");
            AppendMenu(hMenu, MF_STRING, ID_EDIT, L"&Edit");
            AppendMenuW(hMenu, MF_STRING, ID_GAME, L"&Game");

            SetMenu(hWnd, hMenu);
        }
        break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_FILE_NEW:
                    MessageBoxW(hWnd, L"New selected", L"Info", MB_OK | MB_ICONINFORMATION);
                    break;
                    case ID_FILE_EXIT:
                    break;
                // Handle other menu items if needed
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}