#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <vector>

using namespace Gdiplus;

// Global GDI+ token
ULONG_PTR gdiPlusToken;

// Define a ColorStop structure to hold each color and its position
struct ColorStop{
    float position; // 0.0 to 1.0
    Color color;
};

// Function to interpolate between two colors based on a factor t (0.0 to 1.0)
Color InterpolateColor(const Color &color1, const Color &color2, float t) {
    int r = (int)(color1.GetR() + (color2.GetR() - color1.GetR()) * t);
    int g = (int)(color1.GetG() + (color2.GetG() - color1.GetG()) * t);
    int b = (int)(color1.GetB() + (color2.GetB() - color1.GetB()) * t);
    int a = (int)(color1.GetA() + (color2.GetA() - color1.GetA()) * t);
    return Color(a, r, g, b);
}

// Function to create the custom gradient bitmap based on color stops
Bitmap *CreateCustomGradientBitmap(RectF rect, const std::vector<ColorStop>& stops, float angle = 0.0f) {
//    angle = 63.43494882292201f;
//    angle = 90.0f;
    if (angle < 0.0f) {
        angle = 360.0f + angle;
    }
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

    // Loop through each pixel and determine its color based on the gradient
    for (int x = 0; x < rect.Width; x++) {
        // Calculate the interpolation factor (t) based on the vertical position
        float t = (float)x / (rect.Width - 1);

        // Find the two color stops that this position is between
        ColorStop startStop = stops[0];
        ColorStop endStop = stops[0];

        for (size_t i = 1; i < stops.size(); i++) {
            if (stops[i].position > t) {
                endStop = stops[i];
                startStop = stops[i - 1];
                break;
            }
        }

        // Interpolate between the two color stops
        float factor = (t - startStop.position) / (endStop.position - startStop.position);
        Color gradientColor = InterpolateColor(startStop.color, endStop.color, factor);
        solidBrush.SetColor(gradientColor);
        // Set the color for the current row (1-pixel wide)
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

        // Define the color stops (simulating an SVG-like gradient)
        std::vector<ColorStop> stops = {
            {0.0f, Color(255, 255, 0, 0)}, // Red
            {0.25f, Color(255, 255, 0, 0)}, // Red
            {0.5f, Color(0, 0, 0, 0)}, // Transparent Black
            {1.0f, Color(255, 0, 0, 255)} // Blue
        };

        // Create the custom gradient bitmap (brush)
        Gdiplus::RectF rectF = {100, 50, 500, 250};
        Bitmap *gradientBitmap = CreateCustomGradientBitmap(rectF, stops, rotationAngle);

        // Use the bitmap as a texture brush
        TextureBrush textureBrush(gradientBitmap);

        Gdiplus::Pen pen(Color(255, 0, 255, 255), 10);
        graphics.DrawRectangle(&pen, 100, 50, 500, 250);
        // Create an ellipse and fill it with the custom gradient

//        SolidBrush solidBrush(Color(255, 0, 0, 255));
//        graphics.TranslateTransform
//        graphics.RotateTransform(rotationAngle);
//        graphics.FillRectangle(&solidBrush, 100, 50, 500, 500);

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
