#include <windows.h>
#include <gdiplus.h>
#include <iostream>

using namespace Gdiplus;

// Global GDI+ token
ULONG_PTR gdiPlusToken;

// Gradient colors
Color startColor(255, 255, 0, 0); // Red
Color endColor(255, 0, 0, 255); // Blue

// Function to calculate the gradient color based on position (interpolation)
Color InterpolateColor(Color startColor, Color endColor, float t) {
	int r = (int)(startColor.GetR() + (endColor.GetR() - startColor.GetR()) * t);
	int g = (int)(startColor.GetG() + (endColor.GetG() - startColor.GetG()) * t);
	int b = (int)(startColor.GetB() + (endColor.GetB() - startColor.GetB()) * t);
	int a = (int)(startColor.GetA() + (endColor.GetA() - startColor.GetA()) * t);

	return Color(a, r, g, b);
}

// Window procedure to handle messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_PAINT: {
		// Prepare graphics context
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		Graphics graphics(hdc);

		// Get the window size
		RECT rect;
		GetClientRect(hwnd, &rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		// Manually create a custom gradient by interpolating colors
		for (int y = 0; y < height; y++) {
			// Interpolation factor (t) based on vertical position
			float t = (float) y / (float)(height - 1);

			// Calculate the gradient color for the current line
			Color lineColor = InterpolateColor(startColor, endColor, t);

			// Create a solid brush with the interpolated color
			SolidBrush solidBrush(lineColor);

			// Draw a horizontal line (single pixel wide) at position 'y'
			graphics.FillRectangle(&solidBrush, 0, y, width, 1);
		}

		EndPaint(hwnd, &ps);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

// Entry point of the application
int main() {
	// Initialize GDI+
	GdiplusStartupInput gdiPlusStartupInput;
	GdiplusStartup(&gdiPlusToken, &gdiPlusStartupInput, NULL);

	// Define window class
	WNDCLASS wc = {0};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = "Custom Gradient Window";

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONERROR);
		return 1;
	}

	// Create window
	HWND hwnd = CreateWindowEx(
		0,
		"Custom Gradient Window",
		"Custom Gradient Example",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
		NULL, NULL, wc.hInstance, NULL
	);

	if (!hwnd) {
		MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONERROR);
		return 1;
	}

	// Show the window
	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	// Main message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Shutdown GDI+
	GdiplusShutdown(gdiPlusToken);

	return 0;
}
