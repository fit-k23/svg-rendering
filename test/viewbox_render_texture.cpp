#include "../lib/raylib/raylib.h"
#include "../lib/raylib/raymath.h"

void InRender(const Vector2 &offset, const Camera2D &camera) {
	// Draw within the scissor area
	ClearBackground(BLANK);

	DrawCircle(0, 0, 100 * camera.zoom, ColorAlpha(YELLOW, 1));
	DrawCircle(150, 100, 100 * camera.zoom, ColorAlpha(BLUE, 1));
	DrawEllipse(250, 250, 300 * camera.zoom, 50, ColorAlpha(GREEN, 1));

	DrawText("FLIPPED", 0, 150, 20, BLACK);
}

void DrawRender(RenderTexture2D &rtex, const Vector2 &offset, const Camera2D &camera) { //, void (*callback)(const Vector2 &offset)) {
	BeginTextureMode(rtex);
	InRender(offset, camera);
	EndTextureMode();
}

int main() {
	int screenWidth = 800;
	int screenHeight = 600;
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	// Enable MSAA 4X anti-aliasing
	// SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(screenWidth, screenHeight, "raylib [core] example - texture with camera");

	// Initialize camera
	Camera2D camera = { 0 };
	camera.target = {screenWidth / 2.0f, screenHeight / 2.0f};
	camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	Rectangle drawArea = { 100, 100, 300, 300 };
	RenderTexture2D rtex = LoadRenderTexture(drawArea.width, drawArea.height);

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_RIGHT)) camera.target.x -= 5;
		if (IsKeyDown(KEY_LEFT)) camera.target.x += 5;
		if (IsKeyDown(KEY_UP)) camera.target.y += 5;
		if (IsKeyDown(KEY_DOWN)) camera.target.y -= 5;

		camera.zoom += (GetMouseWheelMove() * 0.05f);
		if (camera.zoom > 3.0f) camera.zoom = 3.0f;
		else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

		int nScrWid = GetScreenWidth();
		int nScrHei = GetScreenHeight();
		if (nScrWid != screenWidth || nScrHei != screenHeight) {
			screenWidth = nScrWid;
			screenHeight = nScrHei;
			UnloadRenderTexture(rtex);
			rtex = LoadRenderTexture(screenWidth, screenHeight);
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		BeginMode2D(camera);
		DrawRectangleLines(0, 0, screenWidth, screenHeight, RED);

		Rectangle sMR{
				(drawArea.x - camera.target.x) * camera.zoom + camera.offset.x,
				(drawArea.y - camera.target.y) * camera.zoom + camera.offset.y,
				(drawArea.width) * camera.zoom,
				(drawArea.height) * camera.zoom
		};

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			DrawCircle(0, 0, 100, ColorAlpha(YELLOW, 0.5));
			DrawCircle(150, 100, 100, ColorAlpha(BLUE, 0.5));
			DrawEllipse(250, 250, 300, 50, ColorAlpha(GREEN, 0.5));
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 delta = Vector2Scale(GetMouseDelta(), -1.0f / camera.zoom);
			camera.target = Vector2Add(camera.target, delta);
		}

		if (IsKeyPressed(KEY_R)) {
			camera.target = {screenWidth / 2.0f, screenHeight / 2.0f};
			camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
			camera.rotation = 0.0f;
			camera.zoom = 1.0f;
		}

		DrawRender(rtex, {sMR.x, sMR.y}, camera);

		Rectangle sourceRect = { 0.0f, 0.0f, (float)rtex.texture.width, -(float)rtex.texture.height };
		Rectangle destRect = { sMR.x, sMR.y, sMR.width, sMR.height };

		DrawTexturePro(rtex.texture, sourceRect, destRect, {0.0f, 0.0f}, 0.0f, WHITE);
		EndMode2D();

		DrawRectangleLines(sMR.x, sMR.y, drawArea.width * camera.zoom, drawArea.height * camera.zoom, BLACK);
		EndDrawing();
	}

	UnloadRenderTexture(rtex);
	CloseWindow(); // De-initialization
	return 0;
}
#pragma clang diagnostic pop