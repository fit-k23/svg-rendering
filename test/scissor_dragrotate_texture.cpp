#include "../lib/raylib/raylib.h"
#include "../lib/raylib/raymath.h"
#include "../lib/raylib/rlgl.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib - Scissor Test Example");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

	RenderTexture rtex = LoadRenderTexture(screenWidth, screenHeight);

    int scissorX = 100;
    int scissorY = 100;
    int scissorWidth = 400;
    int scissorHeight = 300;

    float rotation = 0.0f;
    Camera2D camera = { 0 };
    camera.target = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Vector2 texturePosition = { 50, 50 };
    bool dragging = false;
    Vector2 previousMousePosition = { 0, 0 };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update rotation
        if (IsKeyDown(KEY_W)) rotation -= 5.0f;
        if (IsKeyDown(KEY_S)) rotation += 5.0f;

        // Update camera position with arrow keys
        if (IsKeyDown(KEY_UP)) camera.target.y -= 10;
        if (IsKeyDown(KEY_DOWN)) camera.target.y += 10;
        if (IsKeyDown(KEY_LEFT)) camera.target.x -= 10;
        if (IsKeyDown(KEY_RIGHT)) camera.target.x += 10;

        // Update zoom with scroll wheel
        camera.zoom += GetMouseWheelMove() * 0.1f;
        if (camera.zoom < 0.1f) camera.zoom = 0.1f;

        // Dragging with mouse
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
		DrawEllipse(100, 100, 300, 50, ColorAlpha(BLUE, 0.9));
		EndTextureMode();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        DrawTexturePro(rtex.texture,
                       (Rectangle){ scissorX, scissorY, rtex.texture.width, rtex.texture.height },
                       (Rectangle){ texturePosition.x, texturePosition.y, rtex.texture.width, rtex.texture.height },
                       (Vector2){ rtex.texture.width / 2.0f, rtex.texture.height / 2.0f },
                       rotation, 
                       WHITE);
		DrawCircle(0, 0, 133, YELLOW);

		DrawRectangleLines(0, 0, scissorWidth, scissorHeight, RED);
		EndMode2D();



        EndDrawing();
    }
	UnloadRenderTexture(rtex);
    CloseWindow();

    return 0;
}