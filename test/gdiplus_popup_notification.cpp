#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <thread>
#include <chrono>

using namespace Gdiplus;

// Global variables
HINSTANCE hInst;
ULONG_PTR gdiplusToken;

// Function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

// Timer ID for auto-close
#define TIMER_ID 1

// Function to create a menu
HMENU CreateAppMenu() {
	HMENU hMenu = CreateMenu();
	HMENU hFileMenu = CreatePopupMenu();

	// Add items to the File menu
	AppendMenu(hFileMenu, MF_STRING, 1, "Button 1 - Show Notification");
	AppendMenu(hFileMenu, MF_STRING, 2, "Button 2 - Show Notification");
	AppendMenu(hFileMenu, MF_STRING, 3, "Exit");

	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hFileMenu, "Menu");

	return hMenu;
}

// Entry point using main instead of wWinMain
int main(int argc, char* argv[])
{
	// Initialize GDI+
	GdiplusStartupInput gdiPlusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiPlusStartupInput, NULL);

	// Initialize Window Class for Window 1 (Main window)
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;  // Set Window 1 Procedure
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = "WindowClass1";
	RegisterClass(&wc);

	// Create Window 1
	HWND hwnd1 = CreateWindowEx(
		0,
		"WindowClass1",
		"Window 1",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
		nullptr, nullptr, hInst, nullptr);

	// Create and set the menu
	HMENU hMenu = CreateAppMenu();
	SetMenu(hwnd1, hMenu);

	// Show Window 1
	ShowWindow(hwnd1, SW_SHOWNORMAL);
	UpdateWindow(hwnd1);

	// Main message loop
	MSG msg = {};
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Shutdown GDI+
	GdiplusShutdown(gdiplusToken);
	return (int) msg.wParam;
}

// Window procedure for Window 1 (Main window)
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_PAINT:
		{
			// Drawing with GDI+ in Window 1
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			Graphics graphics(hdc);
			Pen pen(Color(255, 0, 0, 255));  // Blue pen
			graphics.DrawRectangle(&pen, 50, 50, 200, 150);  // Drawing a rectangle

			EndPaint(hwnd, &ps);
		}
			break;

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case 1:  // "Button 1 - Show Notification"
				{
					// Create notification window for Button 1
					WNDCLASS wc2 = {};
					wc2.lpfnWndProc = WndProc2;  // Set Window 2 Procedure
					wc2.hInstance = hInst;
					wc2.lpszClassName = "WindowClass2";
					RegisterClass(&wc2);

					HWND hwnd2 = CreateWindowEx(
						WS_EX_TOPMOST | WS_EX_TOOLWINDOW,  // Topmost and tool window styles
						"WindowClass2",
						"Notification",
						WS_POPUP,  // Popup style (no border, no caption)
						0, 0, 300, 100,  // Default size
						nullptr, nullptr, hInst, nullptr);

					// Show window 2 without activating
					ShowWindow(hwnd2, SW_SHOWNOACTIVATE);
					UpdateWindow(hwnd2);

					// Position the notification window at the center-bottom of the screen
					RECT rect;
					GetWindowRect(hwnd2, &rect);
					int screenWidth = GetSystemMetrics(SM_CXSCREEN);
					int screenHeight = GetSystemMetrics(SM_CYSCREEN);
					int xPos = (screenWidth - rect.right + rect.left) / 2;
					int yPos = screenHeight - rect.bottom;
					SetWindowPos(hwnd2, HWND_TOPMOST, xPos, yPos, 0, 0, SWP_NOSIZE);

					// Set a timer to automatically close the notification window after 3 seconds (3000 ms)
					SetTimer(hwnd2, TIMER_ID, 3000, nullptr);
				}
					break;

				case 2:  // "Button 2 - Show Notification"
				{
					// Create notification window for Button 2
					WNDCLASS wc2 = {};
					wc2.lpfnWndProc = WndProc2;  // Set Window 2 Procedure
					wc2.hInstance = hInst;
					wc2.lpszClassName = "WindowClass2";
					RegisterClass(&wc2);

					HWND hwnd2 = CreateWindowEx(
						WS_EX_TOPMOST | WS_EX_TOOLWINDOW,  // Topmost and tool window styles
						"WindowClass2",
						"Notification",
						WS_POPUP,  // Popup style (no border, no caption)
						0, 0, 300, 100,  // Default size
						nullptr, nullptr, hInst, nullptr);

					// Show window 2 without activating
					ShowWindow(hwnd2, SW_SHOWNOACTIVATE);
					UpdateWindow(hwnd2);

					// Position the notification window at the center-bottom of the screen
					RECT rect;
					GetWindowRect(hwnd2, &rect);
					int screenWidth = GetSystemMetrics(SM_CXSCREEN);
					int screenHeight = GetSystemMetrics(SM_CYSCREEN);
					int xPos = (screenWidth - rect.right + rect.left) / 2;
					int yPos = screenHeight - rect.bottom;
					SetWindowPos(hwnd2, HWND_TOPMOST, xPos, yPos, 0, 0, SWP_NOSIZE);

					// Set a timer to automatically close the notification window after 3 seconds (3000 ms)
					SetTimer(hwnd2, TIMER_ID, 3000, nullptr);
				}
					break;

				case 3:  // Exit menu item
					PostQuitMessage(0);
					break;
			}

			return 0;
		}

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

// Window procedure for Window 2 (Notification window)
LRESULT CALLBACK WndProc2(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_PAINT:
		{
			// Drawing with GDI+ in Notification Window (Window 2)
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			Graphics graphics(hdc);
			Pen pen(Color(255, 255, 0, 0));  // Red pen for drawing text
			SolidBrush brush(Color(255, 255, 255, 255));  // White brush for text

			// Draw a simple message in the notification window
			std::wstring message = L"Your notification message!";
			Font font(L"Arial", 16);
			graphics.DrawString(message.c_str(), -1, &font, PointF(10, 30), &brush);

			EndPaint(hwnd, &ps);
		}
			break;

		case WM_TIMER:
			if (wParam == TIMER_ID) {
				// Close the window after 3 seconds
				DestroyWindow(hwnd);
			}
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
