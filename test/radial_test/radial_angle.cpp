#include <windows.h>
#include <gdiplus.h>
#include <cmath>

#include <iostream>

using namespace Gdiplus;
using namespace std;

// Function to interpolate between two colors
Color InterpolateColor(const Color& color1, const Color& color2, float t) {
    BYTE r = static_cast<BYTE>(color1.GetR() + t * (color2.GetR() - color1.GetR()));
    BYTE g = static_cast<BYTE>(color1.GetG() + t * (color2.GetG() - color1.GetG()));
    BYTE b = static_cast<BYTE>(color1.GetB() + t * (color2.GetB() - color1.GetB()));
    BYTE a = static_cast<BYTE>(color1.GetA() + t * (color2.GetA() - color1.GetA()));
    return Color(a, r, g, b);
}

// Function to draw a radial gradient using angle-based interpolation
void DrawRadialGradient(HDC hdc, int width, int height) {

    // Create a Bitmap for the gradient
    Bitmap bitmap(width, height, PixelFormat32bppARGB);
    Graphics graphics(&bitmap);

    // Gradient properties
    PointF innerCenter(width / 2.0f, height / 2.0f);  // Inner circle center
    PointF outerCenter(width / 2.0f, height / 2.0f);  // Outer circle center
    float innerRadius = width / 4.0f;                 // Inner circle radius
    float outerRadius = width / 2.0f;                 // Outer circle radius

    // Gradient colors
    Color innerColor(0, 0, 0, 0);  // Red
    Color outerColor(255, 0, 0, 255);  // Blue

    // Loop through angles from 0 to 360 degrees
    const int steps = 360;  // Number of angular steps
    for (float angle = 0; angle < steps; angle += 0.1f) {
        float theta = angle * (3.141592653589793f / 180.0f);  // Convert to radians

        // Calculate start and end points for the current angle
        PointF innerPoint(innerCenter.X + innerRadius * cos(theta),innerCenter.Y + innerRadius * sin(theta));
        PointF outerPoint(outerCenter.X + outerRadius * cos(theta),outerCenter.Y + outerRadius * sin(theta));

        // Draw the gradient along this radial line
        for (float t = 0; t <= 1.0f; t += 0.001f) {  // Interpolation factor
            float x = innerPoint.X + t * (outerPoint.X - innerPoint.X);
            float y = innerPoint.Y + t * (outerPoint.Y - innerPoint.Y);

            // Interpolate color
            Color pixelColor = InterpolateColor(innerColor, outerColor, t);

            // Set the pixel in the bitmap
            bitmap.SetPixel(static_cast<int>(x), static_cast<int>(y), pixelColor);
        }
    }

	if (innerRadius != 0) {
		Graphics graphic(&bitmap);
		SolidBrush solidBrush(innerColor);
		graphic.FillEllipse(&solidBrush, innerCenter.X - innerRadius, innerCenter.Y - innerRadius - 1, 2 * innerRadius + 1, 2 * innerRadius + 1);
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
        } else if (msg == WM_DESTROY) {
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

	// Shut down GDI+
	GdiplusShutdown(gdiplusToken);
    return 0;
}
