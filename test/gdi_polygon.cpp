#include <windows.h>
#include <gdiplus.h>
#include <vector>

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

std::vector<PointF> points = {
		PointF(-0.06f, 7.97f),
		PointF(11.4f, 7.66f),
		PointF(0.51f, 5.42f),
		PointF(8.7f, -1.1f),
		PointF(0.23f, 2.55f),
		PointF(10.2f, 2.1f),
		PointF(1.74f, -0.56f),
		PointF(6.9f, 10.47f)
};

ULONG_PTR gdiplusToken;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	WNDCLASSW wc = {0};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"PolygonWindowClass";

	RegisterClassW(&wc);

	HWND hwnd = CreateWindowExW(0, L"PolygonWindowClass", L"GDI+ Polygon", WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);

	MSG msg = {0};

	for (auto &point : points) {
		point.X = point.X * 50 + 20;
		point.Y = point.Y * 50 + 20;
	}

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gdiplusToken);
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			Graphics graphics(hdc);
			Pen pen(Color(255, 0, 0, 255), 2);
			graphics.DrawPolygon(&pen, points.data(), points.size());
			SolidBrush brush(Color(128, 0, 0, 255));

			graphics.FillPolygon(&brush, points.data(), points.size(), FillMode::FillModeWinding);
			EndPaint(hwnd, &ps);
			return 0;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
