/*******************************************************************************************
*
* STENCIL Example for raylib
* originally taken from https://github.com/raysan5/raylib/discussions/2964
*
********************************************************************************************/
#include "raylib.h"
#include "rlgl.h"
#include "external/glad.h"

void BeginStencilMode()
{
	rlDrawRenderBatchActive();
	glEnable(GL_STENCIL_TEST);
}

void ClearStencilMask()
{
    glClearStencil(0);
    glClear( GL_STENCIL_BUFFER_BIT );
}

void BeginStencilMask()
{
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

void EndStencilMask()
{
	rlDrawRenderBatchActive();	
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

void EndStencilMode()
{
	rlDrawRenderBatchActive();
	glDisable(GL_STENCIL_TEST);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    // -------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 550;

    InitWindow(800, 600, "raylib example");

    Image noise=GenImagePerlinNoise(256,256,0,0,100);
    Texture2D tex_noise=LoadTextureFromImage(noise);

    SetTargetFPS(10);
    while (!WindowShouldClose())
        {
        BeginDrawing();
        ClearBackground(SKYBLUE);    

        DrawRectanglePro((Rectangle){250,100,60,10},(Vector2){0,0},-40,BLACK);
        DrawRectanglePro((Rectangle){250,100,60,10},(Vector2){0,0},-130,BLACK);
        DrawRectangle(100,100,300,200,WHITE);
        DrawRectangleRounded((Rectangle){110,110,260,180},0.5,10,BLACK);
        for (int i=0;i<100;i+=30)
            DrawCircle(385,130+i,10,ORANGE);

        if (IsKeyDown(KEY_SPACE))
        {
        ClearStencilMask();
        BeginStencilMode();      
            BeginStencilMask();  
            /// Draw the actual stencil
            /// tv screen
            DrawRectangleRounded((Rectangle){110,110,260,180},0.5,10,BLACK);

            EndStencilMask();

        /// Draw noise texture using stencil mask
        DrawTexturePro(tex_noise, 
            (Rectangle){0,0,256,256},(Rectangle){200+GetRandomValue(0,20),250,400,400},
            (Vector2){200,200},0,WHITE);

            EndStencilMode();
            }

        /// Draw without the stencil mask
        DrawRectangle(0,300,screenWidth,20,GREEN);

        DrawText("Hold SPACE key to draw using the stencil mask.",10,10,20,BLACK);
        DrawText("Hold SPACE key to draw using the stencil mask.",11,9,20,WHITE);

        EndDrawing();    
        }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}

