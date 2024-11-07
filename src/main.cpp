#include <iostream>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include "element/utils/SVGColor.h"
#include "api/XMLParser.h"
#include "api/parser/ParserManager.h"
#include "api/Renderer.h"
#include "api/Graphic.h"

#include <cmath>
#pragma comment (lib, "Gdiplus.lib")

#include <chrono>

float getSineValueByTime(float time, float frequency = 1.0f, float amplitude = 1.0f, float phaseShift = 0.0f) {
	// Time-based sine calculation
	return amplitude * std::sin(2.0f * M_PI * frequency * time + phaseShift);
}

void draw(HDC hdc, const std::string &fileName) {
	Gdiplus::Graphics graphics(hdc);
	std::vector<Element*> v;
	XMLParser parser;
	parser.traverseXML(fileName, v);

	graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	graphics.SetTextContrast(100);
	graphics.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
	graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
	graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);

	Renderer render = Renderer(parser.getViewPort(), v, {800, 700});
	graphics.ScaleTransform(0.5, .5);
	render.draw(graphics);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow) {
	HWND hWnd;
	MSG msg;
	WNDCLASS wndClass;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

//	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = TEXT("SVG-Renderer");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(TEXT("SVG-Renderer"),   // window class name
						TEXT("SVG-Renderer"),  // window caption
						WS_OVERLAPPEDWINDOW,      // window style
						CW_USEDEFAULT,            // initial x position
						CW_USEDEFAULT,            // initial y position
						1000,            // initial x size
						500,            // initial y size
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

	Gdiplus::GdiplusShutdown(gdiplusToken);
	delete &ParserManager::getInstance();
	return msg.wParam; // NOLINT(*-narrowing-conversions)
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message) {
		case WM_PAINT: {
			hdc = BeginPaint(hWnd, &ps);

			RECT rect;
			::GetClientRect(hWnd, &rect);

			int width = rect.right - rect.left;
			int height = rect.right - rect.left;

			HDC hdcMem = CreateCompatibleDC(hdc);
			HBITMAP hbmMem = CreateCompatibleBitmap(hdc, width, height);

			HGDIOBJ hOld = SelectObject(hdcMem, hbmMem);
//			SetBkColor(hdcMem, RGB(255, 255, 255));

			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));  // White brush
			FillRect(hdcMem, &rect, hBrush);
			DeleteObject(hBrush);

			// Draw into hdcMem here
			draw(hdcMem, "sample.svg");
//			draw(hdc, "sample.svg");

			// Transfer the off-screen DC to the screen

			BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);

			// Free-up the off-screen DC
			SelectObject(hdcMem, hOld);

			DeleteObject(hbmMem);
			DeleteDC (hdcMem);
			EndPaint(hWnd, &ps);
			return 0;
		}
		case WM_ERASEBKGND:
			return 1;
		case WM_KEYDOWN: {
			std::string tmp = "start cmd /k echo \"";
			tmp += static_cast<char>(wParam);
			tmp += "\"";
			if (static_cast<char>(wParam) == 'R') {
				RECT rect;
				::GetClientRect(hWnd, &rect);
				::RedrawWindow(hWnd, &rect, nullptr, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
				InvalidateRect(hWnd, NULL, TRUE);
			} else {
				system(tmp.c_str());
			}
			return 0;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
