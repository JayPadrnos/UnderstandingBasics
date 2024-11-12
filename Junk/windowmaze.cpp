#define UNICODE
#include <iostream>
#include <windows.h>
#include <ctime>

const int width = 10;
const int height = 10;
wchar_t maze[height][width];

COORD startPosition, currentPosition, endPosition;

void initializeMaze() {
    // Initialize the maze with walls and start position
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            maze[i][j] = L'#';
        }
    }

    startPosition = {1, 1 };
    currentPosition = startPosition;
    endPosition = { height - 2, width - 2 };

    maze[startPosition.Y][startPosition.X] = L'S';
    maze[endPosition.Y][endPosition.X] = L'E';
}

void drawMaze(HWND hWnd, HDC hdc) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            TextOut(hdc, j * 20, i * 20, &maze[i][j], 1);
        }
    }
}

void move(char direction) {
    switch (direction) {
        case 'W':
            if (currentPosition.Y > 0 && maze[currentPosition.Y - 1][currentPosition.X] != L'#') {
                maze[currentPosition.Y][currentPosition.X] = L' ';
                --currentPosition.Y;
            }
            break;
        case 'S':
            if (currentPosition.Y < height - 1 && maze[currentPosition.Y + 1][currentPosition.X] != L'#') {
                maze[currentPosition.Y][currentPosition.X] = L' ';
                ++currentPosition.Y;
            }
            break;
        case 'A':
            if (currentPosition.X > 0 && maze[currentPosition.Y][currentPosition.X - 1] != L'#') {
                maze[currentPosition.Y][currentPosition.X] = L' ';
                --currentPosition.X;
            }
            break;
        case 'D':
            if (currentPosition.X < width - 1 && maze[currentPosition.Y][currentPosition.X + 1] != L'#') {
                maze[currentPosition.Y][currentPosition.X] = L' ';
                ++currentPosition.X;
            }
            break;
    }
}

bool isGameComplete() {
    return currentPosition.X == endPosition.X && currentPosition.Y == endPosition.Y;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            drawMaze(hWnd, hdc);

            EndPaint(hWnd, &ps);
        }
        break;

        case WM_KEYDOWN:
            switch (wParam) {
            case VK_ESCAPE:
                PostQuitMessage(0);
                break;
            case 'W':
            case 'A':
            case 'S':
            case 'D':
                move(static_cast<char>(wParam));
                if (isGameComplete()) {
                    MessageBox(hWnd, L"Congratulations! You Win!", L"You Win", MB_OK | MB_ICONINFORMATION);
                    initializeMaze();
                }    
                InvalidateRect(hWnd, NULL, TRUE);
                break;
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

int main() {
    srand(static_cast<unsigned>(time(0)));

    initializeMaze();

    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MazeGame";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    HWND hWnd = CreateWindow(
        L"MazeGame", L"Maze Game",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        400, 400, NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}