#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

// Global variables for animation state
int circleX = 50;  // Initial X position of the circle
int circleY = 50;  // Initial Y position of the circle
int circleDirectionX = 5; // Speed in the X direction
int circleDirectionY = 5; // Speed in the Y direction

ULONG_PTR gdiplusToken;  // GDI+ token for initialization

// Function to initialize GDI+
void InitGDIPlus() {
	GdiplusStartupInput gdiPlusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiPlusStartupInput, NULL);
}

// Function to shut down GDI+
void ShutdownGDIPlus() {
	GdiplusShutdown(gdiplusToken);
}

// Timer callback to update the position of the circle
void UpdateAnimation(HWND hWnd) {
	// Update the circle position
	circleX += circleDirectionX;
	circleY += circleDirectionY;

	// Reverse direction if the circle hits the window boundaries
	RECT rect;
	GetClientRect(hWnd, &rect);
	if (circleX < 0 || circleX > rect.right) circleDirectionX = -circleDirectionX;
	if (circleY < 0 || circleY > rect.bottom) circleDirectionY = -circleDirectionY;

	// Redraw the window
	InvalidateRect(hWnd, NULL, TRUE);
}

// Window procedure function
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_CREATE: {
			// Set up a timer to call UpdateAnimation every 20ms (50 FPS)
			SetTimer(hWnd, 1, 20, NULL);
			return 0;
		}
		case WM_TIMER: {
			// Update animation
			UpdateAnimation(hWnd);
			return 0;
		}
		case WM_PAINT: {
			// Paint the window using GDI+
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			Graphics graphics(hdc);

			// Create a brush and draw the circle
			SolidBrush brush(Color(255, 0, 0, 255));  // Blue color
			graphics.FillEllipse(&brush, circleX, circleY, 50, 50);  // Draw circle at (circleX, circleY)

			EndPaint(hWnd, &ps);
			return 0;
		}
		case WM_DESTROY: {
			// Clean up the timer and shut down GDI+
			KillTimer(hWnd, 1);
			PostQuitMessage(0);
			return 0;
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

// Entry point
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Initialize GDI+
	InitGDIPlus();

	// Register the window class
	const char* className = "GDIPlusAnimation";
	WNDCLASS wc = {0};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;
	RegisterClass(&wc);

	// Create the window
	HWND hWnd = CreateWindowEx(
			0, className, "GDI+ Animation", WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
			NULL, NULL, hInstance, NULL
	);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Shut down GDI+
	ShutdownGDIPlus();

	return (int)msg.wParam;
}
