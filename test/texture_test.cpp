#include "../lib/raylib/raylib.h"
#include "../lib/raylib/rlgl.h"
#include "../lib/raylib/raymath.h"

#include <iostream>

using namespace std;

void DrawEllipseHQ(int centerX, int centerY, float radiusH, float radiusV, Color color, int step = 1) {
	rlBegin(RL_TRIANGLES);
	for (int i = 0; i < 360; i += step) {
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f((float) centerX, (float) centerY);
		rlVertex2f((float) centerX + cosf(DEG2RAD * (i + step)) * radiusH,(float) centerY + sinf(DEG2RAD * (i + step)) * radiusV);
		rlVertex2f((float) centerX + cosf(DEG2RAD * i) * radiusH, (float) centerY + sinf(DEG2RAD * i) * radiusV);
	}
	rlEnd();
}

int main() {
	Vector2 screenSize = {900, 700};
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
//	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(screenSize.x, screenSize.y, "Texture text");

	RenderTexture rt = LoadRenderTexture(900, 700);

	SetTextureFilter(rt.texture, TEXTURE_FILTER_TRILINEAR);
	Vector2 hsS = Vector2Scale(screenSize, 0.5);
	Camera2D camera;
	camera.target = hsS;
	camera.offset = camera.target;
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_Q)) {
			SetTextureFilter(rt.texture, TEXTURE_FILTER_TRILINEAR);
			SetWindowState(FLAG_MSAA_4X_HINT);
		} else {
			SetTextureFilter(rt.texture, TEXTURE_FILTER_POINT);
		}
		BeginTextureMode(rt);
		ClearBackground(BLANK);
		DrawEllipseHQ(50, 50, 200, 50, ColorAlpha(BLUE, 0.9));
		DrawText("Hello world! This is raylib in C++!!!!", -10, 10, 20, BLACK);
		EndTextureMode();

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 delta = Vector2Scale(GetMouseDelta(), -1.0f / camera.zoom);
			camera.target = Vector2Add(camera.target, delta);
		}

		if (IsKeyDown(KEY_W)) camera.rotation += 0.05;
		if (IsKeyDown(KEY_S)) camera.rotation -= 0.05;

		// Update camera position with arrow keys
		if (IsKeyDown(KEY_UP)) camera.target.y += 0.5;
		if (IsKeyDown(KEY_DOWN)) camera.target.y -= 0.5;
		if (IsKeyDown(KEY_LEFT)) camera.target.x += 0.5;
		if (IsKeyDown(KEY_RIGHT)) camera.target.x -= 0.5;

		float wheel = GetMouseWheelMove();
		if (wheel != 0) {
			camera.zoom += (GetMouseWheelMove() * 0.05f);
			if (camera.zoom > 10.0f) camera.zoom = 10.0f;
			else if (camera.zoom < 0.1f) camera.zoom = 0.1f;
		}

		if (IsKeyPressed(KEY_R)) {
			camera.target = hsS;
			camera.offset = camera.target;
			camera.rotation = 0.0f;
			camera.zoom = 1.0f;
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(camera);
		DrawTexture(rt.texture, 0, 0, WHITE);
		DrawEllipseHQ(50, 50, 200, 50, ColorAlpha(BLUE, 0.9));
		DrawLineEx(Vector2Add(hsS,{-50, 0}), Vector2Add(hsS, {25, 0}), 3, ColorAlpha(RED, 0.7));
		DrawCircleV(hsS, 3, BLACK);
		EndMode2D();
		DrawCircleV(Vector2Add(hsS,{0, 50}), 3 * camera.zoom, BLACK);
		EndDrawing();
	}
	UnloadRenderTexture(rt);

	return 0;
}