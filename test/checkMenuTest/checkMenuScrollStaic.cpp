#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

#define ID_CONFIG_BUTTON 2001

// Data to track the checkbox states
std::vector<bool> itemChecked; // Track checkbox state
HWND hConfigButton; // Handle to the config button
HWND hContainer; // Handle to the container for buttons
HINSTANCE hInst; // Store instance for window class registration

// Number of buttons to create
const int NUM_BUTTONS = 100;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    static int scrollPos = 0;
    switch (msg) {
        case WM_CREATE:
            hContainer = CreateWindowEx(0, "STATIC", "", WS_CHILD | WS_VISIBLE | SS_BLACKFRAME,
                                        0, 0, 500, 300, hwnd, NULL, hInst, NULL);

            // Create all the buttons (A1 to A100)
            for (int i = 0; i < NUM_BUTTONS; ++i) {
                std::string buttonText = "A" + std::to_string(i + 1);
                CreateWindow("BUTTON", buttonText.c_str(), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                             10, 30 * i, 100, 30, hContainer, (HMENU)(i + 1), hInst, NULL);
            }

            // Create the Config button at the bottom-right corner
            hConfigButton = CreateWindow("BUTTON", "Config", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                         300, 250, 100, 30, hwnd, (HMENU)ID_CONFIG_BUTTON, hInst, NULL);
            break;

        case WM_COMMAND: {
            int id = LOWORD(wp);
            if (id == ID_CONFIG_BUTTON) {
				PostMessage(hwnd, WM_CLOSE, 0, 0); // This will trigger the window to close
            }
            break;
        }

        case WM_VSCROLL: {
            int scrollEvent = LOWORD(wp);
            switch (scrollEvent) {
                case SB_LINEDOWN:
                    scrollPos += 1;
                    break;
                case SB_LINEUP:
                    scrollPos -= 1;
                    break;
                case SB_PAGEUP:
                    scrollPos -= 5;
                    break;
                case SB_PAGEDOWN:
                    scrollPos += 5;
                    break;
            }

            // Ensure scrolling doesn't go beyond limits
            scrollPos = max(0, min(scrollPos, NUM_BUTTONS - 10));

            // Adjust the position of the container (move buttons up/down)
            SetWindowPos(hContainer, NULL, 0, -scrollPos * 30, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            break;
        }

        case WM_MOUSEWHEEL: {
            // Mouse wheel scrolling
            int zDelta = GET_WHEEL_DELTA_WPARAM(wp);
            if (zDelta > 0) {
                scrollPos -= 1; // Scroll up
            } else {
                scrollPos += 1; // Scroll down
            }

            // Ensure scrolling doesn't go beyond limits
            scrollPos = max(0, min(scrollPos, NUM_BUTTONS - 10));

            // Adjust the position of the container
            SetWindowPos(hContainer, NULL, 0, -scrollPos * 30, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            break;
        }

        case WM_ERASEBKGND: {
            // Fill the background with white
            HDC hdc = (HDC)wp;
            RECT rect;
            GetClientRect(hwnd, &rect);
            FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW+1)); // Use white color
            return 1;  // Indicate that the background has been erased
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

int main() {
    // Register window class
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst = GetModuleHandle(0);
    wc.lpszClassName = "CheckboxListApp";
    RegisterClass(&wc);

    // Create window (Make it a window with caption)
    HWND hwnd = CreateWindowEx(0, "CheckboxListApp", "Checkbox List with Scrollable Buttons", WS_CAPTION,
                               CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
                               NULL, NULL, hInst, NULL);

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
