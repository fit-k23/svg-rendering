#include <iostream>
#include <windows.h>

#include <gdiplus.h>
#include "api/XMLParser.h"
#include "api/Camera.h"
#include "api/Renderer.h"
#include "api/Graphic.h"
#include "api/FileManager.h"
#include "api/parser/ParserManager.h"
#include "api/parser/ParserHInit.h"

#define APPLICATION_CLASS_NAME "SVGRendering"
#define APPLICATION_TITLE_NAME "SVG Renderer - GROUP 11"

void ProjectInit() {
//	ParserManager::registerParser("svg", new SVGParser);
//	ParserManager::registerParser("float", new FloatParser);
//	ParserManager::registerParser("color", new ColorParser);
//	ParserManager::registerParser("string", new StringParser);

	FileManager::addFile(L"asset/gradient_test.svg");
	FileManager::setCurrent(0);
	XMLParser::getInstance()->traverseXML("asset/bmw_racoon.svg", nullptr, nullptr);
}

void ProjectDeInit() {
	ParserManager::free();
	delete Renderer::getInstance();
	delete XMLParser::getInstance();
	std::cout << "Deleting instance of XMLParser and Renderer\n";
}

void ProjectDraw(HDC hdc) {
	Gdiplus::Graphics graphics(hdc);
	XMLParser *parser = XMLParser::getInstance();

//	graphics.SetClip(Gdiplus::RectF{100, 30, 700, 400});
//	graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
//	graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias8x8);
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
//	graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
	graphics.SetTextContrast(100);
	graphics.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
	graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
	graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);

	Vector2D<float> vPort = parser->getViewPort();
	ViewBox vBox = parser->getViewBox();

//	std::cout << "Viewport x = " << vPort.x << '\n';
//	std::cout << "Viewport y = " << vPort.y << '\n';
//
//	std::cout << "ViewBox minX = " << vBox.minX << '\n';
//	std::cout << "ViewBox minY = " << vBox.minY << '\n';
//	std::cout << "ViewBox width = " << vBox.width << '\n';
//	std::cout << "ViewBox height = " << vBox.height << '\n';

//	if (vBox.width != -1) {
//		graphics.SetClip(Gdiplus::Rect(vBox.minX, vBox.minY, vBox.width, vBox.height));
//		float scaleX = vPort.x / vBox.width;
//		float scaleY = vPort.y / vBox.height;
//
////		if (scaleX < scaleY) scaleY = scaleX;
////		else scaleX = scaleY;
//		float translateX = vPort.x - (vBox.minX * scaleX);
//		float translateY = vPort.y - (vBox.minY * scaleY);
//
////		std::cout << "Scale X = " << scaleX << '\n';
////		std::cout << "Scale Y = " << scaleY << '\n';
////		std::cout << "Translate X = " << translateX << '\n';
////		std::cout << "Translate Y = " << translateY << '\n';
//
//		graphics.TranslateTransform(translateX, translateY);
//		graphics.ScaleTransform(scaleX, scaleY);
//	}
//	std::cout << "\n";
//	Gdiplus::Region region;
//	graphics.GetClip(&region);

	graphics.TranslateTransform(Camera::startPosition.x, Camera::startPosition.y);
	graphics.TranslateTransform(Camera::mousePosition.x, Camera::mousePosition.y);
	graphics.ScaleTransform(Camera::zoom, Camera::zoom);
	graphics.RotateTransform(Camera::rotation);
	graphics.TranslateTransform(-Camera::mousePosition.x, -Camera::mousePosition.y);

//	graphics.SetClip(&region);

	Renderer *render = Renderer::getInstance();

	render->setViewPort(vPort);

	render->draw(graphics, parser->getRoot());
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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

	HWND hwnd = CreateWindow(TEXT(APPLICATION_CLASS_NAME), TEXT(APPLICATION_TITLE_NAME), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 700, nullptr, nullptr, hInstance, nullptr);
	ProjectInit();

	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0)) {
		if(msg.message == WM_QUIT)
			break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ProjectDeInit();
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;

	switch (message) {
		case WM_CREATE: {
			RECT rect;
			::GetWindowRect(hwnd, &rect);
			Camera::screenSize = {rect.right - rect.left, rect.bottom - rect.top};
			::GetClientRect(hwnd, &rect);
			::SetWindowPos(hwnd, HWND_TOP, 0, 0, 2 * Camera::screenSize.x - rect.right + rect.left, 2 * Camera::screenSize.y - rect.bottom + rect.top, SWP_NOMOVE);

			DragAcceptFiles(hwnd, true);
			break;
		}
		case WM_SIZE: {
			RECT rect;
			::GetClientRect(hwnd, &rect);
			Camera::screenSize = {rect.right - rect.left, rect.bottom - rect.top};
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

			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
			FillRect(hdcMem, &rect, hBrush);

			ProjectDraw(hdcMem);

			BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hOld);

			DeleteObject(hBrush);
			DeleteObject(hbmMem);
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
			Camera::mousePosition.x = (float)(short) LOWORD(lParam);
			Camera::mousePosition.y = (float)(short) HIWORD(lParam);
			SetCapture(hwnd);
			break;
		}
		case WM_LBUTTONUP: {
			Camera::isDragging = false;
			ReleaseCapture();
			break;
		}
		case WM_MOUSEMOVE: {
			Vector2D<float> pt = {(float)(short) LOWORD(lParam), (float)(short) HIWORD(lParam)};

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
			auto hDrop = (HDROP) wParam;
			UINT fileCount = DragQueryFile(hDrop, 0xFFFFFFFF, nullptr, 0);
			if (fileCount > 0) {
				std::wstring filePath(256, L'\0');
				DragQueryFileW(hDrop, 0, &filePath[0], filePath.size());
				filePath.resize(wcslen(filePath.c_str())); // Resize to correct length

				std::wcout << "Changing from " << FileManager::getFilePath(FileManager::getCurrent()) << " to " << filePath << '\n';

				std::string tmpFilePath(filePath.begin(), filePath.end());
				XMLParser::getInstance()->traverseXML(tmpFilePath, nullptr, nullptr);
				FileManager::addFile(filePath);
				FileManager::setCurrent(FileManager::getCurrent() + 1);
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
					MessageBox(nullptr, "Press R to reload.\nPress W/S to zoom in/out.\nPress A/D to rotate.", "SVG SHORTCUT", MB_OK);
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
					std::cout  << "Here\n";
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
						std::cout << "Chose " << wp << "\n";
						std::wstring filePath = FileManager::getFilePath(wp - '0');
						if (!filePath.empty()) {
							std::wcout << "Changing from " << FileManager::getFilePath(FileManager::getCurrent()) << " to " << filePath << '\n';
							FileManager::setCurrent(wp - '0');
							std::string tmpFilePath(filePath.begin(), filePath.end());
							XMLParser::getInstance()->traverseXML(tmpFilePath, nullptr, nullptr);
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
