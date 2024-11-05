#include "raylib.h"
#include <cmath>

#define MAX_VERTICES 100
#define MAX_EDGES 100

//struct EdgePoint{
//	float x, y;
//};

struct Edge{
	float ymin;    // minimum y coordinate
	float ymax;    // maximum y coordinate
	float x;       // x coordinate of intersection with current scanline
	float slope;   // inverse slope (dx/dy)
};

// Function to compare edges for sorting
int compareEdges(const Edge &a, const Edge &b) {
	return a.x - b.x;
}

#include <vector>
#include <algorithm>

void scanlineFill(Vector2* vertices, int vertexCount, Color fillColor) {
	// Find min and max y coordinates
	float ymin = vertices[0].y;
	float ymax = vertices[0].y;
	for (int i = 1; i < vertexCount; i++) {
		if (vertices[i].y < ymin) ymin = vertices[i].y;
		if (vertices[i].y > ymax) ymax = vertices[i].y;
	}

	// Create edge table
	std::vector<Edge> edges;
	int edgeCount = 0;

	for (int i = 0; i < vertexCount; i++) {
		int next = (i + 1) % vertexCount;

		// Skip horizontal edges
		if (vertices[i].y == vertices[next].y) continue;

		Edge edge{};

		edge.ymin = fminf(vertices[i].y, vertices[next].y);
		edge.ymax = fmaxf(vertices[i].y, vertices[next].y);

		// Calculate inverse slope (dx/dy)
		edge.slope = (vertices[next].x - vertices[i].x) / (vertices[next].y - vertices[i].y);

		// Set initial x position
		if (vertices[i].y < vertices[next].y)
			edge.x = vertices[i].x;
		else
			edge.x = vertices[next].x;

		edges.push_back(edge);
		edgeCount++;
	}

	// Process each scanline
	for (int y = (int) ymin; y <= (int)ymax; y++) {
		// Find active edges
		std::vector<Edge> activeEdges;
		int activeCount = 0;

		for (int i = 0; i < edgeCount; i++) {
			if (y >= edges[i].ymin && y < edges[i].ymax) {
				activeEdges.push_back(edges[i]);
				activeCount++;
			}
		}

		// Sort active edges by x coordinate
		std::sort(activeEdges.begin(), activeEdges.end(), compareEdges);

		// Fill between pairs of intersections
		for (int i = 0; i < activeCount - 1; i += 2) {
			int x1 = (int)activeEdges[i].x;
			int x2 = (int)activeEdges[i + 1].x;

			// Draw horizontal line
			DrawLine(x1, y, x2, y, fillColor);
		}

		// Update x coordinates for next scanline
		for (int i = 0; i < edgeCount; i++) {
			if (y >= edges[i].ymin && y < edges[i].ymax) {
				edges[i].x += edges[i].slope;
			}
		}
	}
}

#include "rlgl.h"
#include "raymath.h"

void DrawRectangleGradientOP(Rectangle rec, Color topLeft, Color bottomLeft, Color topRight, Color bottomRight) {
	// Static texture and rectangle used for shapes drawing (white pixel loaded by rlgl)
	static Texture2D texShapes = {1, 1, 1, 1, 7};
	static Rectangle texShapesRec = {0.0f, 0.0f, 1.0f, 1.0f};

	// Precalculate texture coordinates for efficiency
	float texWidthInv = 1.0f / texShapes.width;
	float texHeightInv = 1.0f / texShapes.height;
	float tx0 = texShapesRec.x * texWidthInv;
	float ty0 = texShapesRec.y * texHeightInv;
	float tx1 = (texShapesRec.x + texShapesRec.width) * texWidthInv;
	float ty1 = (texShapesRec.y + texShapesRec.height) * texHeightInv;

	// Set texture for shapes drawing
	rlSetTexture(texShapes.id);

	rlBegin(RL_QUADS);
	rlNormal3f(0.0f, 0.0f, 1.0f);

	// Draw the rectangle with gradient colors
	rlColor4ub(topLeft.r, topLeft.g, topLeft.b, topLeft.a);
	rlTexCoord2f(tx0, ty0);
	rlVertex2f(rec.x, rec.y);

	rlColor4ub(bottomLeft.r, bottomLeft.g, bottomLeft.b, bottomLeft.a);
	rlTexCoord2f(tx0, ty1);
	rlVertex2f(rec.x, rec.y + rec.height);

	rlColor4ub(topRight.r, topRight.g, topRight.b, topRight.a);
	rlTexCoord2f(tx1, ty1);
	rlVertex2f(rec.x + rec.width, rec.y + rec.height);

	rlColor4ub(bottomRight.r, bottomRight.g, bottomRight.b, bottomRight.a);
	rlTexCoord2f(tx1, ty0);
	rlVertex2f(rec.x + rec.width, rec.y);
	rlEnd();

	// Reset texture to default
	rlSetTexture(0);
}

void DrawEllipseGradientRadius(int centerX, int centerY, float radiusX, float radiusY, Color color1, Color color2, const int segment) {
	// Number of ellipse segments to draw (the higher, the smoother the gradient)
	for (int i = 0; i < segment; ++i) {
		// Calculate the interpolation factor
		float t = (float) i / (segment - 1);

		// Interpolate the color
		Color color = {
				(unsigned char)(color1.r * (1.0f - t) + color2.r * t),
				(unsigned char)(color1.g * (1.0f - t) + color2.g * t),
				(unsigned char)(color1.b * (1.0f - t) + color2.b * t),
				(unsigned char)(color1.a * (1.0f - t) + color2.a * t)
		};

		// Draw the ellipse segment
		DrawEllipse(centerX, centerY, radiusX * (1.0f - t), radiusY * (1.0f - t), color);
	}
}

int main() {
	// Initialize window
	const int screenWidth = 1000;
	const int screenHeight = 1000;
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
	InitWindow(screenWidth, screenHeight, "Polygon Scanline Fill");

	// Define example polygon vertices
	Vector2 vertices[] = {
	{775, 183},
	{859, 1000},
	{170, 60},
	{ 911, 407 },
	{ 520, 134 },
	{ 392, 408 },
	{37, 454},
	};
	int vertexCount = sizeof(vertices) / sizeof(vertices[0]);

	SetTargetFPS(60);

	Camera2D camera;
	camera.target = {screenWidth / 2.0f, screenHeight / 2.0f};
	camera.offset = camera.target;
	camera.zoom = 1.0f;
	camera.rotation = 0.0f;

	RenderTexture rt = LoadRenderTexture(screenWidth, screenHeight);

	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_W)) camera.rotation += .1f;
		if (IsKeyDown(KEY_S)) camera.rotation -= .1f;
		if (IsKeyDown(KEY_A)) camera.zoom -= .1f;
		if (IsKeyDown(KEY_D)) camera.zoom += .1f;
		if (camera.zoom <= 0.1f) camera.zoom = 0.01;

//		BeginTextureMode(rt);
//		ClearBackground(BLANK);
//		EndTextureMode();
		BeginDrawing();
		ClearBackground(RAYWHITE);

		BeginMode2D(camera);

		scanlineFill(vertices, vertexCount, BLUE);
//		DrawTextureEx(rt.texture, {0, 0}, 0.0f, 1.0, WHITE);
		for (int i = 0; i < vertexCount; i++) {
			DrawLineEx(vertices[i], vertices[(i + 1) % vertexCount],3, BLACK);
		}

		EndMode2D();


		EndDrawing();
	}

	CloseWindow();
	return 0;
}