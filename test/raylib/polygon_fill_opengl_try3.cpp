#include "raylib.h"
#include "rlgl.h"
#include "external/glad.h"  // Include glad for OpenGL functions
#include <vector>

// Define a triangle structure for storing the vertices of triangulated polygons
struct Triangle {
	Vector2 p1, p2, p3;
};

// TriangulatePolygon function placeholder (you can use a proper library here)
std::vector<Triangle> TriangulatePolygon(Vector2 *points, int pointCount) {
	std::vector<Triangle> triangles;

	// Simple triangulation placeholder; replace with an actual triangulation method
	for (int i = 1; i < pointCount - 1; i++) {
		triangles.push_back({points[0], points[i], points[i + 1]});
	}

	return triangles;
}

// Initialize OpenGL stencil settings for complex polygons
void InitStencilBuffer() {
	glEnable(GL_STENCIL_TEST);         // Enable the stencil test
	glClear(GL_STENCIL_BUFFER_BIT);    // Clear the stencil buffer at the start of each frame
}

// Draws a complex polygon with Alternate (odd-even) fill mode using stencil buffer
void DrawPolygonAlternate(Vector2 *points, int pointCount, Color color) {
	auto triangles = TriangulatePolygon(points, pointCount); // Triangulate the polygon first

	// Setup stencil settings for Alternate fill mode
	glStencilFunc(GL_ALWAYS, 0, 1);               // Always pass the stencil test
	glStencilOp(GL_KEEP, GL_INVERT, GL_INVERT);   // Invert the stencil buffer bit

	rlBegin(RL_TRIANGLES);
	for (const auto &triangle : triangles) {
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f(triangle.p1.x, triangle.p1.y);
		rlVertex2f(triangle.p2.x, triangle.p2.y);
		rlVertex2f(triangle.p3.x, triangle.p3.y);
	}
	rlEnd();

	// Render only areas where the stencil buffer is odd (inside the polygon)
	glStencilFunc(GL_EQUAL, 1, 1);
	rlBegin(RL_TRIANGLES);
	for (const auto &triangle : triangles) {
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f(triangle.p1.x, triangle.p1.y);
		rlVertex2f(triangle.p2.x, triangle.p2.y);
		rlVertex2f(triangle.p3.x, triangle.p3.y);
	}
	rlEnd();

	glStencilFunc(GL_ALWAYS, 0, 1); // Reset stencil settings
}

// Draws a complex polygon with Winding fill mode using stencil buffer
void DrawPolygonWinding(Vector2 *points, int pointCount, Color color) {
	auto triangles = TriangulatePolygon(points, pointCount); // Triangulate the polygon first

	// Setup stencil settings for Winding fill mode
	glStencilFunc(GL_ALWAYS, 0, 1);                 // Always pass the stencil test
	glStencilOp(GL_KEEP, GL_INCR_WRAP, GL_DECR_WRAP); // Increment/decrement stencil buffer based on winding

	rlBegin(RL_TRIANGLES);
	int i = 0;
	for (const auto &triangle : triangles) {
		rlColor4ub(color.r, color.g, (color.b + i * 23) % 256, color.a);
		rlVertex2f(triangle.p1.x, triangle.p1.y);
		rlVertex2f(triangle.p2.x, triangle.p2.y);
		rlVertex2f(triangle.p3.x, triangle.p3.y);
	}
	rlEnd();

	// Render only where the stencil buffer is non-zero (inside the winding area)
	glStencilFunc(GL_NOTEQUAL, 0, 1);
	rlBegin(RL_TRIANGLES);
	for (const auto &triangle : triangles) {
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f(triangle.p1.x, triangle.p1.y);
		rlVertex2f(triangle.p2.x, triangle.p2.y);
		rlVertex2f(triangle.p3.x, triangle.p3.y);
	}
	rlEnd();

	glStencilFunc(GL_ALWAYS, 0, 1); // Reset stencil settings
}

int main() {
	InitWindow(800, 600, "Complex Polygon Fill Modes with Stencil Buffer");

	Vector2 points[] = {
			{100.0f, 150.0f},
			{150.0f, 350.0f},
			{300.0f, 150.0f},
			{200.0f, 50.0f},
			{350.0f, 250.0f},
			{250.0f, 350.0f},
			{50.0f, 250.0f}
	};
	int pointCount = sizeof(points) / sizeof(points[0]);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		InitStencilBuffer(); // Clear and set up the stencil buffer for this frame

		if (IsKeyDown(KEY_Q)) {
			// Draw using Alternate Fill Mode
			DrawPolygonAlternate(points, pointCount, RED);
		} else {
			// Draw using Winding Fill Mode
			DrawPolygonWinding(points, pointCount, BLUE);
		}

		for (int i = 0; i < pointCount; ++i) {
			DrawLineEx(points[i], points[(i + 1) % pointCount], 2, BLACK);
		}


		EndDrawing();
	}

	CloseWindow();
	return 0;
}
