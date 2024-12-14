#include <windows.h>
#include <gdiplus.h>
#include <string>

using namespace Gdiplus;

// Global variables
HINSTANCE hInst;
ULONG_PTR gdiplusToken;
HWND hwnd1;  // Window handle for the main window

// Function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Function to create the menu
HMENU CreateAppMenu() {
	HMENU menu = CreateMenu();

	// Create a "File" menu
	HMENU fileMenu = CreatePopupMenu();
	AppendMenu(fileMenu, MF_STRING, 1, "Exit");
	AppendMenu(fileMenu, MF_STRING, 2, "Exit");
	AppendMenu(fileMenu, MF_STRING, 3, "Exit");
	AppendMenu(fileMenu, MF_STRING, 4, "Exit");
	AppendMenu(fileMenu, MF_STRING, 5, "Exit");
	AppendMenu(menu, MF_STRING | MF_POPUP, (UINT_PTR) fileMenu, "File");

	// Create another "Help" menu (optional)
	HMENU helpMenu = CreatePopupMenu();
	AppendMenu(helpMenu, MF_STRING, 2, "About");
	AppendMenu(menu, MF_STRING | MF_POPUP, (UINT_PTR) helpMenu, "Help");

	return menu;
}

// Entry point using main instead of wWinMain
int main(int argc, char *argv[]) {
	// Initialize GDI+
	GdiplusStartupInput gdiPlusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiPlusStartupInput, NULL);

	// Initialize Window Class for Window 1 (Main window)
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;  // Set Window 1 Procedure
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = "WindowClass1";
	RegisterClass(&wc);

	// Create Window 1
	hwnd1 = CreateWindowEx(
		0,
		"WindowClass1",
		"Window 1 with Menu",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
		nullptr, nullptr, hInst, nullptr);

	// Create and set the menu
	HMENU hMenu = CreateAppMenu();
	SetMenu(hwnd1, hMenu);  // Attach menu to the window

	// Show Window 1
	ShowWindow(hwnd1, SW_SHOWNORMAL);
	UpdateWindow(hwnd1);

	// Main message loop
	MSG msg = {};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Shutdown GDI+
	GdiplusShutdown(gdiplusToken);
	return (int) msg.wParam;
}

// Window procedure for Window 1 (Main window)
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_PAINT: {
			// Drawing with GDI+ in Window 1
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			Graphics graphics(hdc);
			Pen pen(Color(255, 0, 0, 255));  // Blue pen
			graphics.DrawRectangle(&pen, 50, 50, 200, 150);  // Drawing a rectangle

			EndPaint(hwnd, &ps);
		}
			break;

		case WM_COMMAND: {
			switch (LOWORD(wParam)) {
				case 1:  // "Exit" menu item
					PostQuitMessage(0);  // Close the window
					break;
				case 2:  // "About" menu item
					MessageBox(hwnd, "This is a basic application.", "About", MB_OK);
					break;

				default:
					return DefWindowProc(hwnd, uMsg, wParam, lParam);
			}
		}
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
