#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <vector>

using namespace Gdiplus;

ULONG_PTR gdiPlusToken;

struct ColorStop{
    float position;
    Color color;
};

Color InterpolateColor(const Color &color1, const Color &color2, float t) {
    int r = (int)(color1.GetR() + (color2.GetR() - color1.GetR()) * t);
    int g = (int)(color1.GetG() + (color2.GetG() - color1.GetG()) * t);
    int b = (int)(color1.GetB() + (color2.GetB() - color1.GetB()) * t);
    int a = (int)(color1.GetA() + (color2.GetA() - color1.GetA()) * t);
    return Color(a, r, g, b);
}

float skip = 1.0f;
Bitmap *CreateCustomGradientBitmap(const std::vector<ColorStop> &stops, Rect rect, float r = 0.5, float cx = 0.5f, float cy = 0.5f, float fx = 0.5f, float fy = 0.5f, float fr = 0.0f) {
    Bitmap* gradientBitmap = new Bitmap(rect.X + rect.Width, rect.Y + rect.Height, PixelFormat32bppARGB);
	Graphics graphics(gradientBitmap);
//	{
//		SolidBrush brush(Color(255, 0,0, 0));
// //		SolidBrush brush(stops.back().color);
//    	graphics.FillRectangle(&brush, rect);
//	}
    Pen pen(Color(0,0,0,0), 1.000f);

	int width = rect.Width;
	int height = rect.Height;

	int focusX = fx * width; // start circle center x
	int focusY = fy * height; // start circle center y
	int centerX = cx * width; // end circle center x
	int centerY = cy * height; // end circle center y

	float radius = r * width;

	float diffX = centerX - focusX;
	float diffY = centerY - focusY;

	float maxDistance = width;
	int cur = 1;
	int oldCur = 0;

//	const float skip = 1.0f;

	for (float i = 0; i < maxDistance; i += skip) {
		float t = i / (maxDistance - 1);

		float posR = radius * t;
		float posX = rect.X + focusX + diffX * t - posR;
		float posY = rect.Y + focusY + diffY * t - posR;

		if (t > stops[cur].position) {
//			pen.SetColor(Color(255,0,0,0));
//			graphics.DrawRectangle(&pen, posX, posY, 2.0 * posR, 2.0 * posR);
			oldCur = cur++;
		}
		float factor = (t - stops[oldCur].position) / (stops[cur].position - stops[oldCur].position);
		Color color = InterpolateColor(stops[oldCur].color, stops[cur].color, factor);
//		color = Color(color.GetA(), color.GetR(), color.GetG(), color.GetB() + int(i % 256));
		pen.SetColor(color);
		graphics.DrawEllipse(&pen, posX, posY, 2 * posR, 2 * posR);
	}
    return gradientBitmap;
}

// Global variable to track the rotation angle
float rotationAngle = 0.0f;
float fx = 0.5;
float fy = 0.5;
Rect rect2 = {50, 50, 1000, 1000};


// Window procedure to handle messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: {
        // Prepare graphics context
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Get the window size

        RECT rect;
        GetClientRect(hwnd, &rect);
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;

        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height);
        SelectObject(hdcMem, hBitmap);

        HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(hdcMem, &rect, hBrush);

        Graphics graphics(hdcMem);

        std::vector<ColorStop> stops = {
            {0.0f, Color(255, 0, 0, 255)}, // Blue
//            {0.5f, Color(255, 0, 255, 0)}, // Green
            {1.0f, Color(0, 0, 0, 0)} // Red
        };

    	int centerX = rect2.X + rect2.Width / 2;
    	int centerY = rect2.Y + rect2.Height / 2;

    	graphics.TranslateTransform(centerX, centerY);
    	graphics.RotateTransform(rotationAngle);
    	graphics.TranslateTransform(-centerX, -centerY);

        Bitmap *gradientBitmap = CreateCustomGradientBitmap(stops, rect2, 0.5, 0.5, 0.5, fx, fy);

        TextureBrush textureBrush(gradientBitmap);

        Pen pen(Color(255, 0, 255, 255), 10);
        graphics.DrawRectangle(&pen, rect2);
        graphics.FillRectangle(&textureBrush, rect2);

        delete gradientBitmap;

        BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);
        DeleteDC(hdcMem);
        DeleteObject(hBitmap);

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_ERASEBKGND: {
        return 0;
    }
    case WM_KEYDOWN: {
        // Check if W or S is pressed and adjust the rotation angle
        if (wParam == 'W') {
            rotationAngle += 2.0f; // Rotate clockwise
        }
        if (wParam == 'S') {
            rotationAngle -= 2.0f; // Rotate counterclockwise
        }
		if (wParam == 'A') {
			if (skip > 0.01f) {
				skip -= 0.01f;
			}
		}
		if (wParam == 'D') {
			skip += 0.01f;
		}
    	SetWindowText(hwnd, (std::string("Skip: " + std::to_string(skip))).c_str());
        // Redraw the window to reflect the updated rotation
        InvalidateRect(hwnd, nullptr, false);
        return 0;
    }
    case WM_MOUSEMOVE: {
		POINT pt = {LOWORD(lParam), HIWORD(lParam)};
		if (pt.x < rect2.X || pt.y < rect2.Y || pt.x >= rect2.Width + rect2.X || pt.y >= rect2.Height + rect2.Y) {
			break;
		}
		fx = (pt.x - rect2.X) * 1.0f / rect2.Width;
		fy = (pt.y - rect2.Y) * 1.0f / rect2.Height;
		InvalidateRect(hwnd, nullptr, false);
		break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int main() {
    GdiplusStartupInput gdiPlusStartupInput;
    GdiplusStartup(&gdiPlusToken, &gdiPlusStartupInput, nullptr);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "Custom Gradient Window";

    if (!RegisterClass(&wc)) {
        MessageBox(nullptr, "Window Registration Failed!", "Error", MB_ICONERROR);
        return 1;
    }

    HWND hwnd = CreateWindowEx(
        0,
        "Custom Gradient Window", // Use ANSI window title
        "Custom Gradient Example", // Use ANSI window title
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1200, 900,
        nullptr, nullptr, wc.hInstance, nullptr
    );

    if (!hwnd) {
        MessageBox(nullptr, "Window Creation Failed!", "Error", MB_ICONERROR);
        return 1;
    }

    // Show the window
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Shutdown GDI+
    GdiplusShutdown(gdiPlusToken);

    return 0;
}
