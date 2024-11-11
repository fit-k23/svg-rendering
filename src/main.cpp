#pragma comment (lib, "Gdiplus.lib")
#include <iostream>
#include <windows.h>

#include <gdiplus.h>
#include "api/XMLParser.h"
#include "api/Renderer.h"
#include "api/Graphic.h"
#include "api/parser/ParserManager.h"
#include "api/parser/ParserHInit.h"

#define APPLICATION_CLASS_NAME "SVGRendering-Group11"
#define APPLICATION_TITLE_NAME "SVG Renderer"

void ProjectInit() {
	ParserManager::getInstance().registerParser("float", new FloatParser());
	ParserManager::getInstance().registerParser("color", new ColorParser());
	ParserManager::getInstance().registerParser("string", new StringParser());
}

void ProjectDraw(HDC hdc, const std::string &fileName) {
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
//	graphics.ScaleTransform(0.5, .5);
	render.draw(graphics);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int main() {
	HWND hWnd;
	MSG msg;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	WNDCLASS wndClass = {
		.style = CS_HREDRAW | CS_VREDRAW,
		.lpfnWndProc = WndProc,
		.cbClsExtra = 0,
		.cbWndExtra = 0,
		.hInstance = hInstance,
		.hIcon = LoadIcon(nullptr, IDI_APPLICATION),
		.hCursor = LoadCursor(nullptr, IDC_ARROW),
		.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH),
		.lpszMenuName = nullptr,
		.lpszClassName = TEXT(APPLICATION_CLASS_NAME),
	};

	RegisterClass(&wndClass);

	hWnd = CreateWindow(TEXT(APPLICATION_CLASS_NAME), TEXT(APPLICATION_TITLE_NAME), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 500, nullptr, nullptr, hInstance, nullptr);
	ProjectInit();

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	// Main message loop
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);
	return static_cast<int>(msg.wParam); // Return the message's result
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message) {
		case WM_PAINT: {
			hdc = BeginPaint(hWnd, &ps);

			// To have a debug terminal in visual studio (bruh)
			//AllocConsole();
			//freopen("CONOUT$", "w", stdout);

			RECT rect;
			::GetClientRect(hWnd, &rect);

			int width = rect.right - rect.left;
			int height = rect.right - rect.left;

			HDC hdcMem = CreateCompatibleDC(hdc);
			HBITMAP hbmMem = CreateCompatibleBitmap(hdc, width, height);

			HGDIOBJ hOld = SelectObject(hdcMem, hbmMem);
//			SetBkColor(hdcMem, RGB(255, 255, 255));

			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
			FillRect(hdcMem, &rect, hBrush);

			// Draw into hdcMem here
			ProjectDraw(hdcMem, "sample.svg");
			// Transfer the off-screen DC to the screen

			BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hOld);
			DeleteObject(hBrush);

			// Free-up the off-screen DC

			DeleteObject(hbmMem);
			DeleteDC (hdcMem);
			EndPaint(hWnd, &ps);
			return 0;
		}
//		case WM_ERASEBKGND:
//			return 1;
		case WM_KEYDOWN: {
			std::string tmp = "start cmd /k echo \"";
			tmp += static_cast<char>(wParam);
			tmp += "\"";
			if (static_cast<char>(wParam) == 'R') {
				RECT rect;
				::GetClientRect(hWnd, &rect);
//				::RedrawWindow(hWnd, &rect, nullptr, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
				::RedrawWindow(hWnd, &rect, nullptr, RDW_INVALIDATE | RDW_NOERASE | RDW_NOFRAME | RDW_UPDATENOW);
//				InvalidateRect(hWnd, nullptr, TRUE);
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
