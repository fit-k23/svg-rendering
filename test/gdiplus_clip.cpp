#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <cmath>

using namespace Gdiplus;

// Camera settings
float zoomFactor = 1.0f;      // Zoom level (1.0 is normal size)
float rotationAngle = 0.0f;   // Rotation angle in degrees
float offsetX = 0.0f;         // Pan offset along the x-axis
float offsetY = 0.0f;         // Pan offset along the y-axis

void OnPaint(HDC hdc) {
	Graphics graphics(hdc);

	// Define the camera area (clipping area from 100,100 to 700,300)
	Rect cameraRect(100, 100, 600, 200);  // (left, top, width, height)

	// Create a GraphicsPath to define the clipping area
	GraphicsPath clipPath;
	clipPath.AddRectangle(cameraRect);

	// Now apply the transformations (zoom, rotation, and pan)
	graphics.ResetTransform();

	// Apply zoom (scale)
	graphics.ScaleTransform(zoomFactor, zoomFactor);

	// Translate (move) the camera view
	graphics.TranslateTransform(offsetX, offsetY);

	// Rotate the scene around the center of the camera view
	float centerX = cameraRect.X + cameraRect.Width / 2.0f;
	float centerY = cameraRect.Y + cameraRect.Height / 2.0f;

	// Translate the origin to the center of the camera view
	graphics.TranslateTransform(centerX, centerY, MatrixOrderAppend);

	// Apply rotation
	graphics.RotateTransform(rotationAngle, MatrixOrderAppend);

	// Translate back to the original position
	graphics.TranslateTransform(-centerX, -centerY, MatrixOrderAppend);

	// Apply the same rotation to the clip path to match the rotated camera view
	Matrix rotationMatrix;
	rotationMatrix.Rotate(rotationAngle);
	clipPath.Transform(rotationMatrix);

	// Set the new clip path that follows the rotated camera view
	graphics.SetClip(&clipPath);

	// Draw some content that will be affected by the camera's transformations
	SolidBrush brush(Color(255, 255, 0, 0));  // Red brush
	graphics.FillRectangle(&brush, 50, 50, 200, 150);  // This will be affected by zoom/rotate/pan

	// Draw more content outside the initial camera region, demonstrating the effect
	graphics.FillRectangle(&brush, 800, 400, 200, 150); // This will not appear unless panned into the view
}

int main() {
	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Create a simple window (for demonstration purposes).
	HWND hwnd = CreateWindow(TEXT("STATIC"), TEXT("GDI+ Camera Example"), WS_OVERLAPPEDWINDOW,
							 CW_USEDEFAULT, CW_USEDEFAULT, 1000, 500, NULL, NULL, NULL, NULL);

	// Set up the paint procedure.
	SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(OnPaint));

	// Show and run the window.
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// Message loop.
	MSG msg;
	while (GetMessage(&msg, hwnd, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Shutdown GDI+.
	GdiplusShutdown(gdiplusToken);
	return 0;
}
