#include "../lib/raylib/raylib.h"

int main(void)
{
	// Initialization
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [textures] example - texture scaling");

	// Set window state to resizable and enable MSAA
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowState(FLAG_MSAA_4X_HINT);

	RenderTexture2D renderTexture;

	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Begin drawing to the render texture
		renderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
		BeginTextureMode(renderTexture);
		ClearBackground(RAYWHITE);


		// Draw shapes to the render texture

		DrawText("This is rendered to a texture!", 10, 10, 20, DARKGRAY);
		DrawCircle(renderTexture.texture.width / 2, renderTexture.texture.height / 2, 50, RED);
		DrawRectangle(renderTexture.texture.width / 2 - 50, renderTexture.texture.height / 2 - 150, 100, 50, BLUE);

		EndTextureMode();

		// Calculate the scale based on the screen size
		float scaleWidth = (float)GetScreenWidth() / renderTexture.texture.width;
		float scaleHeight = (float)GetScreenHeight() / renderTexture.texture.height;

		// Adjust scaling to maintain aspect ratio
		float scale = (scaleWidth < scaleHeight) ? scaleWidth : scaleHeight;

		BeginDrawing();
		ClearBackground(RAYWHITE);

		// Draw the render texture scaled to the screen size and flip the Y-axis
		Rectangle sourceRect = {0.0f, 0.0f, (float)renderTexture.texture.width, -(float)renderTexture.texture.height};
		Rectangle destRect = {((float)GetScreenWidth() - renderTexture.texture.width * scale) / 2,
							  ((float)GetScreenHeight() - renderTexture.texture.height * scale) / 2,
							  renderTexture.texture.width * scale,
							  renderTexture.texture.height * scale};
		Vector2 origin = {0.0f, 0.0f};

		DrawTexturePro(renderTexture.texture, sourceRect, destRect, origin, 0.0f, WHITE);

		DrawCircle(renderTexture.texture.width / 2 - 150, renderTexture.texture.height / 2, 50, RED);
		DrawRectangle(renderTexture.texture.width / 2 - 200, renderTexture.texture.height / 2 - 150, 100, 50, BLUE);

		EndDrawing();
		UnloadRenderTexture(renderTexture);     // Unload render texture
	}

	CloseWindow();
	return 0;
}