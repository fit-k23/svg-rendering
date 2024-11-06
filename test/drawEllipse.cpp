#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

#pragma comment (lib, "gdiplus.lib")

void DrawStrokedEllipse(Graphics& graphics, Pen& pen, REAL x, REAL y, REAL width, REAL height) {
	// Draw an ellipse with a stroke using a pen
	graphics.DrawEllipse(&pen, x, y, width, height);
}

int main() {
	GdiplusStartupInput gdiPlusStartupInput;
	ULONG_PTR gdiPlusToken;
	GdiplusStartup(&gdiPlusToken, &gdiPlusStartupInput, nullptr);

	// Set up the window for rendering
	HWND hwnd = GetConsoleWindow();  // Use console window for simplicity (for demo purposes)
	HDC hdc = GetDC(hwnd);

	Graphics graphics(hdc);

	// Set up the Pen with desired color and width
	Pen pen(Color(250, 255, 0, 0), 10);  // Red color, 3 pixel width

	// Set up the ellipse parameters
	REAL x = 50.0f, y = 50.0f, width = 200.0f, height = 100.0f;

	// Draw the stroked ellipse
	DrawStrokedEllipse(graphics, pen, x, y, width, height);
	DrawStrokedEllipse(graphics, pen, x + 100, y, width, width);

	// Release resources
	ReleaseDC(hwnd, hdc);

	// Shutdown GDI+
	GdiplusShutdown(gdiPlusToken);

	return 0;
}
