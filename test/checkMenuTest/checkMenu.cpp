#include <windows.h>
#include <vector>
#include <string>

#define ID_CHECKBOX1 1001
#define ID_CHECKBOX2 1002
#define ID_CHECKBOX3 1003
#define ID_CHECKBOX4 1004
#define ID_CHECKBOX5 1005
#define ID_CHECKBOX6 1006
#define ID_CONFIG_BUTTON 2001

// Data to track the checkbox states
std::vector<bool> itemChecked = {false, false, false, false, false, false}; // Track checkbox state
HWND hCheckbox[6]; // Handle to checkboxes
HWND hConfigButton; // Handle to the config button

// For dragging the window
bool isDragging = false;
POINT dragStartPos;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            // Create checkboxes
            hCheckbox[0] = CreateWindow("BUTTON", "Item A", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                                        10, 10, 100, 30, hwnd, (HMENU)ID_CHECKBOX1, NULL, NULL);
            hCheckbox[1] = CreateWindow("BUTTON", "Item B", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                                        10, 50, 100, 30, hwnd, (HMENU)ID_CHECKBOX2, NULL, NULL);
            hCheckbox[2] = CreateWindow("BUTTON", "Item C", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                                        10, 90, 100, 30, hwnd, (HMENU)ID_CHECKBOX3, NULL, NULL);
            hCheckbox[3] = CreateWindow("BUTTON", "Item D", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                                        10, 130, 100, 30, hwnd, (HMENU)ID_CHECKBOX4, NULL, NULL);
            hCheckbox[4] = CreateWindow("BUTTON", "Item E", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                                        10, 170, 100, 30, hwnd, (HMENU)ID_CHECKBOX5, NULL, NULL);
            hCheckbox[5] = CreateWindow("BUTTON", "Item F", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                                        10, 210, 100, 30, hwnd, (HMENU)ID_CHECKBOX6, NULL, NULL);

            // Create the Config button in the bottom-right corner
            hConfigButton = CreateWindow("BUTTON", "Config", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                         300, 200, 100, 30, hwnd, (HMENU)ID_CONFIG_BUTTON, NULL, NULL);
            break;

        case WM_COMMAND: {
            int id = LOWORD(wp);

            if (id >= ID_CHECKBOX1 && id <= ID_CHECKBOX6) {
                // Handle checkbox state change
                int checkboxIndex = id - ID_CHECKBOX1;
                itemChecked[checkboxIndex] = !itemChecked[checkboxIndex];

                // Update the checkbox state
                SendMessage(hCheckbox[checkboxIndex], BM_SETCHECK, itemChecked[checkboxIndex] ? BST_CHECKED : BST_UNCHECKED, 0);
            } else if (id == ID_CONFIG_BUTTON) {
                // Config button clicked, delete all checked items
                for (int i = 0; i < 6; i++) {
                    if (itemChecked[i]) {
                        itemChecked[i] = false; // Uncheck all selected items
                        // Update checkbox state
                        SendMessage(hCheckbox[i], BM_SETCHECK, BST_UNCHECKED, 0);
                    }
                }
                // Close the window after Config button click
                PostMessage(hwnd, WM_CLOSE, 0, 0); // This will trigger the window to close
            }
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

        case WM_LBUTTONDOWN: {
            // Start dragging
            isDragging = true;
            dragStartPos.x = LOWORD(lp);  // X-coordinate from the low-order word of LPARAM
            dragStartPos.y = HIWORD(lp);  // Y-coordinate from the high-order word of LPARAM
            SetCapture(hwnd);
            break;
        }

        case WM_LBUTTONUP: {
            // Stop dragging
            isDragging = false;
            ReleaseCapture();
            break;
        }

        case WM_MOUSEMOVE: {
            if (isDragging) {
                // Move window while dragging
                int dx = LOWORD(lp) - dragStartPos.x; // Calculate movement in the X direction
                int dy = HIWORD(lp) - dragStartPos.y; // Calculate movement in the Y direction
                RECT windowRect;
                GetWindowRect(hwnd, &windowRect);

                // Update the position of the window
                SetWindowPos(hwnd, NULL, windowRect.left + dx, windowRect.top + dy, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

                // Update the drag start position to smooth out movement
                dragStartPos.x = LOWORD(lp); // Update starting position
                dragStartPos.y = HIWORD(lp); // Update starting position

                // Minimize redrawing during dragging
                InvalidateRect(hwnd, NULL, FALSE);  // Only invalidate the window when the drag ends
            }
            break;
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
    wc.hInstance = GetModuleHandle(0);
    wc.lpszClassName = "CheckboxListApp";
    RegisterClass(&wc);

    // Create window (Make it a popup window)
    HWND hwnd = CreateWindowEx(0, "CheckboxListApp", "Checkbox List with Config Button", WS_CAPTION,
                               CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,
                               NULL, NULL, wc.hInstance, NULL);

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
