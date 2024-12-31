#include <windows.h>
#include <gdiplus.h>
#include <cmath>
#include <thread>
#include <vector>

using namespace Gdiplus;

// Function to interpolate between two colors
Color InterpolateColor(const Color& color1, const Color& color2, float t) {
    BYTE r = static_cast<BYTE>(color1.GetR() + t * (color2.GetR() - color1.GetR()));
    BYTE g = static_cast<BYTE>(color1.GetG() + t * (color2.GetG() - color1.GetG()));
    BYTE b = static_cast<BYTE>(color1.GetB() + t * (color2.GetB() - color1.GetB()));
    BYTE a = static_cast<BYTE>(color1.GetA() + t * (color2.GetA() - color1.GetA()));
    return Color(a, r, g, b);
}

// Gradient properties (global for simplicity)
PointF innerCenter;
PointF outerCenter;
float innerRadius;
float outerRadius;
Color innerColor(0, 0, 0, 0);  // Red
Color outerColor(255, 0, 0, 255);  // Blue

#ifndef RAD2DEG
#ifndef M_PI_F
#define M_PI_F 3.1415927f
#endif
#define RAD2DEG(angle) ((angle) / M_PI_F * 180.0f + ((angle) < 0 ? 360.0f : 0))
#define DEG2RAD(angle) (((angle) - ((angle) < 0 ? 360.0f : 0)) / 180.0f * M_PI_F)
#endif

// Thread function to draw a portion of the radial gradient
void DrawGradientSegment(Bitmap *bitmap, float startAngle, float endAngle) {
    for (float angle = startAngle; angle < endAngle; angle += 0.01f) {
        float theta = DEG2RAD(angle); // * (3.141592653589793f / 180.0f);  // Convert to radians

        // Calculate start and end points for the current angle
        PointF innerPoint(innerCenter.X + innerRadius * cos(theta),innerCenter.Y + innerRadius * sin(theta));
        PointF outerPoint(outerCenter.X + outerRadius * cos(theta), outerCenter.Y + outerRadius * sin(theta));

        // Draw the gradient along this radial line
        for (float t = 0; t <= 1.0f; t += 0.001f) {  // Interpolation factor
            float x = innerPoint.X + t * (outerPoint.X - innerPoint.X);
            float y = innerPoint.Y + t * (outerPoint.Y - innerPoint.Y);

            // Interpolate color
            Color pixelColor = InterpolateColor(innerColor, outerColor, t);

            // Set the pixel in the bitmap
            bitmap->SetPixel(x, y, pixelColor);
        }
    }
}

void DrawRadialGradient(HDC hdc, int width, int height) {
    innerCenter = PointF(width / 2.0f, height / 2.0f);
    outerCenter = PointF(width / 2.0f, height / 2.0f);
    innerRadius = width / 4.0f;
    outerRadius = width / 2.0f;

    Bitmap bitmap(width, height, PixelFormat32bppARGB);
    const int numThreads = 8;  // Number of threads
    float angleStep = 360.0f / numThreads;
    std::vector<std::thread> threads;
	std::vector<Bitmap *> threadBitmaps;

	for (int i = 0; i < numThreads; ++i) {
		threadBitmaps.push_back(new Bitmap(width, height, PixelFormat32bppARGB));
	}

    for (int i = 0; i < numThreads; ++i) {
        float startAngle = i * angleStep;
        float endAngle = (i + 1) * angleStep;
        threads.emplace_back(DrawGradientSegment, threadBitmaps[i], startAngle, endAngle);
    }

    // Wait for all threads to complete
    for (auto &t : threads) {
        t.join();
    }

	Graphics graphics(&bitmap);
	if (innerRadius != 0) {
		SolidBrush solidBrush(innerColor);
		graphics.FillEllipse(&solidBrush, innerCenter.X - innerRadius, innerCenter.Y - innerRadius - 1, 2 * innerRadius + 1, 2 * innerRadius + 1);
	}

	for (int i = 0; i < numThreads; ++i) {
//		graphics.DrawImage(threadBitmaps[i], 0, 0);
		for (int w = 0; w < width; ++w) {
			for (int h = 0; h < height; ++h) {
				Color color;
				threadBitmaps[i]->GetPixel(w, h, &color);
				if (color.GetA() != 0) {
					bitmap.SetPixel(w, h, color);
				}
			}
		}
		delete threadBitmaps[i];
	}

    TextureBrush textureBrush(&bitmap);

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
