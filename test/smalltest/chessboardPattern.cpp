#include <windows.h>
#include <iostream>

// Function to create a chessboard bitmap
HBITMAP CreateChessboardBitmap() {
    const int squareSize = 16; // Size of each square in pixels
    const int boardSize = 8;   // 8x8 chessboard

    // Create a DIB (Device Independent Bitmap) header
    BITMAPINFOHEADER bih = {};
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = boardSize * squareSize;
    bih.biHeight = -boardSize * squareSize; // Negative height for top-down DIB
    bih.biPlanes = 1;
    bih.biBitCount = 1; // 1-bit color (black and white)
    bih.biCompression = BI_RGB;
    bih.biSizeImage = 0;
    bih.biXPelsPerMeter = 0;
    bih.biYPelsPerMeter = 0;
    bih.biClrUsed = 2; // Only 2 colors (black and white)
    bih.biClrImportant = 0;

    // Create a DIB section and get the pointer to the bitmap data
    void* bits = nullptr;
    HBITMAP hBitmap = CreateDIBSection(NULL, (BITMAPINFO*)&bih, DIB_RGB_COLORS, &bits, NULL, 0);
    if (!hBitmap) {
        std::cerr << "Failed to create bitmap!" << std::endl;
        return nullptr;
    }

    // Set the two colors (black and white)
    RGBQUAD colors[2] = { {0, 0, 0, 0}, {255, 255, 255, 0} }; // Black and white
    SetDIBColorTable(NULL, 0, 2, colors);  // Set color table to black and white

    // Calculate the stride (the number of bytes in one row)
    int rowStride = ((bih.biWidth + 31) / 32) * 4; // 4 bytes per pixel row, padded to a multiple of 4

    // Fill the bitmap data with the chessboard pattern
    for (int y = 0; y < boardSize; ++y) {
        for (int x = 0; x < boardSize; ++x) {
            // Set alternate squares to black and white
            int color = ((x + y) % 2 == 0) ? 1 : 0;  // 1 is white, 0 is black

            for (int py = 0; py < squareSize; ++py) {
                for (int px = 0; px < squareSize; ++px) {
                    // Calculate the pixel offset
                    int offset = (y * squareSize + py) * rowStride + (x * squareSize + px) / 8;
                    BYTE bitPos = (x * squareSize + px) % 8;

                    // Set the corresponding bit to the color
                    if (color == 1) {
                        ((BYTE*)bits)[offset] |= (0x80 >> bitPos);  // Set the bit to 1 (white)
                    } else {
                        ((BYTE*)bits)[offset] &= ~(0x80 >> bitPos); // Set the bit to 0 (black)
                    }
                }
            }
        }
    }

    return hBitmap;
}

// Window procedure for drawing the chessboard background
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

			{
				HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
            	FillRect(hdc, &ps.rcPaint, hBrush);
				DeleteObject(hBrush);
			}
            // Create a chessboard bitmap
            HBITMAP hChessboard = CreateChessboardBitmap();
            if (hChessboard) {
                // Create a pattern brush from the bitmap
                HBRUSH hBrush = CreatePatternBrush(hChessboard);
                if (hBrush) {
                    // Use the brush to fill the window with the chessboard pattern
                    FillRect(hdc, &ps.rcPaint, hBrush);
                    DeleteObject(hBrush); // Clean up the brush
                }
                DeleteObject(hChessboard); // Clean up the bitmap
            }

            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Entry point for the application
int main() {
    const char CLASS_NAME[] = "ChessboardClass";

    // Register the window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClass(&wc)) {
        std::cerr << "Window class registration failed!" << std::endl;
        return 0;
    }

    // Create the window with the specified size 1200x500
    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Chessboard Pattern",
                               WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1200, 500,
                               NULL, NULL, wc.hInstance, NULL);

    if (!hwnd) {
        std::cerr << "Window creation failed!" << std::endl;
        return 0;
    }

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
