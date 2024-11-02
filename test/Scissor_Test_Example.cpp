#include "../lib/raylib/raylib.h"

int main() {
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "raylib - Scissor Test Example");
	SetWindowState(FLAG_WINDOW_RESIZABLE);

	Texture2D texture = LoadTexture("asset/hcmus.png");

	int scissorX = 100;
	int scissorY = 100;
	int scissorWidth = 400;
	int scissorHeight = 300;

	float rotation = 0.0f;
	float zoom = 1.0f;
	Vector2 position = {50, 50};
	Vector2 origin = {0, 0};
	bool dragging = false;
	Vector2 previousMousePosition = {0, 0};

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		// Update rotation
		if (IsKeyDown(KEY_W)) rotation -= 5.0f;
		if (IsKeyDown(KEY_S)) rotation += 5.0f;

		// Update position with arrow keys
		if (IsKeyDown(KEY_UP)) position.y -= 10;
		if (IsKeyDown(KEY_DOWN)) position.y += 10;
		if (IsKeyDown(KEY_LEFT)) position.x -= 10;
		if (IsKeyDown(KEY_RIGHT)) position.x += 10;

		// Update zoom with scroll wheel
		zoom += GetMouseWheelMove() * 0.1f;
		if (zoom < 0.1f) zoom = 0.1f;

		// Dragging with mouse
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			dragging = true;
			previousMousePosition = GetMousePosition();
		}
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) dragging = false;

		if (dragging) {
			Vector2 currentMousePosition = GetMousePosition();
			position.x += (currentMousePosition.x - previousMousePosition.x);
			position.y += (currentMousePosition.y - previousMousePosition.y);
			previousMousePosition = currentMousePosition;
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		BeginScissorMode(scissorX, scissorY, scissorWidth, scissorHeight);

		// Draw the texture with rotation and zoom
		DrawTexturePro(texture,
					   (Rectangle){ 0, 0, texture.width, texture.height },
					   (Rectangle){ position.x, position.y, texture.width * zoom, texture.height * zoom },
					   origin,
					   rotation,
					   WHITE);

		EndScissorMode();

		DrawRectangleLines(scissorX, scissorY, scissorWidth, scissorHeight, RED);


		EndDrawing();
	}

	UnloadTexture(texture);
	CloseWindow();

	return 0;
}