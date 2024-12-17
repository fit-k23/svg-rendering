#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <vector>

using namespace Gdiplus;

ULONG_PTR gdiPlusToken;

struct ColorStop{
    float position; // 0.0 to 1.0
    Color color;
};

Color InterpolateColor(const Color &color1, const Color &color2, float t) {
    int r = (int)(color1.GetR() + (color2.GetR() - color1.GetR()) * t);
    int g = (int)(color1.GetG() + (color2.GetG() - color1.GetG()) * t);
    int b = (int)(color1.GetB() + (color2.GetB() - color1.GetB()) * t);
    int a = (int)(color1.GetA() + (color2.GetA() - color1.GetA()) * t);
    return Color(a, r, g, b);
}

Bitmap *CreateCustomGradientBitmap(RectF rect, const std::vector<ColorStop> &stops, float angle = 0.0f) {
    Bitmap* gradientBitmap = new Bitmap(rect.Width + rect.X, rect.Height + rect.Y);
    Graphics graphics(gradientBitmap);

    int centerX = rect.X + rect.Width / 2;
    int centerY = rect.Y + rect.Height / 2;

    graphics.TranslateTransform(centerX, centerY);
    graphics.RotateTransform(angle);
    graphics.TranslateTransform(-centerX, -centerY);

    SolidBrush solidBrush(Color(0,0,0,0));

    float newWidth = abs(rect.Width * cos(angle / 180.0 * M_PI)) + abs(rect.Height * sin(angle / 180.0 * M_PI));
    rect.X += (rect.Width - newWidth) / 2;
    rect.Width = newWidth;

	int cur = 1;
    int oldCur = 0;

    for (int x = 0; x < rect.Width; ++x) {
        float t = (float) x / (rect.Width - 1);

		Color curColor = stops[cur].color;
		Color oldColor = stops[oldCur].color;

		if (curColor.GetValue() == oldColor.GetValue()) {
			float diff = stops[cur].position - stops[oldCur].position;
			solidBrush.SetColor(curColor);
			graphics.FillRectangle(&solidBrush, x + rect.X, rect.Y - rect.Width / 2, rect.Width * diff + 1.0f,  rect.Y + rect.Height + rect.Width);
			x += rect.Width * diff;
			oldCur = cur;
			++cur;
			continue;
		}

		if (t > stops[cur].position) {
			oldCur = cur;
			++cur;
		}
    	float factor = (t - stops[oldCur].position) / (stops[cur].position - stops[oldCur].position);
		Color gradientColor = InterpolateColor(stops[oldCur].color, stops[cur].color, factor);
        solidBrush.SetColor(gradientColor);
        graphics.FillRectangle(&solidBrush, x + rect.X, rect.Y - rect.Width / 2, 1.0f,  rect.Y + rect.Height + rect.Width);
    }

    return gradientBitmap;
}

// Global variable to track the rotation angle
float rotationAngle = 0.0f;

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
            {0.0f, Color(255, 255, 0, 0)}, // Red
            {0.25f, Color(255, 255, 0, 0)}, // Red
            {0.5f, Color(0, 0, 0, 0)}, // Transparent Black
            {1.0f, Color(255, 0, 0, 255)} // Blue
        };

        Gdiplus::RectF rectF = {100, 50, 500, 250};
        Bitmap *gradientBitmap = CreateCustomGradientBitmap(rectF, stops, rotationAngle);

        TextureBrush textureBrush(gradientBitmap);

        Pen pen(Color(255, 0, 255, 255), 10);
        graphics.DrawRectangle(&pen, 100, 50, 500, 250);

        graphics.FillRectangle(&textureBrush, 100, 50, 500, 250);

        // Clean up
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
        // Redraw the window to reflect the updated rotation
        InvalidateRect(hwnd, nullptr, TRUE);
        return 0;
    }

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
    GdiplusStartup(&gdiPlusToken, &gdiPlusStartupInput, nullptr);

    // Define window class
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "Custom Gradient Window"; // Use ANSI class name

    if (!RegisterClass(&wc)) {
        MessageBox(nullptr, "Window Registration Failed!", "Error", MB_ICONERROR);
        return 1;
    }

    // Create window
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
