#include <windows.h>
#include <tchar.h>

HMENU hMenu;
bool isChecked = false;

// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            // Create a simple menu
            hMenu = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING, 1, "Option 1");
            AppendMenu(hMenu, MF_STRING, 2, _T("Option 2"));

            // Create a toggle option (checkbox)
            AppendMenu(hMenu, MF_STRING | (isChecked ? MF_CHECKED : MF_UNCHECKED), 3, _T("Toggle Option"));
            break;

        case WM_NCLBUTTONDOWN:
            // Check if the click is in the title bar
            if (wParam == HTCAPTION) {
                // Display the menu at the location of the mouse click
                POINT pt;
                GetCursorPos(&pt); // Get mouse position

                // Display the menu
                TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_TOPALIGN , pt.x, pt.y, 0, hwnd, NULL);
            }
            break;

        case WM_COMMAND:
            // Handle menu commands
            switch (LOWORD(wParam)) {
                case 1:
                    MessageBox(hwnd, _T("Option 1 selected"), _T("Menu"), MB_OK);
                    break;
                case 2:
                    MessageBox(hwnd, _T("Option 2 selected"), _T("Menu"), MB_OK);
                    break;
                case 3:
                    isChecked = !isChecked;
                    CheckMenuItem(hMenu, 3, (isChecked ? MF_CHECKED : MF_UNCHECKED));
                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Register and create the window
int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = _T("TitleBarMenuWindow");

    if (!RegisterClass(&wc)) {
        return -1;
    }

    HWND hwnd = CreateWindow(wc.lpszClassName, _T("Title Bar Menu with Toggle"), WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        return -1;
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}
