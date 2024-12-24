#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>
#include <gdiplus.h>
// #include <gdiplus/gdiplus.h>

#include "Application.h"
#include "api/XMLParser.h"
#include "api/Camera.h"
#include "api/Renderer.h"
#include "api/Graphic.h"
#include "api/FileManager.h"
#include "api/parser/ParserManager.h"
#include "api/parser/ParserHInit.h"

#define APPLICATION_CLASS_NAME "SVGRendering"
#define APPLICATION_TITLE_NAME "☰ SVG Renderer - GROUP 11 - Press \"H\" for help! ♥"
#define BACKGROUND_COLOR RGB(255, 255, 255)
// #define BACKGROUND_COLOR RGB(30, 31, 34)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int main(int argc, char **argv) {
	if (argc == 2) {
		std::string path(argv[1]);
		FileManager::clearFiles();
		FileManager::addFile(path);
		FileManager::setCurrentIdx(0);
	}
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
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = TEXT(APPLICATION_CLASS_NAME);

	RegisterClass(&wndClass);

	HWND hwnd = CreateWindow(TEXT(APPLICATION_CLASS_NAME), TEXT(APPLICATION_TITLE_NAME), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 4000, 4000, nullptr, nullptr, hInstance, nullptr);

	Application::getInstance();

	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0)) {
		if(msg.message == WM_QUIT)
			break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);
	return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;

	switch (message) {
		case WM_CREATE: {
			RECT rect;
			::GetWindowRect(hwnd, &rect);
			Camera::screenSize = {static_cast<int>(rect.right - rect.left), static_cast<int>(rect.bottom - rect.top)};
			::GetClientRect(hwnd, &rect);
			::SetWindowPos(hwnd, HWND_TOP, 0, 0, 2 * Camera::screenSize.x - rect.right + rect.left, 2 * Camera::screenSize.y - rect.bottom + rect.top, SWP_NOMOVE);

			DragAcceptFiles(hwnd, true);
			break;
		}
		case WM_SIZE: {
			RECT rect;
			::GetClientRect(hwnd, &rect);
			Camera::screenSize = {static_cast<int>(rect.right - rect.left), static_cast<int>(rect.bottom - rect.top)};
			break;
		}
		case WM_PAINT: {
			HDC hdc = BeginPaint(hwnd, &ps);
			RECT rect;
			::GetClientRect(hwnd, &rect);

			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;

			HDC hdcMem = CreateCompatibleDC(hdc);
			HBITMAP hbmMem = CreateCompatibleBitmap(hdc, width, height);

			HGDIOBJ hOld = SelectObject(hdcMem, hbmMem);

			HBRUSH hBrush = CreateSolidBrush(BACKGROUND_COLOR);
			FillRect(hdcMem, &rect, hBrush);

			SetWindowText(hwnd, (string(APPLICATION_TITLE_NAME) + " File: " + FileManager::getCurrentFile()).c_str());
			Application::getInstance()->draw(hdcMem);

			BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hOld);

			DeleteObject(hBrush);
			DeleteObject(hbmMem);
			DeleteObject(hOld);
			DeleteDC(hdcMem);
			EndPaint(hwnd, &ps);
			return 0;
		}
		case WM_ERASEBKGND: {
			return 1;
		}
		case WM_MOUSEWHEEL: {
			GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? Camera::zoomIn() : Camera::zoomOut();
			InvalidateRect(hwnd, nullptr, false);
			break;
		}
		case WM_LBUTTONDOWN: {
			Camera::isDragging = true;
			Camera::mousePosition.x = static_cast<float>(static_cast<short>(LOWORD(lParam)));
			Camera::mousePosition.y = static_cast<float>(static_cast<short>(HIWORD(lParam)));
			SetCapture(hwnd);
			break;
		}
		case WM_LBUTTONUP: {
			Camera::isDragging = false;
			ReleaseCapture();
			break;
		}
		case WM_NCRBUTTONDOWN: {
			if (wParam == HTCAPTION) {
				POINT pt;
				GetCursorPos(&pt);
				Application::buildFileMenu();
				TrackPopupMenu(Application::fileMenu, TPM_LEFTALIGN | TPM_TOPALIGN , pt.x, pt.y, 0, hwnd, nullptr);
			}
			return 0;
		}
		case WM_COMMAND: {
			size_t idx = LOWORD(wParam);
			if (FileManager::setCurrentIdx(idx)) {
				InvalidateRect(hwnd, nullptr, false);
			}
			return 0;
		}
		case WM_MOUSEMOVE: {
			Vector2D<float> pt = {static_cast<float>(static_cast<short>(LOWORD(lParam))), static_cast<float>(static_cast<short>(HIWORD(lParam)))};

			if (Camera::isDragging && GetCapture() != nullptr) {
				if (Camera::mousePosition.x != -1.0f) {
					Vector2D<float> offset = {pt.x - Camera::mousePosition.x, pt.y - Camera::mousePosition.y};
					Camera::startPosition += offset;
				}
				Camera::mousePosition = pt;
				InvalidateRect(hwnd, nullptr, false);
			}
			return 0;
		}
		case WM_DROPFILES: {
			// Get the file path of the dropped file
			auto hDrop = reinterpret_cast<HDROP>(wParam);
			UINT fileCount = DragQueryFile(hDrop, 0xFFFFFFFF, nullptr, 0);
			for (unsigned int i = 0; i < fileCount; ++i) {
				std::wstring filePath(256, L'\0');
				DragQueryFileW(hDrop, i, &filePath[0], filePath.size());
				filePath.resize(wcslen(filePath.c_str())); // Resize to correct length
				FileManager::addFile(std::string(filePath.begin(), filePath.end()));
			}
			if (fileCount > 0) {
				FileManager::setCurrentIdx(FileManager::getCurrentIdx() + 1);
				Camera::reset();
				InvalidateRect(hwnd, nullptr, false);
			}
			DragFinish(hDrop);
			return 0;
		}
		case WM_KEYDOWN: {
			int wp = static_cast<int>(wParam);
			switch (wp) {
				case 'R': {
					Camera::reset();
					InvalidateRect(hwnd, nullptr, false);
					break;
				}
				case 'C': {
					FileManager::clearFiles();
					break;
				}
				case 'W': {
					Camera::zoomIn();
					InvalidateRect(hwnd, nullptr, false);
					break;
				}
				case 'S': {
					Camera::zoomOut();
					InvalidateRect(hwnd, nullptr, false);
					break;
				}
				case 'A': {
					Camera::rotateClockWise();
					InvalidateRect(hwnd, nullptr, false);
					break;
				}
				case 'D': {
					Camera::rotateCounterClockWise();
					InvalidateRect(hwnd, nullptr, false);
					break;
				}
				case 'H': {
					MessageBox(nullptr, "Press R to reload.\nPress W/S to zoom in/out.\nPress A/D to rotate.\nUse either mouse drag or arrow keys to navigation.\nPress M to display ruler.\nPress (0-9) to quick select the imported SVGs.\nLeft click at the title bar to get MENU.\n", "SVG SHORTCUT", MB_OK);
					break;
				}
				case 'M': {
					Application::isRulerMode = !Application::isRulerMode;
					InvalidateRect(hwnd, nullptr, false);
					break;
				}
				case VK_UP: {
					Camera::startPosition.y -= 10;
					InvalidateRect(hwnd, nullptr, false);
					break;
				}
				case VK_DOWN: {
					Camera::startPosition.y += 10;
					InvalidateRect(hwnd, nullptr, false);
					break;
				}
				case VK_LEFT: {
					Camera::startPosition.x -= 10;
					InvalidateRect(hwnd, nullptr, false);
					break;
				}
				case VK_RIGHT: {
					Camera::startPosition.x += 10;
					InvalidateRect(hwnd, nullptr, false);
					break;
				}
				default: {
					if (wp >= '0' && wp <= '9') {
						std::string filePath = FileManager::getFile(wp - '0');
						if (!filePath.empty()) {
							FileManager::setCurrentIdx(wp - '0');
							Camera::reset();
							InvalidateRect(hwnd, nullptr, false);
						}
					}
				}
			}
			return 0;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		}
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
