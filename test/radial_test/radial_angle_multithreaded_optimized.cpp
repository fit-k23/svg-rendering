#include <windows.h>
#include <gdiplus.h>
#include <cmath>
#include <thread>
#include <vector>
#include <algorithm>

using namespace Gdiplus;

// Structure for defining color stops
struct Stop {
    float offset;  // The position of the stop (0.0 to 1.0)
    Color color;   // Color at this stop
    float opacity; // Opacity at this stop (1.0 = fully opaque, 0.0 = fully transparent)

    Stop(float offset, Color color, float opacity = 1.0f)
        : offset(offset), color(color), opacity(opacity) {}
};

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

std::vector<Stop> gradientStops = {
    Stop(0.0f, Color(255, 255, 0)),             // Yellow at 0%
    Stop(0.5f, Color(0, 0, 255)),             // Blue at 50%
    Stop(0.75f, Color(0, 0, 0, 0), 0.0f),      // Transparent black at 75%
    Stop(1.0f, Color(255, 255, 0))             // Yellow at 100%
};

#ifndef RAD2DEG
#ifndef M_PI_F
#define M_PI_F 3.1415927f
#endif
#define RAD2DEG(angle) ((angle) / M_PI_F * 180.0f + ((angle) < 0 ? 360.0f : 0))
#define DEG2RAD(angle) (((angle) - ((angle) < 0 ? 360.0f : 0)) / 180.0f * M_PI_F)
#endif

// Thread function to draw a portion of the radial gradient
void DrawGradientSegment(Color *pixelData, RectF boundingBox, float startAngle, float endAngle) {
#pragma omp parallel for simd
    for (float angle = startAngle; angle < endAngle; angle += 0.1f) {
        float theta = DEG2RAD(angle); // Convert to radians
		float thetaCos = cos(theta);
		float thetaSin = sin(theta);

        PointF innerPoint(innerCenter.X + innerRadius * thetaCos, innerCenter.Y + innerRadius * thetaSin);
        PointF outerPoint(outerCenter.X + outerRadius * thetaCos, outerCenter.Y + outerRadius * thetaSin);

		int cur = 1;
		int oldCur = 0;
#pragma omp simd
        for (float t = 0; t <= 1.0f; t += 0.001f) {  // Interpolation factor
            int x = innerPoint.X + t * (outerPoint.X - innerPoint.X);
            int y = innerPoint.Y + t * (outerPoint.Y - innerPoint.Y);

			if (t > gradientStops[cur].offset) {
				oldCur = cur++;
			}
            // Ensure x, y are within bounds
            if (x >= 0 && x < boundingBox.Width && y >= 0 && y < boundingBox.Height) {
            	float normalizedT = (t - gradientStops[oldCur].offset) / (gradientStops[cur].offset - gradientStops[oldCur].offset);
                Color pixelColor = InterpolateColor(gradientStops[oldCur].color, gradientStops[cur].color, normalizedT);

                // Set the pixel in the shared buffer
                int index = (y + boundingBox.Y) * (boundingBox.Width + boundingBox.X) + x + boundingBox.X;
                pixelData[index] = pixelColor;
            }
        }
    }
}

// Drawing radial gradient
void DrawRadialGradient(HDC hdc, RectF boundingBox) {
    innerCenter = PointF(boundingBox.Width / 3.0f, boundingBox.Height / 2.0f);
    outerCenter = PointF(boundingBox.Width / 2.0f, boundingBox.Height / 2.0f);
//    innerRadius = boundingBox.Width / 4.0f;
    innerRadius = 0;
    outerRadius = boundingBox.Width / 2.0f;

    // Allocate a buffer for pixel data
    std::vector<Color> pixelData((boundingBox.X + boundingBox.Width) * (boundingBox.Height + boundingBox.Y), Color(0, 0, 0, 0));

    const int numThreads = 8;  // Number of threads
    float angleStep = 360.0f / numThreads;
    std::vector<std::thread> threads;

    // Create threads to process portions of the gradient
    for (int i = 0; i < numThreads; ++i) {
        float startAngle = i * angleStep;
        float endAngle = (i + 1) * angleStep;
        threads.emplace_back(DrawGradientSegment, pixelData.data(), boundingBox, startAngle, endAngle);
    }

    for (auto &t : threads) {
        t.join();
    }

//	if (gradientStops.back().color.GetA() != 0) {
//		Color outerColor = gradientStops.back().color;
//#pragma omp parallel for simd
//		for (int i = 0; i < boundingBox.Width; ++i) {
//			for (int j = 0; j < boundingBox.Height; ++j) {
//				float dx = i - outerCenter.X;
//				float dy = j - outerCenter.Y;
//				float distanceSquared = dx * dx + dy * dy; // Using squared distance to avoid sqrt
//
//				if (distanceSquared > outerRadius * outerRadius) {
//					int index = (j + boundingBox.Y) * boundingBox.Width + i + boundingBox.X;
//					pixelData[index] = outerColor;
//				}
//			}
//		}
//	}

    Bitmap bitmap(boundingBox.X + boundingBox.Width, boundingBox.Y + boundingBox.Height, PixelFormat32bppARGB);
    BitmapData bitmapData;
    Rect rect(0, 0, boundingBox.Width + boundingBox.X, boundingBox.Height + boundingBox.Y);

    bitmap.LockBits(&rect, ImageLockModeWrite, PixelFormat32bppARGB, &bitmapData);

    memcpy(bitmapData.Scan0, pixelData.data(), pixelData.size() * sizeof(Color));

    // Unlock the bitmap
    bitmap.UnlockBits(&bitmapData);

	if (innerRadius != 0) {
		Graphics graphic(&bitmap);
		SolidBrush solidBrush(gradientStops[0].color);
		graphic.FillEllipse(&solidBrush, innerCenter.X - innerRadius, innerCenter.Y - innerRadius - 1, 2 * innerRadius + 1, 2 * innerRadius + 1);
	}

    // Drawing on the window
    Graphics windowGraphics(hdc);
    TextureBrush textureBrush(&bitmap);
    windowGraphics.FillRectangle(&textureBrush, boundingBox.X, boundingBox.Y, boundingBox.Width, boundingBox.Height);
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
			RectF boundingBox(100, 100, 800, 500);
            DrawRadialGradient(hdc, boundingBox);  // Draw gradient
            EndPaint(hwnd, &ps);
            return 0;
        }
        if (msg == WM_KEYDOWN) {
            if (wParam == 'R') {
                InvalidateRect(hwnd, nullptr, false);
            }
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

    // Shut down GDI+
    GdiplusShutdown(gdiplusToken);
    return 0;
}
