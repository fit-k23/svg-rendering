#include <iostream>
#include "conio.h"
#include "api/XMLParser.h"
#include "api/Graphic.h"

/// Raylib
#include "../lib/raylib/raylib.h"
#include "../lib/raylib/rlgl.h"
#include "../lib/raylib/raymath.h"
#include "utils/Raylibex.h"
#include "utils/Icon.h"

#define APPLICATION_NAME "SVG RENDERING"

void app() {
	Vector2 screenSize = {800, 600};

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	//Enable MSAA 4X anti-aliasing
	SetConfigFlags(FLAG_MSAA_4X_HINT);

	//Better image but blurry text...
	//SetConfigFlags(FLAG_WINDOW_HIGHDPI);

	InitWindow(screenSize.x, screenSize.y, APPLICATION_NAME);

	Image icon = LoadImageFromMemory(".png", ICON_DATA, ICON_LEN);

	if (icon.data != nullptr) {
		// Set the window icon
		SetWindowIcon(icon);
		// We no longer need the image in memory once the icon is set
		UnloadImage(icon);
	} else {
		printf("Failed to load icon.\n");
	}

	Camera2D camera;
	camera.target = Vector2Scale(screenSize, 0.5f);
	camera.offset = camera.target;
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	SetTargetFPS(60);

	Rectangle scissorArea = { 100, 100, 300, 300 };
	bool maximumWindow = false;
	Vector2 previousScreenSize = screenSize;

	while (!WindowShouldClose()) {
		float wheel = GetMouseWheelMove();
		if (wheel != 0) {
//			camera.offset = GetMousePosition();
//			camera.target = GetScreenToWorld2D(GetMousePosition(), camera);
//
//			float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
//			if (wheel < 0) scaleFactor = 1.0f / scaleFactor;
//			camera.zoom = Clamp(camera.zoom * scaleFactor, 0.125f, 64.0f);

			camera.zoom += (GetMouseWheelMove() * 0.05f);
			if (camera.zoom > 3.0f) camera.zoom = 3.0f;
			else if (camera.zoom < 0.1f) camera.zoom = 0.1f;
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 delta = Vector2Scale(GetMouseDelta(), -1.0f / camera.zoom);
			camera.target = Vector2Add(camera.target, delta);
		}

		if (IsKeyPressed(KEY_F)) {
			if (maximumWindow) {
				previousScreenSize = screenSize;
				MaximizeWindow();
			} else {
				SetWindowSize(previousScreenSize.x, previousScreenSize.y);
			}
			maximumWindow = !maximumWindow;
		}

		Vector2 currentScreenSize = {static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};

		if (screenSize.x != currentScreenSize.x || screenSize.y != currentScreenSize.y) {
			previousScreenSize = screenSize;
			screenSize = currentScreenSize;
		}

		if (IsKeyPressed(KEY_R)) {
			camera.target = Vector2Scale(screenSize, 0.5f);
			camera.offset = camera.target;
			camera.rotation = 0.0f;
			camera.zoom = 1.0f;
		}

		if (IsKeyDown(KEY_RIGHT)) camera.target.x -= 5;
		if (IsKeyDown(KEY_LEFT)) camera.target.x += 5;
		if (IsKeyDown(KEY_UP)) camera.target.y += 5;
		if (IsKeyDown(KEY_DOWN)) camera.target.y -= 5;
//		if (IsKeyDown(KEY_EQUAL)) camera.zoom *= 0.05f;
//		if (IsKeyDown(KEY_MINUS)) camera.zoom /= 0.05f;

		int screenWidth = screenSize.x;
		int screenHeight = screenSize.y;

		BeginDrawing();
		ClearBackground(BLACK);
		int sx = GetScreenWidth() / 10;
		int sy = GetScreenHeight() / 10;

		for (int i = 0; i < sx; i++) {
			for (int j = 0; j < sy; j++) {
				if ((i + j) % 2 == 0) {
					DrawRectangle(i * 10, j * 10, 10, 10, GRAY);
				}
			}
		}

		DrawRectangle(0, 0, 350, 75, ColorAlpha({20, 20, 20}, 0.75));
		DrawText("Hold left click to move camera", 0, 0, 20, YELLOW);
		DrawText("Scroll mouse wheel to zoom in/out", 0, 25, 20, YELLOW);
		DrawText("Hold right click to rotate camera", 0, 50, 20, YELLOW);

		BeginMode2D(camera);
		DrawRectangleLines(0, 0, screenWidth, screenHeight, RED);
		DrawRectangleLines(-1, -1, screenWidth + 1, screenHeight + 1, RED);
		DrawCircle(400, 300, 100, ColorAlpha(RED, 0.9));
		DrawCircle(screenWidth / 2, screenHeight / 2, 10, YELLOW);
		EndMode2D();
		EndDrawing();
	}

	CloseWindow();
}

void test() {
	Vector2 screenSize = { 800, 600 };

	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	//Enable MSAA 4X anti-aliasing
	//SetConfigFlags(FLAG_MSAA_4X_HINT);

	//Better image but blurry text...
	//SetConfigFlags(FLAG_WINDOW_HIGHDPI);

	InitWindow(screenSize.x, screenSize.y, APPLICATION_NAME);
	
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		Vector2 points[] = {{0, 40}, {40, 40}, {40, 80}, {80, 80}, {80, 120}, {120, 120}, {120, 140}};
		DrawTriangleFan(points, 7, WHITE);
		EndDrawing();
	}

	CloseWindow();
}

int main() {
	//app();
	test();
	//std::cout << "\n\n";
	//XMLParser parser;
	//std::vector<Element*> v;
	//parser.traverseXML("sample.svg", v);
	//std::cout << (int)v.size() << '\n';

	//for (int i = 0; i < (int)v.size(); ++i)
	//	v[i]->dbg();

	//for (int i = 0; i < (int)v.size(); ++i) delete v[i];

	return 0;
}
