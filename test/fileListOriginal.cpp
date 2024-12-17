#include <windows.h>
#include <gdiplus.h>
#include <vector>
#include <string>
#include <commdlg.h>

using namespace Gdiplus;
using namespace std;

HINSTANCE hInst;
vector<string> fileList; // List to hold file names

// Function to load files from a folder
void LoadFilesFromFolder(const string& folderPath) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((folderPath + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        return;
    }

    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            fileList.push_back(findFileData.cFileName);
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

// Function to create a popup menu
void ShowFilePopupMenu(HWND hwnd) {
    HMENU hMenu = CreatePopupMenu();

    // Add each file as a menu item
    for (size_t i = 0; i < fileList.size(); ++i) {
        AppendMenuA(hMenu, MF_STRING, i + 1, fileList[i].c_str());
    }

    // Track the menu selection
    POINT pt;
    GetCursorPos(&pt);
    SetForegroundWindow(hwnd);
    int selectedItem = TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_TOPALIGN | TPM_LEFTBUTTON, pt.x, pt.y, 0, hwnd, nullptr);

    // Show message box with the selected file name
    if (selectedItem > 0 && selectedItem <= fileList.size()) {
        string message = "You selected the file: " + fileList[selectedItem - 1];
        MessageBoxA(hwnd, message.c_str(), "File Selected", MB_OK);
    }

    DestroyMenu(hMenu);
}

// Window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_RBUTTONDOWN: {
            // Show popup menu on right-click
            ShowFilePopupMenu(hwnd);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int main() {
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    WNDCLASS wndClass = {0};
    wndClass.lpfnWndProc = WndProc;
    wndClass.hInstance = GetModuleHandle(NULL);
    wndClass.lpszClassName = "FilePopupMenuClass";
    RegisterClass(&wndClass);

    // Create the main window
    HWND hwnd = CreateWindow(wndClass.lpszClassName, "File Popup Menu", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1200, 800, NULL, NULL, hInst, NULL);
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    // Load files from the folder (you can change this path)
//    LoadFilesFromFolder("D:\\clion\\OOP\\svg-rendering\\asset");
    LoadFilesFromFolder("C:\\Users\\nttis\\Downloads");

    // Event loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Shutdown GDI+
    GdiplusShutdown(gdiplusToken);

    return 0;
}
