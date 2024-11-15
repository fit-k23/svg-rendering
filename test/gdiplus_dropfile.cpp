#include <iostream>
#include <windows.h>
#include <commdlg.h>
#include <gdiplus.h>
#include <string>
#include <vector>

using namespace Gdiplus;

// Global variables for GDI+ startup
ULONG_PTR gdiplusToken;

// Function to initialize GDI+
void InitGDIPlus() {
	GdiplusStartupInput gdiPlusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiPlusStartupInput, NULL);
}

// Function to shut down GDI+
void ShutdownGDIPlus() {
	GdiplusShutdown(gdiplusToken);
}

// Function to render the dropped image
void RenderImage(HDC hdc, const std::wstring &filePath) {
	Bitmap *image = Bitmap::FromFile(filePath.c_str());

	if (image && image->GetLastStatus() == Ok) {
		Graphics graphics(hdc);
		graphics.DrawImage(image, 0, 0);  // Draw at (0, 0) (you can modify this as needed)
	} else {
		MessageBox(NULL, "Failed to load image.", "Error", MB_OK | MB_ICONERROR);
	}

	delete image;
}

// Window procedure function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CREATE:
			// Register the window to accept dropped files
			DragAcceptFiles(hwnd, TRUE);
			break;

		case WM_DROPFILES: {
			// Get the file path of the dropped file
			HDROP hDrop = (HDROP) wParam;
			UINT fileCount = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
			if (fileCount > 0) {
				// Get the path of the first file dropped
				std::wstring filePath(256, L'\0');
				DragQueryFileW(hDrop, 0, &filePath[0], filePath.size());
				filePath.resize(wcslen(filePath.c_str())); // Resize to correct length

				// Render the image (you could implement your own method to resize and display)
				HDC hdc = GetDC(hwnd);
				RenderImage(hdc, filePath);
				ReleaseDC(hwnd, hdc);
			}
			DragFinish(hDrop);
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
	MSG msg;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	WNDCLASS wndClass;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WindowProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = TEXT("DropFileWindowClass");

	RegisterClass(&wndClass);

	HWND hWnd = CreateWindow(TEXT("DropFileWindowClass"), TEXT("Drop PNG To Window"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 500, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	// Main message loop
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);
	return static_cast<int>(msg.wParam); // Return the message's result
}
