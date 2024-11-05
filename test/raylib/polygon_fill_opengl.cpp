#include "raylib.h"
#include "rlgl.h"
#include "external/glad.h"

// Function to initialize stencil buffer for OpenGL drawing
void InitStencilBuffer() {
	rlDisableBackfaceCulling(); // Disable back-face culling for proper polygon filling
	glEnable(GL_STENCIL_TEST);       // Enable stencil testing
}

// Function to draw a polygon using Alternate (odd-even) fill mode
void DrawPolygonAlternate(Vector2 *points, int pointCount, Color color) {
	rlPushMatrix();
	rlBegin(RL_TRIANGLES);

	glEnable(GL_STENCIL_TEST);         // Enable stencil testing
	glStencilFunc(GL_ALWAYS, 0, 1); // Always pass stencil test
	glStencilOp(GL_KEEP, GL_INVERT, GL_INVERT); // Invert stencil value

	for (int i = 1; i < pointCount - 1; i++) {
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f(points[0].x, points[0].y);
		rlVertex2f(points[i].x, points[i].y);
		rlVertex2f(points[i + 1].x, points[i + 1].y);
	}
	rlEnd();

	glStencilFunc(GL_EQUAL, 1, 1); // Draw only where stencil value is odd (odd-even rule)
	rlBegin(RL_TRIANGLES);
	for (int i = 1; i < pointCount - 1; i++) {
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f(points[0].x, points[0].y);
		rlVertex2f(points[i].x, points[i].y);
		rlVertex2f(points[i + 1].x, points[i + 1].y);
	}
	rlEnd();

	glStencilFunc(GL_ALWAYS, 0, 1); // Reset stencil settings
	glDisable(GL_STENCIL_TEST);         // Disable stencil testing
	rlPopMatrix();
}

// Function to draw a polygon using Winding fill mode
void DrawPolygonWinding(Vector2 *points, int pointCount, Color color) {
	rlPushMatrix();
	rlBegin(RL_TRIANGLES);

	glEnable(GL_STENCIL_TEST);         // Enable stencil testing
	glStencilFunc(GL_ALWAYS, 0, 1); // Always pass stencil test
	glStencilOp(GL_KEEP, GL_INCR_WRAP, GL_DECR_WRAP); // Increment for front-facing, decrement for back-facing

	for (int i = 1; i < pointCount - 1; i++) {
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f(points[0].x, points[0].y);
		rlVertex2f(points[i].x, points[i].y);
		rlVertex2f(points[i + 1].x, points[i + 1].y);
	}
	rlEnd();

	glStencilFunc(GL_NOTEQUAL, 0, 1); // Draw where stencil value is non-zero
	rlBegin(RL_TRIANGLES);
	for (int i = 1; i < pointCount - 1; i++) {
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f(points[0].x, points[0].y);
		rlVertex2f(points[i].x, points[i].y);
		rlVertex2f(points[i + 1].x, points[i + 1].y);
	}
	rlEnd();

	glStencilFunc(GL_ALWAYS, 0, 1); // Reset stencil settings
	glDisable(GL_STENCIL_TEST);         // Disable stencil testing
	rlPopMatrix();
}

int main() {
	InitWindow(800, 600, "Alternate and Winding Fill Modes with rlgl");

	Vector2 points[] = {
	{ 100.0f, 150.0f },
	{ 150.0f, 350.0f },
	{ 300.0f, 150.0f },
	{ 200.0f, 50.0f },
	{ 350.0f, 250.0f },
	{ 250.0f, 350.0f },
	{ 50.0f, 250.0f },
	};
	int pointCount = sizeof(points) / sizeof(points[0]);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		InitStencilBuffer();

		// Draw using Alternate Fill Mode
		DrawPolygonAlternate(points, pointCount, RED);

		// Draw using Winding Fill Mode
//		DrawPolygonWinding(points, pointCount, BLUE);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
