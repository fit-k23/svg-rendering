#include <windows.h>
#include <windowsx.h>
#include <gdiplus.h>
#include <cmath>

using namespace Gdiplus;

HINSTANCE hInstance;
HWND hWnd;
PointF mousePos(0, 0);
REAL rotationAngle = 0.0f; // Initial rotation angle
REAL zoomFactor = 1.0f; // Initial zoom factor

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static Graphics* graphics = nullptr;
	HDC hdc;

	switch (uMsg) {
		case WM_CREATE:
			return 0;

		case WM_MOUSEMOVE: {
			// Get the current mouse position
			mousePos.X = GET_X_LPARAM(lParam);
			mousePos.Y = GET_Y_LPARAM(lParam);
			InvalidateRect(hwnd, NULL, TRUE);  // Trigger a redraw
			return 0;
		}

		case WM_LBUTTONDOWN: {
			// Handle mouse click (optional)
			mousePos.X = GET_X_LPARAM(lParam);
			mousePos.Y = GET_Y_LPARAM(lParam);
			InvalidateRect(hwnd, NULL, TRUE);  // Trigger a redraw
			return 0;
		}

		case WM_KEYDOWN: {
			// Rotate with A/D keys
			if (wParam == 'A') {
				rotationAngle -= 5.0f;  // Rotate counterclockwise
			} else if (wParam == 'D') {
				rotationAngle += 5.0f;  // Rotate clockwise
			}
			// Zoom in/out with W/S keys
			if (wParam == 'W') {
				zoomFactor += 0.1f;  // Zoom in
			} else if (wParam == 'S') {
				zoomFactor -= 0.1f;  // Zoom out
				if (zoomFactor < 0.1f) zoomFactor = 0.1f; // Prevent zooming out too much
			}
			InvalidateRect(hwnd, NULL, TRUE);  // Trigger a redraw on key press
			return 0;
		}

		case WM_PAINT: {
			hdc = GetDC(hwnd);
			graphics = new Graphics(hdc);

			// Create the transformation matrix
			Matrix transform;

			// Step 1: Translate to the mouse position (set mouse position as the origin)
			transform.Translate((REAL)mousePos.X, (REAL)mousePos.Y);

			// Step 2: Apply rotation around the mouse position
			transform.Rotate(rotationAngle);

			// Step 3: Apply zoom (scale) centered around the mouse position
			transform.Scale(zoomFactor, zoomFactor);

			// Step 4: Apply the transformation to the graphics object
			graphics->SetTransform(&transform);

			// Step 5: Draw a filled rectangle (50x50) at the transformed origin
			SolidBrush brush(Color(255, 0, 0, 255));  // Red color
			graphics->FillRectangle(&brush, -25, -25, 50, 50);  // Draw rectangle centered on the mouse position

			delete graphics;
			ReleaseDC(hwnd, hdc);
			return 0;
		}

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int main() {
	// Initialize GDI+
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	hInstance = GetModuleHandle(nullptr);

	WNDCLASS wndClass = {};
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WindowProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = TEXT("GDIDRAWMOUSE");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(TEXT("GDIDRAWMOUSE"), TEXT("GDI DRAW MOUSE"), WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, CW_USEDEFAULT, 1024, 1024, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	// Main message loop
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);  // Shutdown GDI+ at the end
	return static_cast<int>(msg.wParam); // Return the message's result
}
