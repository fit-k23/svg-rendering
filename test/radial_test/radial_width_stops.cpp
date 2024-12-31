#include <windows.h>
#include <gdiplus.h>
#include <cmath>
#include <iostream>

using namespace Gdiplus;
using namespace std;

Color InterpolateColor(const Color& color1, const Color& color2, float t) {
    BYTE r = static_cast<BYTE>(color1.GetR() + t * (color2.GetR() - color1.GetR()));
    BYTE g = static_cast<BYTE>(color1.GetG() + t * (color2.GetG() - color1.GetG()));
    BYTE b = static_cast<BYTE>(color1.GetB() + t * (color2.GetB() - color1.GetB()));
    BYTE a = static_cast<BYTE>(color1.GetA() + t * (color2.GetA() - color1.GetA()));
    return Color(a, r, g, b);
}

// Function to draw a radial gradient with three color stops
void DrawRadialGradient(HDC hdc, int width, int height) {

    // Create a Bitmap to hold the gradient
    Bitmap bitmap(width, height, PixelFormat32bppARGB);
    Graphics graphics(&bitmap);

    // Define gradient properties
    PointF innerCenter(width / 2.0f, height / 2.0f);  // Inner circle center
    PointF outerCenter(width / 2.0f, height / 2.0f);  // Outer circle center
//    float innerRadius = width / 4.0f;                 // Inner circle radius
    float innerRadius = 0.0f;
    float outerRadius = width / 2.0f;                 // Outer circle radius

    // Define gradient colors
    Color red(255, 255, 0, 0);    // Red
    Color blue(0, 0, 0, 255);   // Blue
    Color yellow(255, 255, 255, 0); // Yellow

    // Loop through every pixel to calculate the color
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Calculate distance from the center of the gradient (distance from inner and outer circle centers)
            float dx = x - innerCenter.X;
            float dy = y - innerCenter.Y;
            float distance = std::sqrt(dx * dx + dy * dy);

            // Calculate interpolation factor t based on distance
            float t = (distance - innerRadius) / (outerRadius - innerRadius);
            t = max(0.0f, min(1.0f, t));  // Clamp t to [0, 1]

            // Interpolate color based on three stops
            Color pixelColor;
            if (t < 0.5f) {
                // Interpolate between red and blue for 0.0 <= t < 0.5
                float t_red_blue = t * 2.0f;  // Scale t to [0, 1] range
                pixelColor = InterpolateColor(red, blue, t_red_blue);
            } else {
                // Interpolate between blue and yellow for 0.5 <= t <= 1.0
                float t_blue_yellow = (t - 0.5f) * 2.0f;  // Scale t to [0, 1] range
                pixelColor = InterpolateColor(blue, yellow, t_blue_yellow);
            }

            // Set pixel color in the bitmap
            bitmap.SetPixel(x, y, pixelColor);
        }
    }

    // Create a TextureBrush to use the gradient bitmap
    TextureBrush textureBrush(&bitmap);

    // Draw a rectangle with the gradient brush
    Graphics windowGraphics(hdc);
    windowGraphics.FillRectangle(&textureBrush, 0, 0, width, height);
}

// WinMain entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Initialize window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = [](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT {
        if (msg == WM_PAINT) {
            PAINTSTRUCT ps;
        	HDC hdc = BeginPaint(hwnd, &ps);
        	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
        	FillRect(hdc, &ps.rcPaint, brush);
            DrawRadialGradient(hdc, 800, 800);  // Draw gradient
            EndPaint(hwnd, &ps);
            return 0;
        }
		if (msg == WM_DESTROY) {
            PostQuitMessage(0);
            return 0;
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    };
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("RadialGradientWindow");

    RegisterClass(&wc);

    // Create and show the window
    HWND hwnd = CreateWindow(wc.lpszClassName, TEXT("Radial Gradient Example"),
                             WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                             800, 800, nullptr, nullptr, hInstance, nullptr);
    ShowWindow(hwnd, nCmdShow);

	// Initialize GDI+
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	GdiplusShutdown(gdiplusToken);
    return 0;
}
