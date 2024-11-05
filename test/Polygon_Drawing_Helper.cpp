#include "../lib/raylib/raylib.h"
#include "../lib/raylib/rlgl.h"
#include "../lib/raylib/raymath.h"

void DrawPolyPro(Vector2 center, Vector2 *points, int pointCount, Color color) {
	if (pointCount >= 3 && points != nullptr) {
		rlBegin(RL_TRIANGLES);
		for (int i = 0; i < pointCount; i++) {
			rlColor4ub(color.r, color.g + i * 10, color.b, color.a);
			int j = (i + 1) % pointCount;

			rlVertex2f(points[i].x, points[i].y);
			rlVertex2f(center.x, center.y);
			rlVertex2f(points[j].x, points[j].y);
		}

		rlEnd();
	}
}


void DrawPolyW(Vector2 *points, int pointCount, Color color) {
	if (pointCount >= 3 && points != nullptr) {
		rlBegin(RL_TRIANGLES);
		for (int i = 0; i < pointCount; i++) {
			rlColor4ub(color.r, (color.g + i * 10) % 256, color.b, color.a);
			int j = (i + 1) % pointCount;
			int k = (i + 2) % pointCount;

			rlVertex2f(points[i].x, points[i].y);
			rlVertex2f(points[j].x, points[j].y);
			rlVertex2f(points[k].x, points[k].y);
		}

		rlEnd();
	}
}

int main() {
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes drawing");

	float rotation = 0.0f;

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	int mode = 1;
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		Vector2 vertices[] = {
			{ 100.0f, 150.0f },
			{ 150.0f, 350.0f },
			{ 300.0f, 150.0f },
			{ 200.0f, 50.0f },
			{ 350.0f, 250.0f },
			{ 250.0f, 350.0f },
			{ 50.0f, 250.0f },
		};
		int vertexCount = sizeof(vertices) / sizeof(vertices[0]);

		if (IsKeyPressed(KEY_W)) {
			++mode %= 5;
		}
		Vector2 center = GetMousePosition();
		switch (mode) {
			case 0:
				DrawPolyW(vertices, vertexCount, PINK);
				break;
			case 1:
				DrawPolyPro(vertices[0], vertices, vertexCount, BLUE);
				break;
			case 3:
				break;
				DrawTriangleStrip(vertices, vertexCount, ColorAlpha(RED, 0.9));
			default:
				DrawTriangleFan(vertices, vertexCount, ColorAlpha(RED, 0.9));
		}

		for (int i = 0; i < vertexCount; ++i) DrawLineEx(vertices[i], vertices[(i + 1) % vertexCount], 3, BLACK);

		DrawCircleV(vertices[0], 7, BLACK);
		DrawCircleV(vertices[1], 7, BROWN);

		EndDrawing();
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}