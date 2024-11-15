#pragma comment (lib, "Gdiplus.lib")
#include <iostream>
#include <windows.h>

#include <gdiplus.h>
#include "api/XMLParser.h"
#include "api/Camera.h"
#include "api/Renderer.h"
#include "api/Graphic.h"
#include "api/FileManager.h"
#include "api/parser/ParserManager.h"
#include "api/parser/ParserHInit.h"

#define APPLICATION_CLASS_NAME "SVGRendering-Group11"
#define APPLICATION_TITLE_NAME "SVG Renderer"


void ProjectInit() {
	ParserManager::registerParser("svg", new SVGParser);
	ParserManager::registerParser("float", new FloatParser);
	ParserManager::registerParser("color", new ColorParser);
	ParserManager::registerParser("string", new StringParser);
}

void ProjectDeInit() {
	ParserManager::free();
}

void ProjectDraw(HDC hdc, const std::string &fileName) {
	Gdiplus::Graphics graphics(hdc);
	std::vector<Element *> v;
	XMLParser parser;
	parser.traverseXML(fileName, v);

	graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	graphics.SetTextContrast(100);
	graphics.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
	graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
	graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);

	float centerX = GetSystemMetrics(SM_CXSCREEN) / 2.0f;
	float centerY = GetSystemMetrics(SM_CYSCREEN) / 2.0f;

	Renderer render = Renderer(parser.getViewPort(), v, {2 * centerX, 2 * centerY});

	graphics.TranslateTransform(Camera::position.x, Camera::position.y);
//	graphics.TranslateTransform(centerX, centerY);
	graphics.ScaleTransform(Camera::zoom, Camera::zoom);
	graphics.RotateTransform(Camera::rotation);
//	graphics.TranslateTransform(-centerX, -centerY);
	graphics.TranslateTransform(-Camera::position.x, -Camera::position.y);
	render.draw(graphics);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int main() {
	MSG msg;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	WNDCLASS wndClass;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = TEXT(APPLICATION_CLASS_NAME);

	RegisterClass(&wndClass);

	HWND hWnd = CreateWindow(TEXT(APPLICATION_CLASS_NAME), TEXT(APPLICATION_TITLE_NAME), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 800, nullptr, nullptr, hInstance, nullptr);
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
	PAINTSTRUCT ps;

	switch (message) {
		case WM_PAINT: {
			HDC hdc = BeginPaint(hWnd, &ps);
			// To have a debug terminal in visual studio (bruh)
			//AllocConsole();
			//freopen("CONOUT$", "w", stdout);

			RECT rect;
			::GetClientRect(hWnd, &rect);

			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;

			HDC hdcMem = CreateCompatibleDC(hdc);
			HBITMAP hbmMem = CreateCompatibleBitmap(hdc, width, height);

			HGDIOBJ hOld = SelectObject(hdcMem, hbmMem);
//			SetBkColor(hdcMem, RGB(255, 255, 255));

			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
			FillRect(hdcMem, &rect, hBrush);

			// Draw into hdcMem here
//			ProjectDraw(hdcMem, "asset/text_anchor.svg");
			ProjectDraw(hdcMem, "asset/Zig_logo_2020.svg");
			// Transfer the off-screen DC to the screen

			BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hOld);

			DeleteObject(hBrush);
			DeleteObject(hbmMem);
			DeleteDC(hdcMem);
			EndPaint(hWnd, &ps);
			return 0;
		}
		case WM_ERASEBKGND: {
			return 1;
		}
		case WM_MOUSEWHEEL: {
			int delta = GET_WHEEL_DELTA_WPARAM(wParam);

			if (delta > 0) {
				Camera::zoomIn();
			} else {
				Camera::zoomOut();
			}
			InvalidateRect(hWnd, nullptr, false);
			break;
		}
		case WM_LBUTTONDOWN: {
			Camera::isDragging = true;
			SetCapture(hWnd);
			break;
		}
		case WM_LBUTTONUP: {
			Camera::isDragging = false;
			ReleaseCapture();
			break;
		}
		case WM_MOUSEMOVE: {
			POINT pt = {LOWORD(lParam), HIWORD(lParam)};
			if (Camera::isDragging && GetCapture() != nullptr) {
				Camera::position.x = pt.x;
				Camera::position.y = pt.y;
				InvalidateRect(hWnd, nullptr, false);
			}
			return 0;
		}
		case WM_KEYDOWN: {
			switch (static_cast<char>(wParam)) {
				case 'R': {
					InvalidateRect(hWnd, nullptr, false);
					break;
				}
				case 'W': {
					Camera::zoomIn();
					InvalidateRect(hWnd, nullptr, false);
					break;
				}
				case 'S': {
					Camera::zoomOut();
					InvalidateRect(hWnd, nullptr, false);
					break;
				}
				case 'A': {
					Camera::rotateClockWise();
					InvalidateRect(hWnd, nullptr, false);
					break;
				}
				case 'D': {
					Camera::rotateCounterClockWise();
					InvalidateRect(hWnd, nullptr, false);
					break;
				}
				default: {

				}
			}
			return 0;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
