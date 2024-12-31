#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

#pragma comment(lib, "gdiplus.lib")

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: {
        // Create a Graphics object for drawing
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

		HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
		FillRect(hdc, &(ps.rcPaint), brush);
		DeleteObject(brush);

        Graphics graphics(hdc);

        // Create a GraphicsPath to define the circle (radial gradient will use this)
        GraphicsPath path;
        path.AddEllipse(20, 10, 100, 100);  // Circle inside the rectangle (centered)

        // Create a PathGradientBrush based on the circle path
        PathGradientBrush pathBrush(&path);

        // Define color stops for the radial gradient
        Color colors[3] = {
            Color(255, 255, 0, 0),  // Red at position 0.0
            Color(255, 0, 0, 255),  // Blue at position 0.5
            Color(255, 0, 255, 0)   // Green at position 1.0
        };

        // Define positions for the color stops
        REAL positions[3] = { 0.0f, 0.5f, 1.0f };

        // Set the color and position stops in the PathGradientBrush
        pathBrush.SetCenterPoint(PointF(70.0f, 35.0f));  // Set the center of the gradient (middle of the rectangle)
        pathBrush.SetInterpolationColors(colors, positions, 3);          // Set the gradient positions

        // Set additional properties for the radial gradient
        pathBrush.SetFocusScales(0.5f, 0.5f); // Focus: 0.5 means halfway between center and edge

        // Fill the entire rectangle with the radial gradient
        graphics.FillRectangle(&pathBrush, 20, 10, 100, 50);

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int main() {
    // Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Create a window
    const char CLASS_NAME[] = "GradientWindowClass";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, "Radial Gradient Example", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
        NULL, NULL, wc.hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOWNORMAL);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Cleanup GDI+
    GdiplusShutdown(gdiplusToken);

    return 0;
}
