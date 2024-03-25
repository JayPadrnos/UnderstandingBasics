#include <windows.h>
#include <iostream>

int main() {
    const wchar_t* exePath = L"path_to_your_exe.exe";
    const wchar_t* iconPath = L"your_icon_ico";

    // Load the icon file
    HICON hIcon = static_cast<HICON>(LoadImage(NULL, iconPath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE));
    if (!hIcon) {
        std::cerr << "Failed to load icon" << std::endl;
        return 1;
    }

    // Update the icon of the exe file
    if (!UpdateResource(NULL, RT_GROUP_ICON, MAKEINTRESOURCE(1), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), reinterpret_cast<LPVOID>(hIcon), SizeofResource(NULL, hIcon))) {
        std::cerr << "Failed to update icon resource" << std::endl;
        DestroyIcon(hIcon);
        return 1;
    }

    // Save changes to the exe file
    if (!EndUpdateResource(NULL, FALSE)) {
        std::cerr << "Failed to save changes to exe file" << std::endl;
        DestroyIcon(hIcon);
        return 1;
    }

    std::cout << "Icon changed successfully!" << std::endl;

    // Clean up
    DestroyIcon(hIcon);

    return 0;
}