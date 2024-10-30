#include <iostream>

#include "../lib/raylib/raylib.h"
#include "../lib/raylib/rlgl.h"
#include "../lib/raylib/raymath.h"
#include "Graphic.h"
#include "XMLParser.h"

int main() {
	// Initialization
	const int screenWidth = 900;
	const int screenHeight = 600;
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	// Enable MSAA 4X anti-aliasing
//	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(screenWidth, screenHeight, "Random Filled Polygon with raylib");
//	int display = GetCurrentMonitor();
//	SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));

	// Set up for random number generation
	SetTargetFPS(60);

	Camera2D camera = {0};
	camera.offset = Vector2Zero();
	camera.zoom = 1.0f;

	std::vector<Element*> v;
	XMLParser parser;
	parser.traverseXML("sample.svg", v);

	std::cout << (int)v.size() << '\n';

	for (int i = 0; i < (int)v.size(); ++i) {
		std::cout << "[Rectangle " << i << "]\n";
		v[i]->dbg();
		static_cast<Rect*>(v[i])->draw(); // <-- cast Element* to Rect*
	}

	for (int i = 0; i < (int)v.size(); ++i) delete v[i];

	/***** TEMPORARY COMMENT FOR TESTING *****/
	//Ellipse e({50, 50}, {200, 200, 100, 255}, {0, 0, 0, 133}, 2.0, {300.2, 100.2});

	//// Main game loop
	//while (!WindowShouldClose()) {
	//	float wheel = GetMouseWheelMove();
	//	if (wheel != 0) {
	//		// Get the world point that is under the mouse
	//		Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

	//		// Set the offset to where the mouse is
	//		camera.offset = GetMousePosition();

	//		// Set the target to match, so that the camera maps the world space point
	//		// under the cursor to the screen space point under the cursor at any zoom
	//		camera.target = mouseWorldPos;

	//		// Zoom increment
	//		float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
	//		if (wheel < 0) scaleFactor = 1.0f / scaleFactor;
	//		camera.zoom = Clamp(camera.zoom * scaleFactor, 0.125f, 64.0f);
	//	}
	//	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
	//		printf("Left is down\n");
	//		camera.rotation++;
	//		if (360 - camera.rotation < 0.5) {
	//			camera.rotation = 0;
	//		}
	//	}

	//	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
	//		Vector2 delta = GetMouseDelta();
	//		delta = Vector2Scale(delta, -1.0f / camera.zoom);
	//		camera.target = Vector2Add(camera.target, delta);
	//	}

	//	// Draw
	//	BeginDrawing();
	//	ClearBackground(BLACK);
	//	int sx = GetScreenWidth() / 10;
	//	int sy = GetScreenHeight() / 10;

	//	for (int i = 0; i < sx; i++) {
	//		for (int j = 0; j < sy; j++) {
	//			if ((i + j) % 2 == 0) {
	//				DrawRectangle(i * 10, j * 10, 10, 10, GRAY);
	//			}
	//		}
	//	}

	//	DrawRectangle(0, 0, 350, 75, ColorAlpha({20, 20, 20}, 0.75));
	//	DrawText("Hold left click to move camera", 0, 0, 20, YELLOW);
	//	DrawText("Scroll mouse wheel to zoom in/out", 0, 25, 20, YELLOW);
	//	DrawText("Hold right click to rotate camera", 0, 50, 20, YELLOW);

	//	BeginMode2D(camera);

	//	DrawRectangle(GetScreenWidth() / 2 - 250, GetScreenHeight() / 2 - 250, 500, 500, ColorAlpha(BLUE,0.5));

	//	e.draw();

	//	DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 50, MAROON);
	//	EndMode2D();

	//	EndDrawing();
	//}

	CloseWindow();
	return 0;
}
