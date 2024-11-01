#include "../lib/raylib/raylib.h"
#include "../lib/raylib/raymath.h"
#include "../lib/raylib/rlgl.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib - Scissor Test Example");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    Camera2D camera = { 0 };
    camera.target = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    bool dragging = false;
    Vector2 previousMousePosition = { 0, 0 };

	RenderTexture rtex = LoadRenderTexture(screenWidth, screenHeight);
	Texture texture = rtex.texture;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update rotation
        if (IsKeyDown(KEY_W)) camera.rotation += 5.0f;
        if (IsKeyDown(KEY_S)) camera.rotation -= 5.0f;

        // Update camera position with arrow keys
        if (IsKeyDown(KEY_UP)) camera.target.y -= 10;
        if (IsKeyDown(KEY_DOWN)) camera.target.y += 10;
        if (IsKeyDown(KEY_LEFT)) camera.target.x += 10;
        if (IsKeyDown(KEY_RIGHT)) camera.target.x -= 10;

		float wheel = GetMouseWheelMove();
		if (wheel != 0) {
			camera.zoom += (GetMouseWheelMove() * 0.05f);
			if (camera.zoom > 3.0f) camera.zoom = 3.0f;
			else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

			texture.width *= camera.zoom;
			texture.height *= camera.zoom;
		}

		if (IsKeyPressed(KEY_R)) {
			camera.target = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
			camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
			camera.rotation = 0.0f;
			camera.zoom = 1.0f;
			texture.width = screenWidth;
			texture.height = screenHeight;
		}

        // Mouse dragging
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            dragging = true;
            previousMousePosition = GetMousePosition();
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) dragging = false;

        if (dragging) {
            Vector2 currentMousePosition = GetMousePosition();
            Vector2 delta = { (currentMousePosition.x - previousMousePosition.x) / camera.zoom,
                              (currentMousePosition.y - previousMousePosition.y) / camera.zoom };
            camera.target = Vector2Subtract(camera.target, delta);
            previousMousePosition = currentMousePosition;
        }

		BeginTextureMode(rtex);
		ClearBackground(BLANK);
		DrawEllipse(100 * camera.zoom, 100 * camera.zoom, 300 * camera.zoom, 50 * camera.zoom, ColorAlpha(BLUE, GetRandomValue(0, 100) / 100.0f));
		EndTextureMode();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        DrawTexture(texture, screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2, WHITE);
		DrawRectangleLines(screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2, texture.width, texture.height, RED);
		DrawRectangleLines(screenWidth / 2 - texture.width / 2 - 1, screenHeight / 2 - texture.height / 2 - 1, texture.width + 1, texture.height + 1, RED);
		EndMode2D();
        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();

    return 0;
}