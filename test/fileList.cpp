#include <windows.h>
#include <gdiplus.h>
#include <vector>
#include <string>
#include <commdlg.h>  // For file dialog

using namespace Gdiplus;
using namespace std;

// Global variables
HINSTANCE hInst;
vector<string> fileList; // List to hold file names

// Function to load files from a folder
void LoadFilesFromFolder(const string& folderPath) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((folderPath + "\\*").c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        return; // No files found
    }

    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            fileList.push_back(findFileData.cFileName); // Store the file name
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
}

// Function to create a popup menu with scrolling functionality
void ShowFilePopupMenu(HWND hwnd) {
    // Get screen height and calculate 3/4 height for the menu
    RECT rect;
    GetClientRect(GetDesktopWindow(), &rect);
    int screenHeight = rect.bottom;
    int popupHeight = (screenHeight * 3) / 4;

    // Create a new window for the popup menu with a fixed height
    HWND hwndList = CreateWindowEx(0, "LISTBOX", NULL,
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
        100, 100, 400, popupHeight, hwnd, NULL, hInst, NULL);

    // Add the files to the listbox
    for (const auto& file : fileList) {
        SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)file.c_str());
    }

    // Ensure the listbox resizes correctly
    SetWindowPos(hwndList, HWND_TOP, 100, 100, 400, popupHeight, SWP_NOACTIVATE);

    // Handle selection and user input immediately
    MSG msg;
    while (GetMessage(&msg, hwndList, 0, 0)) {
        if (msg.message == WM_COMMAND && HIWORD(msg.wParam) == LBN_SELCHANGE) {
            int selectedIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
            if (selectedIndex != LB_ERR) {
                char selectedFile[256];
                SendMessage(hwndList, LB_GETTEXT, selectedIndex, (LPARAM)selectedFile);

                // Show a message box with the selected file
                string message = "You selected the file: " + string(selectedFile);
                MessageBoxA(hwnd, message.c_str(), "File Selected", MB_OK);
            }
            break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyWindow(hwndList); // Close the popup window after selection
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

// WinMain - The main entry point
int main() {
    // Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    // Create a simple window
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
    LoadFilesFromFolder("D:\\clion\\OOP\\svg-rendering\\asset");

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
