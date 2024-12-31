#include <windows.h>
#include <gdiplus.h>
#include <cmath>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace Gdiplus;
using namespace std;

Color InterpolateColor(const Color& color1, const Color& color2, float t) {
    BYTE r = static_cast<BYTE>(color1.GetR() + t * (color2.GetR() - color1.GetR()));
    BYTE g = static_cast<BYTE>(color1.GetG() + t * (color2.GetG() - color1.GetG()));
    BYTE b = static_cast<BYTE>(color1.GetB() + t * (color2.GetB() - color1.GetB()));
    BYTE a = static_cast<BYTE>(color1.GetA() + t * (color2.GetA() - color1.GetA()));
    return Color(a, r, g, b);
}

// Function to draw a portion of the radial gradient (a horizontal strip of pixels)
void DrawGradientSection(Bitmap *bitmap, int startY, int endY, int width, int height, const Color& innerColor, const Color& outerColor) {
    // Define gradient properties
    PointF innerCenter(width / 2.0f, height / 2.0f);  // Inner circle center
    PointF outerCenter(width / 2.0f, height / 2.0f);  // Outer circle center
    float innerRadius = width / 4.0f;                 // Inner circle radius
    float outerRadius = width / 2.0f;                 // Outer circle radius

    // Loop through the assigned section of the bitmap
    for (int y = startY; y < endY; ++y) {
        for (int x = 0; x < width; ++x) {
            float dx = x - innerCenter.X;
            float dy = y - innerCenter.Y;
            float distanceInner = std::sqrt(dx * dx + dy * dy);

            dx = x - outerCenter.X;
            dy = y - outerCenter.Y;
            float distanceOuter = std::sqrt(dx * dx + dy * dy);

            // Calculate interpolation factor
            float t = (distanceInner - innerRadius) / (outerRadius - innerRadius);
            t = max(0.0f, min(1.0f, t));  // Clamp t to [0, 1]

            // Interpolate color
            Color pixelColor = InterpolateColor(innerColor, outerColor, t);

            // Set pixel color in the bitmap
            bitmap->SetPixel(x, y - startY, pixelColor);
        }
    }
}

void DrawRadialGradientMultiThreaded(Bitmap &bitmap, int width, int height, const Color& innerColor, const Color& outerColor, int numThreads) {
    int sectionHeight = height / numThreads;

    vector<thread> threads;
	vector<Bitmap *> threadBitmaps;
	for (int i = 0; i < numThreads; ++i) {
		threadBitmaps.push_back(new Bitmap(width, sectionHeight, PixelFormat32bppARGB));
	}

    // Create threads for drawing sections
    for (int i = 0; i < numThreads; ++i) {
        int startY = i * sectionHeight;
        int endY = (i + 1) * sectionHeight;
        threads.push_back(thread(DrawGradientSection, threadBitmaps[i], startY, endY, width, height, innerColor, outerColor));
    }

    // Wait for all threads to finish
    for (auto &t : threads) {
        t.join();
    }

	Graphics graphics(&bitmap);
	for (int i = 0; i < numThreads; ++i) {
		graphics.DrawImage(threadBitmaps[i], 0, i * sectionHeight);
		delete threadBitmaps[i];
	}
}

// WinMain entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Initialize window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = [](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT {
        if (msg == WM_PAINT) {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
        	RECT rect;
        	::GetClientRect(hwnd, &rect);

        	int width = rect.right - rect.left;
        	int height = rect.bottom - rect.top;
        	HDC hdcMem = CreateCompatibleDC(hdc);
        	HBITMAP hbmMem = CreateCompatibleBitmap(hdc, width, height);

        	HGDIOBJ hOld = SelectObject(hdcMem, hbmMem);

            HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
            FillRect(hdcMem, &ps.rcPaint, brush);

			Rect size = {0, 0, 1200, 1200};
            Bitmap bitmap(size.Width, size.Height, PixelFormat32bppARGB);
            Color innerColor(255, 255, 0, 0);  // Red
            Color outerColor(255, 0, 0, 255);  // Blue

            DrawRadialGradientMultiThreaded(bitmap, size.Width, size.Height, innerColor, outerColor, 8);

            // Create a Graphics object to display the bitmap
            Graphics windowGraphics(hdcMem);
            windowGraphics.DrawImage(&bitmap, 0, 0);

        	BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);
        	SelectObject(hdcMem, hOld);

        	DeleteObject(hbmMem);
        	DeleteObject(hOld);
        	DeleteDC(hdcMem);

            EndPaint(hwnd, &ps);
            return 0;
        }
		if (msg == WM_ERASEBKGND) {
			return 1;
		}
		if (msg == WM_KEYDOWN) {
			if (wParam == 'R') {
				InvalidateRect(hwnd, nullptr, false);
			}
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
