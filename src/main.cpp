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

#define APPLICATION_CLASS_NAME "SVGRendering"
#define APPLICATION_TITLE_NAME "SVG Renderer - GROUP 11 - Press \"H\" for help! - "
// #define BACKGROUND_COLOR RGB(255, 255, 255)
#define BACKGROUND_COLOR RGB(240, 240, 240)
// #define BACKGROUND_COLOR RGB(30, 31, 34)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool handleArgs(int argc, char **argv) {
	if (argc == 1) {
		cout << "example.exe path/to/file.svg\n"
				"example.exe path/to/folder\n";
		return true;
	}
	string path;
	for (int i = 1; i < argc; ++i) {
		path += argv[i];
		if (i != argc - 1) {
			path += " ";
		}
	}
	if (!FileHelper::pathExists(path)) {
		cout << "File or Folder does not exist!\n";
		return false;
	}
	if (FileHelper::pathIsDirectory(path)) {
		return FileManager::addFolder(path);
	}
	return FileManager::addFile(path);
}

void updateCaption(HWND hwnd, const std::string &suffix = "") {
	SetWindowText(hwnd, (string(APPLICATION_TITLE_NAME) + " - File: " + FileManager::getCurrentFile() + " - Viewport: {" + std::to_string(XMLParser::getInstance()->getViewPort().x) + ", " + std::to_string(XMLParser::getInstance()->getViewPort().y) + "} - Zoom: " + std::to_string(Camera::zoom) + suffix).c_str());
}

void updateViewBox() {
	return;
	Vector2D vPort = XMLParser::getInstance()->getViewPort();
	ViewBox vBox = XMLParser::getInstance()->getViewBox();
	if (vPort.x <= 0 && vPort.y <= 0) {
		vPort.x = Camera::screenSize.x;
		vPort.y = Camera::screenSize.y;
	}

	float boundPort = std::min(vPort.x, vPort.y);

	// if ((vPort.x != vBox.width || vPort.y != vBox.height) && vBox.width != 0 && vBox.height != 0) {
	// 	if (vBox.width == -1 && vBox.height == -1) {
	// 		vBox.width = vPort.x;
	// 		vBox.height = vPort.y;
	// 	}
	// 	float scale_x = vPort.x / vBox.width;
	// 	float scale_y = vPort.y / vBox.height;
	// 	scale = std::min(scale_x, scale_y);
	// }
	float boundScreen = std::min(Camera::screenSize.x, Camera::screenSize.y);
	Camera::zoom = boundScreen / boundPort + 0.001;
	if (Camera::zoom <= 0) {
		int c = 0;
	}
}

