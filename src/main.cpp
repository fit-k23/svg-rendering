#include <iostream>
#include <windows.h>

#include "../lib/rapidxml/rapidxml.hpp"
#include "Graphic.h"

#include <objidl.h>
#include <gdiplus.h>

#define APP_ID "svg-rendering"
#define APP_NAME "SVG Render"

using namespace Gdiplus;
#pragma comment (lib, "Gdiplus.lib")

VOID OnPaint(HDC hdc) {
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	graphics.DrawLine(&pen, 0, 0, 200, 100);
	SolidBrush solidBrush(Color(255, 255, 0, 0));
//	Point point1 = Point(0, 0);
//	Point point2 = Point(102, 120);
//	Point point3 = Point(102, 10);
//	Point point4 = Point(10, 299);
//	Point points[4] = {point1,point2,point3,point4};
	Point points[] = {{46,22}, {33,33}, {28,44}, {22,44}, {22,95}, {31,95}, {20,100}, {12,117}, {0,117}, {0,22}};
	graphics.FillPolygon(&solidBrush, points, 10);
	Point point2[] = {{46,22}, {28,44}, {19,30}};
	graphics.FillPolygon(&solidBrush, point2, 3);
	Point point3[] = {{31,95}, {12,117}, {4,106}};
	graphics.FillPolygon(&solidBrush, point3, 3);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow) {
	HWND hWnd;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	WNDCLASS wndClass = {.style = CS_HREDRAW | CS_VREDRAW, .lpfnWndProc = WndProc, .cbClsExtra = 0, .cbWndExtra = 0, .hInstance = hInstance, .hIcon = LoadIcon(nullptr, IDI_APPLICATION), .hCursor = LoadCursor(nullptr, IDC_ARROW), .hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH), .lpszMenuName = nullptr, .lpszClassName = TEXT(APP_ID)};

	RegisterClass(&wndClass);

	hWnd = CreateWindow(TEXT(APP_ID), TEXT(APP_NAME), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);
	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
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