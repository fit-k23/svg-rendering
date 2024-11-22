#include <windows.h>
#include <crtdbg.h>

#define TEST_DEBUG

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int main() {
#ifdef TEST_DEBUG
	// Enable memory leak detection.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Win32 application code
	HINSTANCE hInstance = GetModuleHandle(NULL);
	WNDCLASS wc = {0};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("MemoryLeakApp");
	RegisterClass(&wc);

	HWND hwnd = CreateWindow(wc.lpszClassName, TEXT("Memory Leak Detection"),
							 WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
							 800, 600, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	// Simulate some memory allocations
	int* p = new int[100];  // Simulate a leak here (no delete call)

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
