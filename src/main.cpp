#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include "element/utils/SVGColor.h"

using namespace Gdiplus;
#pragma comment (lib, "Gdiplus.lib")

void OnPaint(HDC hdc) {
	Graphics graphics(hdc);
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias8x8);
	graphics.SetTextContrast(100);
	graphics.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
	graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
	graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);

	Pen pen(Color(220, 255, 0, 0), 10);  // Red color, 3 pixel width

	// Set up the ellipse parameters
	REAL x = 50.0f, y = 50.0f, width = 200.0f, height = 100.0f;
	graphics.DrawEllipse(&pen, x, y, width, height);
	graphics.DrawEllipse(&pen, x + 200, y, width, width);
	SolidBrush whiteBrush(SVG_YELLOW);
	graphics.FillEllipse(&whiteBrush, 200, 100, 150, 50);

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow) {
	HWND hWnd;
	MSG msg;
	WNDCLASS wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = TEXT("GettingStarted");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(TEXT("GettingStarted"),   // window class name
						TEXT("Getting Started"),  // window caption
						WS_OVERLAPPEDWINDOW,      // window style
						CW_USEDEFAULT,            // initial x position
						CW_USEDEFAULT,            // initial y position
						CW_USEDEFAULT,            // initial x size
						CW_USEDEFAULT,            // initial y size
						nullptr,                  // parent window handle
						nullptr,                  // window menu handle
						hInstance,                // program instance handle
						nullptr);                 // creation parameters

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);
	return msg.wParam; // NOLINT(*-narrowing-conversions)
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message) {
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			OnPaint(hdc);
			EndPaint(hWnd, &ps);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
