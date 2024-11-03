#include "../../lib/raylib/raylib.h"
#include "../../lib/raylib/raymath.h"
#include "../../lib/raylib/rlgl.h"

int main() {
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(1280, 800, "Example");
	SetTargetFPS(144);

	Vector2 center{ GetScreenWidth() * 0.25f, GetScreenHeight() * 0.5f };
	Vector2 rectangleSize = { 200, 400 };

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);

		rlPushMatrix();
		rlViewport(-300, 100, 1280, 800);
		rlTranslatef(center.x, center.y, 0); // center of rotation in screen space
		rlRotatef(float(GetTime()) * 90, 0, 0, 1); // rotation (90 degrees per second)

		DrawRectangleLinesEx(Rectangle{ rectangleSize.x * -0.5f, rectangleSize.y * -0.5f, rectangleSize.x, rectangleSize.y }, 2.0f, RED); // draw rectangle relative to the transform not in screen space

		rlPopMatrix();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}