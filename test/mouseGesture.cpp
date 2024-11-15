#define _WIN32_WINNT 0x0602  // Windows 8 or later

#include <windows.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#include <Winuser.h>

struct TouchData {
	POINT touchPoint;
	bool isDown;
};

class GestureHandler {
public:
	GestureHandler() : firstTouchIndex(-1), secondTouchIndex(-1) {}

	void ProcessPointerEvent(WPARAM wParam, LPARAM lParam) {
		// Extract the pointer information
		POINTER_INFO pointerInfo;
		GetPointerInfo(wParam, &pointerInfo);

		// Find the touch index (finger index)
		int touchIndex = pointerInfo.pointerId;

		if (pointerInfo.pointerFlags & POINTER_FLAG_DOWN) {
			if (firstTouchIndex == -1) {
				firstTouchIndex = touchIndex;
			} else if (secondTouchIndex == -1) {
				secondTouchIndex = touchIndex;
			}
			touchData.push_back({ pointerInfo.ptPixelLocation, true });
		}
		else if (pointerInfo.pointerFlags & POINTER_FLAG_UP) {
			if (touchIndex == firstTouchIndex) {
				firstTouchIndex = -1;
			} else if (touchIndex == secondTouchIndex) {
				secondTouchIndex = -1;
			}
			touchData.push_back({ pointerInfo.ptPixelLocation, false });
		}

		if (firstTouchIndex != -1 && secondTouchIndex != -1) {
			// Handle two-finger gestures
			DetectGesture();
		}
	}

private:
	void DetectGesture() {
		if (touchData.size() < 2) return;

		const POINT& firstFinger = touchData[0].touchPoint;
		const POINT& secondFinger = touchData[1].touchPoint;

		// Detect pinch (zoom) gestures
		int deltaX = abs(firstFinger.x - secondFinger.x);
		int deltaY = abs(firstFinger.y - secondFinger.y);

		// If fingers are close enough, it's a zoom gesture
		if (deltaX < 50 && deltaY < 50) {
			// Calculate zoom direction based on distance change
			static int lastDistance = -1;
			int currentDistance = sqrt(deltaX * deltaX + deltaY * deltaY);
			if (lastDistance != -1) {
				if (currentDistance > lastDistance) {
					std::cout << "Zoom Out\n";
				} else if (currentDistance < lastDistance) {
					std::cout << "Zoom In\n";
				}
			}
			lastDistance = currentDistance;
		}

		// Detect scroll gestures based on finger movement (vertical/horizontal)
		if (deltaX > deltaY) {
			if (firstFinger.x < secondFinger.x) {
				std::cout << "Scroll Right\n";
			} else {
				std::cout << "Scroll Left\n";
			}
		} else {
			if (firstFinger.y < secondFinger.y) {
				std::cout << "Scroll Down\n";
			} else {
				std::cout << "Scroll Up\n";
			}
		}
	}

private:
	std::vector<TouchData> touchData;
	int firstTouchIndex;
	int secondTouchIndex;
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static GestureHandler gestureHandler;

	switch (uMsg) {
		case WM_MOUSEWHEEL: {
			std::cout << "MOUSE WHEEL\n";
			break;
		}
		case WM_MOUSEMOVE: {
			std::cout << "MOUSE MOVE\n";
			break;
		}
		case WM_POINTERDOWN:
			std::cout << "WM_POINTERDOWN received\n";
			gestureHandler.ProcessPointerEvent(wParam, lParam);
			break;

		case WM_POINTERUPDATE:
			std::cout << "WM_POINTERUPDATE received\n";
			gestureHandler.ProcessPointerEvent(wParam, lParam);
			break;

		case WM_POINTERUP:
			std::cout << "WM_POINTERUP received\n";
			gestureHandler.ProcessPointerEvent(wParam, lParam);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}


int main() {
	// Register the window class
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = TEXT("GestureApp");
	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(0, TEXT("GestureApp"), TEXT("Multi-Touch Gestures"), WS_OVERLAPPEDWINDOW,
							   CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
							   NULL, NULL, wc.hInstance, NULL);

	RegisterTouchWindow(hwnd, TWF_WANTPALM);

	ShowWindow(hwnd, SW_SHOWNORMAL);
	MSG msg;
	while (GetMessage(&msg, hwnd, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
