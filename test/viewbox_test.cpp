#include "../lib/raylib/raylib.h"
#include "../lib/raylib/raymath.h"

int main() {
	// Initialization
	const int screenWidth = 800;
	const int screenHeight = 600;
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	//Enable MSAA 4X anti-aliasing
//	SetConfigFlags(FLAG_MSAA_4X_HINT);
	InitWindow(screenWidth, screenHeight, "raylib [core] example - scissor with camera");



	// Define the scissor area in screen space
	Rectangle scissorArea = { 100, 100, 300, 300 };

	// Initialize camera
	Camera2D camera = { 0 };
	camera.target = {screenWidth / 2.0f, screenHeight / 2.0f};
	camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	SetTargetFPS(60); // Set our game to run at 60 frames-per-second

	while (!WindowShouldClose()) { // Detect window close button or ESC key
		// Camera controls
		if (IsKeyDown(KEY_RIGHT)) camera.target.x -= 5;
		if (IsKeyDown(KEY_LEFT)) camera.target.x += 5;
		if (IsKeyDown(KEY_UP)) camera.target.y += 5;
		if (IsKeyDown(KEY_DOWN)) camera.target.y -= 5;

		camera.zoom += (GetMouseWheelMove() * 0.05f);
		if (camera.zoom > 3.0f) camera.zoom = 3.0f;
		else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

		BeginDrawing();
		ClearBackground(RAYWHITE);

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


		BeginMode2D(camera); // Begin 2D mode with camera again
		DrawRectangleLines(0, 0, screenWidth, screenHeight, RED);
		Rectangle sMR{
				(scissorArea.x - camera.target.x) * camera.zoom + camera.offset.x,
				(scissorArea.y - camera.target.y) * camera.zoom + camera.offset.y,
				(scissorArea.width) * camera.zoom,
				(scissorArea.height) * camera.zoom
		};

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			DrawCircle(0, 0, 100, ColorAlpha(YELLOW, 0.5));
			DrawCircle(150, 100, 100, ColorAlpha(BLUE, 0.5));
			DrawEllipse(250, 250, 300, 50, ColorAlpha(GREEN, 0.5));
		}

		BeginScissorMode(
			sMR.x,
			sMR.y,
			sMR.width,
			sMR.height
		);


		// Draw within the scissor area
		DrawCircle(0, 0, 100, RED);
		DrawCircle(150, 100, 100, BLUE);

		DrawEllipse(250, 250, 300, 50, GREEN);

		EndScissorMode(); // End scissor mode

		EndMode2D(); // End 2D mode with camera

		// Draw the outline of the scissor area for visualization
		DrawRectangleLines(sMR.x, sMR.y, sMR.width, sMR.height, BLACK);

		EndDrawing();
	}

	CloseWindow(); // De-initialization
	return 0;
}