int main(int argc, char **argv) {
	FileManager::EXECUTABLE_PATH = FileHelper::getParentPath(argv[0]);
	if (!handleArgs(argc, argv)) {
		return 0;
	}
	FileManager::setCurrentIdx(0);
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
	updateViewBox();
	updateCaption(hwnd);

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
			PAINTSTRUCT ps;
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
			updateCaption(hwnd);
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
			POINT pt;
			GetCursorPos(&pt);
			if (wParam == HTCAPTION) {
				TrackPopupMenu(Application::menu, TPM_LEFTALIGN | TPM_TOPALIGN , pt.x, pt.y, 0, hwnd, nullptr);
			}
			return 0;
		}
		case WM_RBUTTONDOWN: {
			POINT pt;
			GetCursorPos(&pt);
			TrackPopupMenu(Application::fileMenu, TPM_LEFTALIGN | TPM_TOPALIGN , pt.x, pt.y, 0, hwnd, nullptr);
			return 0;
		}
		case WM_COMMAND: {
			size_t idx = LOWORD(wParam);
			if (idx >= MenuBase::fileBase) {
				switch (idx - MenuBase::fileBase) {
					case 0: {
						Application::openImportFileMenu();
						break;
					}
					case 1: {
						Application::isMaximumScreen = !Application::isMaximumScreen;
						ShowWindow(hwnd, Application::isMaximumScreen ? SW_MAXIMIZE : SW_RESTORE);
						CheckMenuItem(Application::menu, MenuBase::current + 1, MF_STRING | (Application::isMaximumScreen ? MF_CHECKED : MF_UNCHECKED));
						break;
					}
					case 2: {
						Application::isViewFullPath = !Application::isViewFullPath;
						Application::buildMenu();
						// CheckMenuItem(Application::menu, MenuBase::current + 2, MF_STRING | (Application::isViewFullPath ? MF_CHECKED : MF_UNCHECKED));
						break;
					}
					case 3: {
						Application::isRulerMode = !Application::isRulerMode;
						InvalidateRect(hwnd, nullptr, false);
						CheckMenuItem(Application::menu, MenuBase::current + 3, MF_STRING | (Application::isRulerMode ? MF_CHECKED : MF_UNCHECKED));
						break;
					}
					case 4: {
						Application::doSRGBGradient = !Application::doSRGBGradient;
						CheckMenuItem(Application::menu, MenuBase::current + 4, MF_STRING | (Application::doSRGBGradient ? MF_CHECKED : MF_UNCHECKED));
						InvalidateRect(hwnd, nullptr, false);
						break;
					}
					default: {}
				}
			} else {
				if (idx != FileManager::getCurrentIdx()) {
					CheckMenuItem(Application::fileMenu, FileManager::getCurrentIdx(), MF_STRING | MF_UNCHECKED);
					if (FileManager::setCurrentIdx(idx)) {
						updateViewBox();
						updateCaption(hwnd);
						CheckMenuItem(Application::fileMenu, FileManager::getCurrentIdx(), MF_STRING | MF_CHECKED);
						InvalidateRect(hwnd, nullptr, false);
					}
				}
			}
			return 0;
		}
		case WM_MOUSEMOVE: {
			Vector2D pt = {static_cast<float>(static_cast<short>(LOWORD(lParam))), static_cast<float>(static_cast<short>(HIWORD(lParam)))};

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
			bool idkWhatToName = false;
			size_t choose = FileManager::getCurrentIdx();
			for (unsigned int i = 0; i < fileCount; ++i) {
				std::wstring filePath(256, L'\0');
				DragQueryFileW(hDrop, i, &filePath[0], filePath.size());
				filePath.resize(wcslen(filePath.c_str())); // Resize to correct length

				if (FileManager::addFile(std::string(filePath.begin(), filePath.end()))) {
					if (!idkWhatToName) {
						idkWhatToName = true;
						choose = FileManager::getSize() - 1;
					}
				}
			}
			if (fileCount > 0) {
				if (FileManager::setCurrentIdx(choose)) {
					updateViewBox();
					updateCaption(hwnd);
				}
				Camera::reset();
				Application::buildMenu();
				InvalidateRect(hwnd, nullptr, false);
			}
			DragFinish(hDrop);
			return 0;
		}
	case WM_SYSCOMMAND: {
		if (wParam == SC_MAXIMIZE) {
			Application::isMaximumScreen = true;
		}
		if (wParam == SC_RESTORE) {
			Application::isMaximumScreen = false;
		}
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	case WM_KEYDOWN: {
			int wp = static_cast<int>(wParam);
			switch (wp) {
				case 'R': {
					Camera::reset();
					updateViewBox();
					updateCaption(hwnd);
					InvalidateRect(hwnd, nullptr, false);
					break;
				}
				case 'T': {
					FileManager::setCurrentIdx(FileManager::getCurrentIdx(), true);
					InvalidateRect(hwnd, nullptr, false);
					break;
				}
				case 'C': {
					Camera::reset();
					FileManager::clearFiles();
					break;
				}
				case 'W': {
					Camera::zoomIn();
					updateCaption(hwnd);
					InvalidateRect(hwnd, nullptr, false);
					break;
				}
				case 'S': {
					Camera::zoomOut();
					updateCaption(hwnd);
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
					MessageBox(nullptr, "Press R to reload.\n"
						"Press T to reload from disk! (Without changing viewer camera)\n"
						"Press W/S to zoom in/out.\n"
						"Press A/D to rotate.\n"
						"Use either mouse drag or arrow keys to navigation.\n"
						"Press M to display ruler.\n"
						"Press C to clear all imported SVGs\n"
						"Left click at the title bar to get MENU.\n",
						"SVG SHORTCUT", MB_OK);
					break;
				}
				case 'M': {
					Application::isRulerMode = !Application::isRulerMode;
					InvalidateRect(hwnd, nullptr, false);
					break;
				}
				case 'F': {
					Application::isMaximumScreen = !Application::isMaximumScreen;
					if (Application::isMaximumScreen) {
						ShowWindow(hwnd, SW_MAXIMIZE);
					} else {
						ShowWindow(hwnd, SW_RESTORE);
					}
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
				default: {}
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
