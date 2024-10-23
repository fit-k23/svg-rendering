#include <iostream>
#include <vector>
#include <string>
#include "time.h"
#include "../lib/rapidxml/rapidxml.hpp"
//#include "Graphic.h"
#include "../lib/raylib/raylib.h"
#include "../lib/raylib/rlgl.h"
#include "../lib/raylib/raymath.h"

#include "raylib.h"

// Function to generate random polygon points
void GenerateRandomPolygon(Vector2 *vertices, int sides, float radius, Vector2 center) {
	for (int i = 0; i < sides; i++) {
		// Generate random angle and calculate position
		float angle = (float) i / (float) sides * 2.0f * PI;  // Dividing full circle by number of sides
		vertices[i].x = center.x + radius * cosf(angle + GetRandomValue(-100, 100) / 100.0f); // Slight random offset
		vertices[i].y = center.y + radius * sinf(angle + GetRandomValue(-100, 100) / 100.0f);
	}
}

int main() {
	// Initialization
	const int screenWidth = 900;
	const int screenHeight = 600;
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Random Filled Polygon with raylib");
	int display = GetCurrentMonitor();
//	SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));

	// Set up for random number generation
	srand(time(nullptr));

	// Polygon parameters
	int sides = GetRandomValue(3, 8); // Random number of sides (3 to 8)
	float radius = 100.0f;            // Radius of polygon
	Vector2 center = {screenWidth / 2, screenHeight / 2};

	Vector2 vertices[8];  // Array to store vertices, max 8 sides
	GenerateRandomPolygon(vertices, sides, radius, center);  // Generate polygon points

	SetTargetFPS(60);

	Camera2D camera = {0};
	camera.offset = Vector2Zero();
	camera.zoom = 1.0f;

	// Main game loop
	while (!WindowShouldClose()) {
		float wheel = GetMouseWheelMove();
		if (wheel != 0) {
			// Get the world point that is under the mouse
			Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

			// Set the offset to where the mouse is
			camera.offset = GetMousePosition();

			// Set the target to match, so that the camera maps the world space point
			// under the cursor to the screen space point under the cursor at any zoom
			camera.target = mouseWorldPos;

			// Zoom increment
			float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
			if (wheel < 0) scaleFactor = 1.0f / scaleFactor;
			camera.zoom = Clamp(camera.zoom * scaleFactor, 0.125f, 64.0f);
		}
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			printf("Left is down\n");
			camera.rotation++;
			if (360 - camera.rotation < 0.5) {
				camera.rotation = 0;
			}
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			Vector2 delta = GetMouseDelta();
			delta = Vector2Scale(delta, -1.0f / camera.zoom);
			camera.target = Vector2Add(camera.target, delta);
		}

		// Draw
		BeginDrawing();
		ClearBackground(BLACK);
		int sx = GetScreenWidth() / 10;
		int sy = GetScreenHeight() / 10;

		for (int i = 0; i < sx; i++) {
			for (int j = 0; j < sy; j++) {
				if ((i + j) % 2 == 0) {
					DrawRectangle(i * 10, j * 10, 10, 10, GRAY);
//					DrawPixel(i, j, WHITE);
				}
			}
		}

		DrawRectangle(0, 0, 350, 75, ColorAlpha({20, 20, 20}, 0.75));
		DrawText("Hold right click to move camera", 0, 0, 20, YELLOW);
		DrawText("Scroll mouse wheel to zoom in/out", 0, 25, 20, YELLOW);
		DrawText("Hold left click to rotate camera", 0, 50, 20, YELLOW);

		BeginMode2D(camera);

		// Draw the 3d grid, rotated 90 degrees and centered around 0,0
		// just so we have something in the XY plane

		// Draw a reference circle
		DrawRectangle(GetScreenWidth() / 2 - 250, GetScreenHeight() / 2 - 250, 500, 500, ColorAlpha(BLUE,0.5));

		DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 50, MAROON);
		EndMode2D();

		// Draw the filled polygon using DrawTriangleFan
//		DrawTriangleFan(vertices, sides, YELLOW);  // Fill the polygon with color YELLOW

		EndDrawing();
	}

	// De-Initialization
	CloseWindow();  // Close window and OpenGL context

	return 0;
}
