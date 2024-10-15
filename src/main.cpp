#include <iostream>
#include <vector>
//#include <windows.h>

#include "../lib/rapidxml/rapidxml.hpp"
//#include "Graphic.h"

//#include <objidl.h>
//#include <gdiplus.h>
//
//#define APP_ID "svg-rendering"
//#define APP_NAME "SVG Render"
//
//using namespace Gdiplus;
//#pragma comment (lib, "Gdiplus.lib")
//
//VOID OnPaint(HDC hdc) {
//	Graphics graphics(hdc);
//	Pen pen(Color(255, 0, 0, 255));
//	graphics.DrawLine(&pen, 0, 0, 200, 100);
//	SolidBrush solidBrush(Color(255, 255, 0, 0));
////	Point point1 = Point(0, 0);
////	Point point2 = Point(102, 120);
////	Point point3 = Point(102, 10);
////	Point point4 = Point(10, 299);
////	Point points[4] = {point1,point2,point3,point4};
//	Point points[] = {{46,22}, {33,33}, {28,44}, {22,44}, {22,95}, {31,95}, {20,100}, {12,117}, {0,117}, {0,22}};
//	graphics.FillPolygon(&solidBrush, points, 10);
//	Point point2[] = {{46,22}, {28,44}, {19,30}};
//	graphics.FillPolygon(&solidBrush, point2, 3);
//	Point point3[] = {{31,95}, {12,117}, {4,106}};
//	graphics.FillPolygon(&solidBrush, point3, 3);
//}
//
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//
//INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow) {
//	HWND hWnd;
//	GdiplusStartupInput gdiplusStartupInput;
//	ULONG_PTR gdiplusToken;
//
//	// Initialize GDI+.
//	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
//
//	WNDCLASS wndClass = {.style = CS_HREDRAW | CS_VREDRAW, .lpfnWndProc = WndProc, .cbClsExtra = 0, .cbWndExtra = 0, .hInstance = hInstance, .hIcon = LoadIcon(nullptr, IDI_APPLICATION), .hCursor = LoadCursor(nullptr, IDC_ARROW), .hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH), .lpszMenuName = nullptr, .lpszClassName = TEXT(APP_ID)};
//
//	RegisterClass(&wndClass);
//
//	hWnd = CreateWindow(TEXT(APP_ID), TEXT(APP_NAME), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);
//
//	ShowWindow(hWnd, iCmdShow);
//	UpdateWindow(hWnd);
//	MSG msg;
//
//	while (GetMessage(&msg, nullptr, 0, 0)) {
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//	}
//
//	GdiplusShutdown(gdiplusToken);
//	return msg.wParam;
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
//	HDC hdc;
//	PAINTSTRUCT ps;
//
//	switch (message) {
//		case WM_PAINT:
//			hdc = BeginPaint(hWnd, &ps);
//			OnPaint(hdc);
//			EndPaint(hWnd, &ps);
//			return 0;
//		case WM_DESTROY:
//			PostQuitMessage(0);
//			return 0;
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//}

#include "../lib/raylib/raylib.h"
#include "../lib/raylib/rlgl.h"
#include "../lib/raylib/raymath.h"

