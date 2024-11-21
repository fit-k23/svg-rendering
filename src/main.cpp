#pragma comment (lib, "Gdiplus.lib")
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

#define APPLICATION_CLASS_NAME "SVGRendering-Group11"
#define APPLICATION_TITLE_NAME "SVG Renderer"


void ProjectInit() {
	ParserManager::registerParser("svg", new SVGParser);
	ParserManager::registerParser("float", new FloatParser);
	ParserManager::registerParser("color", new ColorParser);
	ParserManager::registerParser("string", new StringParser);
}

void ProjectDeInit() {
	ParserManager::free();
}

std::string svgFile = "asset/sample1.svg";
std::string preFile = "";
XMLParser *parser = nullptr;
Renderer *render = nullptr;

void ProjectDraw(HDC hdc, const std::string &fileName) {
	Gdiplus::Graphics graphics(hdc);
	if (parser == nullptr) parser = XMLParser::getInstance();

	if (preFile != fileName) {
		if (preFile != "")
			std::cout << "Changing from " << preFile << " to " << fileName << '\n';
		preFile = fileName;
		parser->traverseXML(fileName, nullptr, nullptr);

		Element* svg = parser->getRoot();
	}

	graphics.SetClip(Gdiplus::RectF{100, 30, 700, 400});

	graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	//graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias8x8);
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
//	graphics.SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);
	graphics.SetTextContrast(100);
	graphics.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
	graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
	graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);

	float centerX = GetSystemMetrics(SM_CXSCREEN) / 2.0f;
	float centerY = GetSystemMetrics(SM_CYSCREEN) / 2.0f;

	Vector2D<float> vPort = parser->getViewPort();
	ViewBox vBox = parser->getViewBox();


