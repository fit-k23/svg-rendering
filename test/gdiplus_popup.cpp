#include <windows.h>
#include <gdiplus.h>
#include <memory>
using namespace Gdiplus;

// Global variables
ULONG_PTR gdiplusToken;  // GDI+ token for initialization
Bitmap* backgroundBitmap = nullptr;  // Background bitmap (underlayer)
Bitmap* popupBitmap = nullptr;       // Popup bitmap
bool showPopup = false;  // Flag to toggle the popup layer

// Function to initialize GDI+
void InitGDIPlus() {
	GdiplusStartupInput gdiPlusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiPlusStartupInput, nullptr);
}

// Function to shut down GDI+
void ShutdownGDIPlus() {
	GdiplusShutdown(gdiplusToken);
}

// Function to load bitmaps
void LoadBitmaps() {
	// Load the background bitmap (underlayer)
	backgroundBitmap = Bitmap::FromFile(L"asset/hcmusa.png");  // Ensure this path is correct

	// Load the popup bitmap
	popupBitmap = Bitmap::FromFile(L"asset/hcmus.png");  // Ensure this path is correct
}

// Function to clean up bitmaps
void CleanUpBitmaps() {
	delete backgroundBitmap;
	delete popupBitmap;
}

// Window procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_CREATE:
			// Load the bitmaps when the window is created
			LoadBitmaps();
			return 0;

		case WM_KEYDOWN: {
			if (wParam == 'R') {
				// Toggle the popup visibility when 'R' is pressed
				showPopup = !showPopup;
				InvalidateRect(hWnd, NULL, TRUE);  // Redraw the window
			}
			return 0;
		}

		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			Graphics graphics(hdc);

			// Create an offscreen bitmap (using a compatible pixel format)
			Bitmap offScreen(ps.rcPaint.right, ps.rcPaint.bottom, PixelFormat32bppARGB);  // Correct pixel format

			// Create a Graphics object for the offscreen bitmap to draw on
			Graphics offGraphics(&offScreen);  // Offscreen graphics to perform drawing operations
			offGraphics.SetSmoothingMode(SmoothingModeAntiAlias);
			offGraphics.SetCompositingMode(CompositingModeSourceOver);

			// Draw the background (underlayer)
			offGraphics.DrawImage(backgroundBitmap, 0, 0, backgroundBitmap->GetWidth(), backgroundBitmap->GetHeight());

			// Draw the popup if showPopup is true
			if (showPopup) {
				offGraphics.DrawImage(popupBitmap, 100, 100);  // Example position, adjust as needed
			}

			// Now copy the offscreen content to the screen
			graphics.DrawImage(&offScreen, 0, 0);

			EndPaint(hWnd, &ps);
			return 0;
		}

		case WM_DESTROY:
			// Clean up the bitmaps and shut down GDI+ when the window is destroyed
			CleanUpBitmaps();
			PostQuitMessage(0);
			return 0;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

// Entry point
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Initialize GDI+
	InitGDIPlus();

	// Register the window class
	const char* className = "GDIPlusApp";
	WNDCLASS wc = {0};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;
	RegisterClass(&wc);

	// Create the window
	HWND hWnd = CreateWindowEx(
			0, className, "GDI+ Animation", WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
			NULL, NULL, hInstance, NULL
	);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Shut down GDI+
	ShutdownGDIPlus();

	return (int)msg.wParam;
}
