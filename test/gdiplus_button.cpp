#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#include <vector>
#include <string>

#define APPLICATION_CLASS_NAME "GDIPLUS_BUTTON"
#define APPLICATION_TITLE_NAME "GDIPLUS_BUTTON"

using namespace Gdiplus;

// Global variables
HINSTANCE hInstance;
HWND hwndMain;
GdiplusStartupInput gdiPlusStartupInput;
ULONG_PTR gdiPlusToken;

// Button structure
struct Button {
	int id;
	int x;
	int y;
	std::wstring text;
};

enum class MenuFlag : int{
	FLAG_CLOSE = 0,
	FLAG_OPEN
};

// List of buttons
std::vector<Button> buttons;
Button *selectedButton = nullptr;

int screenWidth = 1000;
int screenHeight = 500;
//int button_padding = 15;
int button_padding = 5;
int button_width = screenWidth / 4 - 2 * button_padding;
int button_height = 30;
int text_size = 20;

int offset_button_y = button_height;

int circle_x = screenWidth * 0.85;
int circle_y = screenHeight * 0.85;
int circle_r = 20;

bool forceDisableMenu = false;
bool openMenu = false;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	PAINTSTRUCT ps;
	SolidBrush brush(Color(255, 0, 0, 0));  // Black color for text

	switch (msg) {
		case WM_CREATE: {
			RECT rect;
			::GetWindowRect(hwnd, &rect);
			screenWidth = rect.right - rect.left;
			screenHeight = rect.bottom - rect.top;
			::GetClientRect(hwnd, &rect);
			::SetWindowPos(hwnd, HWND_TOP, 0, 0, 2 * screenWidth - rect.right + rect.left, 2 * screenHeight - rect.bottom + rect.top, SWP_NOMOVE);

			for (int i = 0; i < 10; ++i) {
				int top = i * (button_height + button_padding) + button_padding + offset_button_y;
				buttons.push_back({i, button_padding, top, L"Button " + std::to_wstring(i)});
			}

			break;
		}
		case WM_SIZE: {
//		case WM_SIZING: {
			RECT rect;
			::GetClientRect(hwnd, &rect);
			std::cout << "Client (" << rect.right - rect.left << "," << rect.bottom - rect.top << ")\n";

			screenWidth = rect.right - rect.left;
			screenHeight = rect.bottom - rect.top;

			::GetWindowRect(hwnd, &rect);
			std::cout << "Window (" << rect.right - rect.left << "," << rect.bottom - rect.top << ")\n";
			std::cout << "Cur:   (" << screenWidth << "," << screenHeight << ")\n\n";
			button_width = screenWidth / 4 - 2 * button_padding;
			forceDisableMenu = screenWidth < 400;
			InvalidateRect(hwnd, nullptr, false);
			break;
		}
		case WM_MOUSEMOVE: {
			POINT pt = {LOWORD(lp), HIWORD(lp)};
			RECT r;
			r.left = screenWidth * 0.85;
			r.right = screenWidth;
			r.top = 0;
			r.bottom = screenHeight;
			if (!openMenu) {
				if (PtInRect(&r, pt)) {
					openMenu = true;
				} else {
					openMenu = false;
				}
			}
		}
		case WM_TIMER: {
			switch ((MenuFlag) wp) {
				case MenuFlag::FLAG_OPEN: {
					break;
				}
				case MenuFlag::FLAG_CLOSE: {
					break;
				}
			}
			break;
		}
		case WM_LBUTTONDOWN: {
			POINT pt = {LOWORD(lp), HIWORD(lp)};

			if (openMenu) {
				for (auto &button: buttons) {
					RECT r;
					r.left = screenWidth * 0.75 + button.x;
					r.right = r.left + button_width;
					r.top = button.y;
					r.bottom = r.top + button_height;
					if (PtInRect(&r, pt)) {
						selectedButton = &button;
						InvalidateRect(hwnd, NULL, TRUE);  // Force a redraw
					}
				}
			} else {
				int dx = pt.x - circle_x;
				int dy = pt.y - circle_y;
				if (dx * dx + dy * dy <= circle_r * circle_r) {
					openMenu = true;
					InvalidateRect(hwnd, NULL, TRUE);  // Force a redraw
				}
			}
			break;
		}
		case WM_PAINT: {
			RECT rect;
			::GetClientRect(hwnd, &rect);

			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;

			HDC hdc = BeginPaint(hwnd, &ps);
			HDC hdcMem = CreateCompatibleDC(hdc);
			HBITMAP hbmMem = CreateCompatibleBitmap(hdc, width, height);

			HGDIOBJ hOld = SelectObject(hdcMem, hbmMem);
//			SetBkColor(hdcMem, RGB(255, 255, 255));

			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
			FillRect(hdcMem, &rect, hBrush);

			Gdiplus::Graphics graphic(hdcMem);
			graphic.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
			graphic.SetTextContrast(100);
			graphic.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
			graphic.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
			graphic.SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);

			// Create a font for drawing the button text

			if (!forceDisableMenu && openMenu) {
				SolidBrush menuBrush(Color(200, 200, 200, 130));
				graphic.FillRectangle(&menuBrush, screenWidth * 0.75, 0.0, screenWidth, screenHeight);
				Font font = Font(L"Arial", 11);
				for (int i = 0; i < buttons.size(); ++i) {
					Button button = buttons[i];
					SolidBrush buttonBrush(Color(255, 200, 200, 200));  // Light blue
					if (selectedButton != nullptr && selectedButton->id == i) {
						buttonBrush.SetColor(Color(255, 200, 200, 0));
					}

					graphic.FillRectangle(&buttonBrush, screenWidth * 0.75 + button.x, button.y, button_width, button_height);

					// Draw the button text
					SolidBrush textBrush(Color(255, 0, 0, 0));  // Black text
					graphic.DrawString(button.text.c_str(), -1, &font, PointF(screenWidth * 0.75 + button.x + 10, button.y + 10), &textBrush);
				}

				// If a button is selected, display the clicked message
				if (selectedButton != nullptr) {
					SolidBrush textBrush(Color(255, 0, 0, 0));  // Black text
					std::wstring clickedText = L"Button " + std::to_wstring(selectedButton->id) + L" clicked";
					graphic.DrawString(clickedText.c_str(), -1, &font, PointF(50, 250), &textBrush);
				}
			} else {
				SolidBrush buttonBrush(Color(255, 200, 200, 200));
				graphic.FillEllipse(&brush, circle_x - circle_r, circle_y - circle_r, 2 * circle_r, 2 * circle_r);

				auto brusha = SolidBrush(Color(255, 100, 255, 0));
				int r = 100;
				graphic.FillEllipse(&brusha, screenWidth - r, screenHeight - r, 2 * r, 2 * r);
			}

			BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hOld);

			DeleteObject(hBrush);
			DeleteObject(hbmMem);
			DeleteDC(hdcMem);
			EndPaint(hwnd, &ps);
			break;
		}
		case WM_ERASEBKGND: {
			return 1;
		}
		case WM_KEYDOWN: {
//			std::string tmp = "start cmd /k echo \"";
//			tmp += static_cast<char>(wp);
//			tmp += "\"";
			if (static_cast<char>(wp) == 'M') {
//				RECT rect;
//				::GetClientRect(hWnd, &rect);
//				//				::RedrawWindow(hWnd, &rect, nullptr, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
//				::RedrawWindow(hWnd, &rect, nullptr, RDW_INVALIDATE | RDW_NOERASE | RDW_NOFRAME | RDW_UPDATENOW);
				openMenu = !openMenu;
				InvalidateRect(hwnd, nullptr, TRUE);
			}
//			else {
//				system(tmp.c_str());
//			}
			return 0;
		}
		case WM_DESTROY: {
			// Clean up GDI+
			GdiplusShutdown(gdiPlusToken);
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, msg, wp, lp);
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
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = TEXT(APPLICATION_CLASS_NAME);

	RegisterClass(&wndClass);

	HWND hWnd = CreateWindow(TEXT(APPLICATION_CLASS_NAME), TEXT(APPLICATION_TITLE_NAME), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, screenWidth, screenHeight, nullptr, nullptr, hInstance, nullptr);

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