//void DrawPolygonTextured(const Vector2 &position, const std::vector<Vector2> &points, const Texture2D &texture, Color tint) {
//	// bounding box
//	Vector2 min = points[0];
//	Vector2 max = points[0];
//
//	for (const auto &point: points) {
//		if (point.x > max.x)
//			max.x = point.x;
//		if (point.y > max.y)
//			max.y = point.y;
//		if (point.x < min.x)
//			min.x = point.x;
//		if (point.y < max.y)
//			min.y = point.y;
//	}
//	// normalize size
//	max.x = (max.x - min.x);
//	max.y = (max.y - min.y);
//
//	rlPushMatrix();
//
//	rlTranslatef(position.x, position.y, 0);
//
//	rlSetTexture(texture.id);
//
//	// we have to do quads to get textures
//	rlBegin(RL_QUADS);
//
//	rlColor4ub(tint.r, tint.g, tint.b, tint.a);
//
//	// draw a triangle from 0 to each edge, so we turn the polygon into a fan
//	// assumes points in CCW order
//	for (size_t i = 1; i < points.size() - 2; i++) {
//		rlTexCoord2f((points[0].x - min.x) / max.x, (points[0].y - min.y) / max.y);
//		rlVertex2f(points[0].x, points[0].y);
//		rlVertex2f(points[0].x, points[0].y);    // must double first vert because of quads
//
//		rlTexCoord2f((points[i].x - min.x) / max.x, (points[i].y - min.y) / max.y);
//		rlVertex2f(points[i].x, points[i].y);
//
//		rlTexCoord2f((points[i + 1].x - min.x) / max.x, (points[i + 1].y - min.y) / max.y);
//		rlVertex2f(points[i + 1].x, points[i + 1].y);
//	}
//
//	rlEnd();
//	rlSetTexture(0);
//	rlPopMatrix();
//}
//
//int main() {
//	InitWindow(800, 450, "raylib [core] example - basic window");
//	while (!WindowShouldClose()) {
//		BeginDrawing();
//		ClearBackground(WHITE);
//		DrawCircle(50, 50, 20, RED);
//		EndDrawing();
//	}
//	CloseWindow();
//	return 0;
//}

//#define MAX_POINTS  11      // 10 points and back to the start
//
//// Draw textured polygon, defined by vertex and texture coordinates
//void DrawTexturePoly(Texture2D texture, Vector2 center, Vector2 *points, Vector2 *texcoords, int pointCount, Color tint);
//
////------------------------------------------------------------------------------------
//// Program main entry point
////------------------------------------------------------------------------------------
//int main(void)
//{
//	// Initialization
//	//--------------------------------------------------------------------------------------
//	const int screenWidth = 800;
//	const int screenHeight = 450;
//
//	InitWindow(screenWidth, screenHeight, "raylib [textures] example - textured polygon");
//
//	// Define texture coordinates to map our texture to poly
//	Vector2 texcoords[MAX_POINTS] = {
//			(Vector2){ 0.75f, 0.0f },
//			(Vector2){ 0.25f, 0.0f },
//			(Vector2){ 0.0f, 0.5f },
//			(Vector2){ 0.0f, 0.75f },
//			(Vector2){ 0.25f, 1.0f},
//			(Vector2){ 0.375f, 0.875f},
//			(Vector2){ 0.625f, 0.875f},
//			(Vector2){ 0.75f, 1.0f},
//			(Vector2){ 1.0f, 0.75f},
//			(Vector2){ 1.0f, 0.5f},
//			(Vector2){ 0.75f, 0.0f}  // Close the poly
//	};
//
//	// Define the base poly vertices from the UV's
//	// NOTE: They can be specified in any other way
//	Vector2 points[MAX_POINTS] = { 0 };
//	for (int i = 0; i < MAX_POINTS; i++)
//	{
//		points[i].x = (texcoords[i].x - 0.5f)*256.0f;
//		points[i].y = (texcoords[i].y - 0.5f)*256.0f;
//	}
//
//	// Define the vertices drawing position
//	// NOTE: Initially same as points but updated every frame
//	Vector2 positions[MAX_POINTS] = { 0 };
//	for (int i = 0; i < MAX_POINTS; i++) positions[i] = points[i];
//
//	// Load texture to be mapped to poly
//	Texture texture = LoadTexture("resources/cat.png");
//
//	float angle = 0.0f;             // Rotation angle (in degrees)
//
//	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
//	//--------------------------------------------------------------------------------------
//
//	// Main game loop
//	while (!WindowShouldClose())    // Detect window close button or ESC key
//	{
//		// Update
//		//----------------------------------------------------------------------------------
//		// Update points rotation with an angle transform
//		// NOTE: Base points position are not modified
//		angle++;
//		for (int i = 0; i < MAX_POINTS; i++) positions[i] = Vector2Rotate(points[i], angle*DEG2RAD);
//		//----------------------------------------------------------------------------------
//
//		// Draw
//		//----------------------------------------------------------------------------------
//		BeginDrawing();
//
//		ClearBackground(RAYWHITE);
//
//		DrawText("textured polygon", 20, 20, 20, DARKGRAY);
//
//		DrawTexturePoly(texture, (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f },
//						positions, texcoords, MAX_POINTS, WHITE);
//
//		EndDrawing();
//		//----------------------------------------------------------------------------------
//	}
//
//	// De-Initialization
//	//--------------------------------------------------------------------------------------
//	UnloadTexture(texture); // Unload texture
//
//	CloseWindow();          // Close window and OpenGL context
//	//--------------------------------------------------------------------------------------
//
//	return 0;
//}
//
//// Draw textured polygon, defined by vertex and texture coordinates
//// NOTE: Polygon center must have straight line path to all points
//// without crossing perimeter, points must be in anticlockwise order
//void DrawTexturePoly(Texture2D texture, Vector2 center, Vector2 *points, Vector2 *texcoords, int pointCount, Color tint)
//{
//	rlSetTexture(texture.id);
//
//	// Texturing is only supported on RL_QUADS
//	rlBegin(RL_QUADS);
//
//	rlColor4ub(tint.r, tint.g, tint.b, tint.a);
//
//	for (int i = 0; i < pointCount - 1; i++)
//	{
//		rlTexCoord2f(0.5f, 0.5f);
//		rlVertex2f(center.x, center.y);
//
//		rlTexCoord2f(texcoords[i].x, texcoords[i].y);
//		rlVertex2f(points[i].x + center.x, points[i].y + center.y);
//
//		rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
//		rlVertex2f(points[i + 1].x + center.x, points[i + 1].y + center.y);
//
//		rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
//		rlVertex2f(points[i + 1].x + center.x, points[i + 1].y + center.y);
//	}
//	rlEnd();
//
//	rlSetTexture(0);
//}