//	std::cout << "Viewport x = " << vPort.x << '\n';
//	std::cout << "Viewport y = " << vPort.y << '\n';
//
//	std::cout << "ViewBox minX = " << vBox.minX << '\n';
//	std::cout << "ViewBox minY = " << vBox.minY << '\n';
//	std::cout << "ViewBox width = " << vBox.width << '\n';
//	std::cout << "ViewBox height = " << vBox.height << '\n';

	if (vBox.width != -1) {
		float scaleX = vPort.x / vBox.width;
		float scaleY = vPort.y / vBox.height;

//		if (scaleX < scaleY) scaleY = scaleX;
//		else scaleX = scaleY;
		float translateX = vPort.x - (vBox.minX * scaleX);
		float translateY = vPort.y - (vBox.minY * scaleY);

//		std::cout << "Scale X = " << scaleX << '\n';
//		std::cout << "Scale Y = " << scaleY << '\n';
//		std::cout << "Translate X = " << translateX << '\n';
//		std::cout << "Translate Y = " << translateY << '\n';
//		std::cout << "\n";

//		graphics.TranslateTransform(translateX, translateY);
		graphics.ScaleTransform(scaleX, scaleY);
	}

	graphics.TranslateTransform(Camera::startPosition.x, Camera::startPosition.y);
	graphics.TranslateTransform(Camera::mousePosition.x, Camera::mousePosition.y);
	graphics.ScaleTransform(Camera::zoom, Camera::zoom);
	graphics.RotateTransform(Camera::rotation);
	graphics.TranslateTransform(-Camera::mousePosition.x, -Camera::mousePosition.y);

	if (render == nullptr)
		render = Renderer::getInstance();
	
	render->setViewPort(vPort);
	//render->setShapes(parser->getShapes());
	render->setScreenSize({ 2 * centerX, 2 * centerY });

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
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = TEXT(APPLICATION_CLASS_NAME);

	RegisterClass(&wndClass);

	HWND hWnd = CreateWindow(TEXT(APPLICATION_CLASS_NAME), TEXT(APPLICATION_TITLE_NAME), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 800, nullptr, nullptr, hInstance, nullptr);
	ProjectInit();

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	// Main message loop
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// delete XMLparser and Renderer pointer
	delete parser;
	delete render;
	std::cout << "Deleteing instance of XMLParser and Renderer\n";
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return static_cast<int>(msg.wParam); // Return the message's result
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;

	switch (message) {
		case WM_CREATE: {
			DragAcceptFiles(hWnd, true);
			break;
		}
		case WM_PAINT: {
			HDC hdc = BeginPaint(hWnd, &ps);
			RECT rect;
			::GetClientRect(hWnd, &rect);

			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;

			HDC hdcMem = CreateCompatibleDC(hdc);
			HBITMAP hbmMem = CreateCompatibleBitmap(hdc, width, height);

			HGDIOBJ hOld = SelectObject(hdcMem, hbmMem);
//			SetBkColor(hdcMem, RGB(255, 255, 255));

			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
			FillRect(hdcMem, &rect, hBrush);

			// Draw into hdcMem here
//			ProjectDraw(hdcMem, "asset/text_anchor.svg");
			ProjectDraw(hdcMem, svgFile);
			// Transfer the off-screen DC to the screen

			BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hOld);

			DeleteObject(hBrush);
			DeleteObject(hbmMem);
			DeleteDC(hdcMem);
			EndPaint(hWnd, &ps);
			return 0;
		}
		case WM_ERASEBKGND: {
			return 1;
		}
		case WM_MOUSEWHEEL: {
			int delta = GET_WHEEL_DELTA_WPARAM(wParam);

			if (delta > 0) {
				Camera::zoomIn();
			} else {
				Camera::zoomOut();
			}
			InvalidateRect(hWnd, nullptr, false);
			break;
		}
		case WM_LBUTTONDOWN: {
			Camera::isDragging = true;
			Camera::mousePosition.x = (float)(short) LOWORD(lParam);
			Camera::mousePosition.y = (float)(short) HIWORD(lParam);
			SetCapture(hWnd);
			break;
		}
		case WM_LBUTTONUP: {
			Camera::isDragging = false;
			ReleaseCapture();
			break;
		}
		case WM_MOUSEMOVE: {
			POINT pt = {(int)(short) LOWORD(lParam), (int)(short) HIWORD(lParam)};

			if (Camera::isDragging && GetCapture() != nullptr) {
				if (Camera::mousePosition.x != -1.0f) {
					Vector2D<float> offset = {pt.x - Camera::mousePosition.x, pt.y - Camera::mousePosition.y};
					Camera::startPosition += offset;
				}
				Camera::mousePosition.x = pt.x;
				Camera::mousePosition.y = pt.y;
//				std::printf("(%d, %d, %d)\n", lParam, pt.x, pt.y);
				InvalidateRect(hWnd, nullptr, false);
			}
			return 0;
		}
		case WM_DROPFILES: {
			// Get the file path of the dropped file
			HDROP hDrop = (HDROP) wParam;
			UINT fileCount = DragQueryFile(hDrop, 0xFFFFFFFF, nullptr, 0);
			if (fileCount > 0) {
				std::wstring filePath(256, L'\0');
				DragQueryFileW(hDrop, 0, &filePath[0], filePath.size());
				filePath.resize(wcslen(filePath.c_str())); // Resize to correct length
				svgFile = std::string(filePath.begin(), filePath.end());
				InvalidateRect(hWnd, nullptr, false);
			}
			DragFinish(hDrop);
			return 0;
		}
		case WM_KEYDOWN: {
			switch (static_cast<char>(wParam)) {
				case 'R': {
					InvalidateRect(hWnd, nullptr, false);
					break;
				}
				case 'W': {
					Camera::zoomIn();
					InvalidateRect(hWnd, nullptr, false);
					break;
				}
				case 'S': {
					Camera::zoomOut();
					InvalidateRect(hWnd, nullptr, false);
					break;
				}
				case 'A': {
					Camera::rotateClockWise();
					InvalidateRect(hWnd, nullptr, false);
					break;
				}
				case 'D': {
					Camera::rotateCounterClockWise();
					InvalidateRect(hWnd, nullptr, false);
					break;
				}
				default: {

				}
			}
			return 0;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
