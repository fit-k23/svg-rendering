#include <windows.h>
#include <gdiplus.h>

using namespace Gdiplus;

#pragma comment(lib, "gdiplus.lib")

// Global variables
ULONG_PTR gdiplusToken;

// Window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CREATE: {
		GdiplusStartupInput gdiPlusStartupInput;
		GdiplusStartup(&gdiplusToken, &gdiPlusStartupInput, NULL);
	}
		return 0;

	case WM_NCPAINT: {
		HDC hdc = GetWindowDC(hwnd);
		Graphics graphics(hdc);

		// Fill the title bar background with a solid color (e.g., blue)
		SolidBrush backgroundBrush(Color(255, 0, 122, 204)); // Blue background
		graphics.FillRectangle(&backgroundBrush, 0, 0, 800, 30); // Fill the area of the title bar

		// Draw 3 lines (Hamburger menu)
		Pen pen(Color(255, 255, 255)); // White color for the lines
		int width = 20; // Width of the lines
		int offset = 5; // Space between lines
		int x = 10; // X position of the lines
		int y = 10; // Y position (start of the title bar)

		// Draw three horizontal lines
		for (int i = 0; i < 3; i++) {
			graphics.DrawLine(&pen, x, y + i * (offset + 3), x + width, y + i * (offset + 3));
		}

		ReleaseDC(hwnd, hdc);
		return 1;
	}

	case WM_DESTROY:
		// Cleanup GDI+
		GdiplusShutdown(gdiplusToken);
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hwnd, msg, wp, lp);
	}
	return 0;
}

int main() {
	// Define window class
	WNDCLASS wc = {0};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = "SimpleHamburgerMenuClass";

	if (!RegisterClass(&wc)) {
		return -1;
	}

	// Create a window with a normal title bar (we won't disable it here)
	HWND hwnd = CreateWindowEx(
		0,
		"SimpleHamburgerMenuClass",
		"Hamburger Menu Example",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	if (hwnd == NULL) {
		return -1;
	}

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