#include "raylib.h"
#include <stdlib.h>  // For rand() and srand()
#include <time.h>    // For time()
//
//// Function to generate random polygon points
//void GenerateRandomPolygon(Vector2* vertices, int sides, float radius, Vector2 center) {
//	for (int i = 0; i < sides; i++) {
//		// Generate random angle and calculate position
//		float angle = (float)i / (float)sides * 2.0f * PI;  // Dividing full circle by number of sides
//		vertices[i].x = center.x + radius * cosf(angle + GetRandomValue(-100, 100) / 100.0f); // Slight random offset
//		vertices[i].y = center.y + radius * sinf(angle + GetRandomValue(-100, 100) / 100.0f);
//	}
//}
//
//int main() {
//	// Initialization
//	const int screenWidth = 1900;
//	const int screenHeight = 1280;
//	InitWindow(screenWidth, screenHeight, "Random Filled Polygon with raylib");
//
//	// Set up for random number generation
//	srand(time(nullptr));
//
//	// Polygon parameters
//	int sides = GetRandomValue(3, 8); // Random number of sides (3 to 8)
//	float radius = 100.0f;            // Radius of polygon
//	Vector2 center = { screenWidth / 2, screenHeight / 2 };
//
//	Vector2 vertices[8];  // Array to store vertices, max 8 sides
//	GenerateRandomPolygon(vertices, sides, radius, center);  // Generate polygon points
//
//	SetTargetFPS(60);
//
//	// Main game loop
//	while (!WindowShouldClose()) {
//		// Update
//
//		// Draw
//		BeginDrawing();
//		ClearBackground(RAYWHITE);
//		int sx = GetScreenWidth() / 10;
//		int sy = GetScreenHeight() / 10;
//		for (int i = 0; i < sx; i++) {
//			for (int j = 0; j < sy; j++) {
//				if  ((i + j) % 2 == 0) {
//					DrawRectangle(i * 10, j * 10, 10, 10, GRAY);
////					DrawPixel(i, j, WHITE);
//				}
//			}
//   		}
//
//		// Draw the filled polygon using DrawTriangleFan
//		DrawTriangleFan(vertices, sides, YELLOW);  // Fill the polygon with color YELLOW
//
//		EndDrawing();
//	}
//
//	// De-Initialization
//	CloseWindow();  // Close window and OpenGL context
//
//	return 0;
//}
