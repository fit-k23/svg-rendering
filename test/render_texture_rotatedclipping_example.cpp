#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib - rotated clipping example without OpenGL calls");

    // Create a render texture for the original content
    RenderTexture2D target = LoadRenderTexture(512, 512);

    // Create another render texture to act as a mask
    RenderTexture2D mask = LoadRenderTexture(512, 512);

    float rotationAngle = 0.0f;

    while (!WindowShouldClose())
    {
        // Update rotation
        rotationAngle += 0.5f;

        // Draw content to the render texture
        BeginTextureMode(target);
        ClearBackground(RAYWHITE);

        DrawText("This is rendered to a texture!", 10, 10, 20, DARKGRAY);
        DrawCircle(target.texture.width / 2, target.texture.height / 2, 50, RED);
        DrawRectangle(target.texture.width / 2 - 50, target.texture.height / 2 - 150, 100, 50, BLUE);

        EndTextureMode();

        // Draw a rotated rectangular mask
        BeginTextureMode(mask);
        ClearBackground(BLANK); // Transparent background
        
        Vector2 maskCenter = {mask.texture.width / 2, mask.texture.height / 2};
        Rectangle maskRect = {0, 0, (float)mask.texture.width, (float)mask.texture.height};
        Vector2 origin = {maskRect.width / 2, maskRect.height / 2};
        
        DrawRectanglePro(maskRect, origin, rotationAngle, WHITE);
        
        EndTextureMode();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw and use the mask RenderTexture
        DrawTexture(target.texture, (screenWidth - target.texture.width) / 2, (screenHeight - target.texture.height) / 2, WHITE);
        DrawTexturePro(mask.texture, maskRect, 
                       (Rectangle){ (screenWidth - mask.texture.width) / 2, (screenHeight - mask.texture.height) / 2, mask.texture.width, mask.texture.height },
                       origin, rotationAngle, WHITE);

        EndDrawing();
    }

    // De-Initialization
    UnloadRenderTexture(target); // Unload render texture
    UnloadRenderTexture(mask);   // Unload mask texture
    CloseWindow();               // Close window and OpenGL context

    return 0;
}