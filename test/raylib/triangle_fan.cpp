#include "../../lib/raylib/raylib.h"

int main(void) {
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [shapes] example - DrawTriangleFan()");

	Vector2 points[6] = {
			{ 200, 200 },
			{ 100, 100 },
			{ 100, 300 },
			{ 300, 300 },
			{ 300, 100 },
			{ 100, 100 }
	};

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		for (int i = 0; i < 6; i++) {
			DrawLineEx(points[i], points[(i + 1) % 6], 3, BLUE);
			DrawTriangle(points[i], points[(i + 1) % 6], points[(i + 2) % 6], ColorAlpha(RED, i / 6.0f));
		}

		DrawTriangleFan(points, 6, ColorAlpha(BLUE, 0.5));   // It draws a RED square shape (4 triangles)

		EndDrawing();
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}