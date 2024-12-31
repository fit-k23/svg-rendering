#include <windows.h>
#include <gdiplus.h>
#include <cmath>
#include <vector>

using namespace Gdiplus;
using namespace std;

// Structure to hold color and its stop
struct ColorStop {
    float stop;  // Position of the color stop (from 0 to 1)
    Color color; // The color at this stop
};

// Function to interpolate between two colors
Color InterpolateColor(const Color& color1, const Color& color2, float t) {
    BYTE r = static_cast<BYTE>(color1.GetR() + t * (color2.GetR() - color1.GetR()));
    BYTE g = static_cast<BYTE>(color1.GetG() + t * (color2.GetG() - color1.GetG()));
    BYTE b = static_cast<BYTE>(color1.GetB() + t * (color2.GetB() - color1.GetB()));
    BYTE a = static_cast<BYTE>(color1.GetA() + t * (color2.GetA() - color1.GetA()));
    return Color(a, r, g, b);
}

// Function to find the color for a specific position based on color stops
Color GetGradientColor(const vector<ColorStop>& colorStops, float t) {
    // Ensure that the value of t is between 0 and 1
    t = max(0.0f, min(t, 1.0f));

    // Find the correct segment between color stops
    for (size_t i = 0; i < colorStops.size() - 1; ++i) {
        if (t >= colorStops[i].stop && t <= colorStops[i + 1].stop) {
            float segmentT = (t - colorStops[i].stop) / (colorStops[i + 1].stop - colorStops[i].stop);
            return InterpolateColor(colorStops[i].color, colorStops[i + 1].color, segmentT);
        }
    }
    return colorStops.back().color;  // If t is at or beyond the last stop, return the last color
}

// Function to draw a radial gradient using angle-based interpolation
void DrawRadialGradient(HDC hdc, int width, int height) {

    // Create a Bitmap for the gradient
    Bitmap bitmap(width, height, PixelFormat32bppARGB);
    Graphics graphics(&bitmap);

    // Gradient properties
    PointF innerCenter(width / 2.0f, height / 2.0f);  // Inner circle center
    PointF outerCenter(width / 2.0f, height / 2.0f);  // Outer circle center
//    float innerRadius = width / 4.0f;                 // Inner circle radius
    float innerRadius = 0;                 // Inner circle radius
    float outerRadius = width / 2.0f;                 // Outer circle radius

    // Define the color stops
    vector<ColorStop> colorStops = {
        {0.0f, Color(255, 255, 255, 0)},      // Red
        {0.5f, Color(255, 0, 0, 255)},     // Blue
        {0.75f, Color(0, 0, 0, 0)},          // Transparent (black with opacity 0)
        {1.0f, Color(255, 255, 255, 0)}     // Yellow
    };

    // Loop through angles from 0 to 360 degrees
    const int steps = 360;  // Number of angular steps
    for (float angle = 0; angle < steps; angle += 0.1f) {
        float theta = angle * (3.141592653589793f / 180.0f);  // Convert to radians

        // Calculate start and end points for the current angle
        PointF innerPoint(innerCenter.X + innerRadius * cos(theta), innerCenter.Y + innerRadius * sin(theta));
        PointF outerPoint(outerCenter.X + outerRadius * cos(theta), outerCenter.Y + outerRadius * sin(theta));

        // Draw the gradient along this radial line
        for (float t = 0; t <= 1.0f; t += 0.001f) {  // Interpolation factor
            float x = innerPoint.X + t * (outerPoint.X - innerPoint.X);
            float y = innerPoint.Y + t * (outerPoint.Y - innerPoint.Y);

            // Get the interpolated color for the current position
            Color pixelColor = GetGradientColor(colorStops, t);

            // Set the pixel in the bitmap
            bitmap.SetPixel(x, y, pixelColor);
        }
    }

	if (innerRadius != 0) {
		Graphics graphic(&bitmap);
		SolidBrush solidBrush(colorStops[0].color);
		graphic.FillEllipse(&solidBrush, innerCenter.X - innerRadius, innerCenter.Y - innerRadius - 1, 2 * innerRadius + 1, 2 * innerRadius + 1);
	}

	if (colorStops.back().color.GetA() != 0) {
		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				float dx = i - outerCenter.X;
				float dy = j - outerCenter.Y;
				float distance = std::sqrt(dx * dx + dy * dy);
				if (distance > outerRadius) {
					bitmap.SetPixel(i, j, colorStops.back().color);
				}
			}
		}
	}

    // Draw the gradient on the window
    Graphics windowGraphics(hdc);
    windowGraphics.DrawImage(&bitmap, 0, 0);
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
