#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include "external/glad.h"

#include <vector>

// Simple structure for storing triangles (each triangle has 3 points)
struct Triangle {
	Vector2 p1, p2, p3;
};

// Triangulation function placeholder (implement or use a library here)
std::vector<Triangle> TriangulatePolygon(Vector2 *points, int pointCount) {
	std::vector<Triangle> triangles;

	// Placeholder triangulation algorithm (replace with actual logic or library)
	// Here, we will simply connect every third point as a naive example
	for (int i = 1; i < pointCount - 1; i++) {
		triangles.push_back({points[0], points[i], points[i + 1]});
	}

	return triangles;
}

#include "raylib.h"
#include "rlgl.h"
#include <GL/gl.h>
#include <vector>

// Draw complex polygon using Alternate FillMode with triangulation
void DrawPolygonAlternate(Vector2 *points, int pointCount, Color color) {
	auto triangles = TriangulatePolygon(points, pointCount); // Triangulate first

	rlPushMatrix();
	glEnable(GL_STENCIL_TEST);                   // Enable stencil testing
	glStencilFunc(GL_ALWAYS, 0, 1);              // Always pass stencil test
	glStencilOp(GL_KEEP, GL_INVERT, GL_INVERT);  // Invert stencil value

	rlBegin(RL_TRIANGLES);
	for (const auto &triangle : triangles) {
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f(triangle.p1.x, triangle.p1.y);
		rlVertex2f(triangle.p2.x, triangle.p2.y);
		rlVertex2f(triangle.p3.x, triangle.p3.y);
	}
	rlEnd();

	glStencilFunc(GL_EQUAL, 1, 1);               // Draw only where stencil value is odd (odd-even rule)
	rlBegin(RL_TRIANGLES);
	for (const auto &triangle : triangles) {
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f(triangle.p1.x, triangle.p1.y);
		rlVertex2f(triangle.p2.x, triangle.p2.y);
		rlVertex2f(triangle.p3.x, triangle.p3.y);
	}
	rlEnd();

	glStencilFunc(GL_ALWAYS, 0, 1);              // Reset stencil settings
	glDisable(GL_STENCIL_TEST);                  // Disable stencil testing
	rlPopMatrix();
}

// Draw complex polygon using Winding FillMode with triangulation
void DrawPolygonWinding(Vector2 *points, int pointCount, Color color) {
	auto triangles = TriangulatePolygon(points, pointCount); // Triangulate first

	rlPushMatrix();
	glEnable(GL_STENCIL_TEST);                  // Enable stencil testing
	glStencilFunc(GL_ALWAYS, 0, 1);             // Always pass stencil test
	glStencilOp(GL_KEEP, GL_INCR_WRAP, GL_DECR_WRAP); // Increment for front-facing, decrement for back-facing

	rlBegin(RL_TRIANGLES);
	for (const auto &triangle : triangles) {
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f(triangle.p1.x, triangle.p1.y);
		rlVertex2f(triangle.p2.x, triangle.p2.y);
		rlVertex2f(triangle.p3.x, triangle.p3.y);
	}
	rlEnd();

	glStencilFunc(GL_NOTEQUAL, 0, 1);           // Draw where stencil value is non-zero
	rlBegin(RL_TRIANGLES);
	for (const auto &triangle : triangles) {
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f(triangle.p1.x, triangle.p1.y);
		rlVertex2f(triangle.p2.x, triangle.p2.y);
		rlVertex2f(triangle.p3.x, triangle.p3.y);
	}
	rlEnd();

	glStencilFunc(GL_ALWAYS, 0, 1);             // Reset stencil settings
	glDisable(GL_STENCIL_TEST);                 // Disable stencil testing
	rlPopMatrix();
}

int main() {
	InitWindow(800, 600, "Complex Polygon Fill Modes with Triangulation");

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

		// Draw using Alternate Fill Mode
//		DrawPolygonAlternate(points, pointCount, RED);

		// Draw using Winding Fill Mode
		DrawPolygonWinding(points, pointCount, BLUE);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
