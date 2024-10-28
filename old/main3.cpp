#include "../lib/raylib/raylib.h"
#include "../lib/raylib/raymath.h"
#include "../lib/raylib/rlgl.h"

void DrawEllipseWithStroke(float centerX, float centerY, float radiusH, float radiusV, Color fillColor, Color strokeColor, float strokeWidth, float zoomLevel, float rotation);

void DrawEllipsePro(Vector2 center, float radiusH, float radiusV, float rotation, Color color) {
	// Draw ellipse with rotation
	int num_segments = 9999; // More segments for smoother ellipse

	Vector2 previousPoint = { center.x + radiusH * cosf(rotation * DEG2RAD), center.y + radiusV * sinf(rotation * DEG2RAD) };

	for (int i = 1; i <= num_segments; i++) {
		float angle = (float)i * 360.0f / (float)num_segments;
		Vector2 nextPoint = {
				center.x + radiusH * cosf((angle + rotation) * DEG2RAD),
				center.y + radiusV * sinf((angle + rotation) * DEG2RAD)
		};

		DrawLineV(previousPoint, nextPoint, color);
		previousPoint = nextPoint;
	}
}

void DrawEllipseHQ(int centerX, int centerY, float radiusH, float radiusV, Color color) {
	rlBegin(RL_TRIANGLES);
	int step = 1;
	for (int i = 0; i < 360; i += step) {
		rlColor4ub(color.r, (color.g + i) % 256, color.b, color.a);
		rlVertex2f((float)centerX, (float)centerY);
		rlVertex2f((float)centerX + cosf(DEG2RAD * (i + step)) *radiusH, (float)centerY + sinf(DEG2RAD * (i + step)) * radiusV);
		rlVertex2f((float)centerX + cosf(DEG2RAD * i) * radiusH, (float)centerY + sinf(DEG2RAD*i) * radiusV);
	}
	rlEnd();
}

int main() {
	// Initialization
	const int screenWidth = 800;
	const int screenHeight = 600;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	// Enable MSAA 4X anti-aliasing
	SetConfigFlags(FLAG_MSAA_4X_HINT);

	InitWindow(screenWidth, screenHeight, "raylib - Zoom, Rotate, and Drag Ellipse");

	float zoomLevel = 1.0f;
	float rotation = 0.0f;
	Vector2 ellipsePosition = { screenWidth / 2, screenHeight / 2 };
	Vector2 previousMousePosition = { 0, 0 };
	bool dragging = false;

	SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose()) { // Detect window close button or ESC key
		DrawFPS(100, 100);
		// Update
		if (IsKeyPressed(KEY_UP)) zoomLevel += 0.1f;
		if (IsKeyPressed(KEY_DOWN)) zoomLevel -= 0.1f;
		if (zoomLevel < 0.1f) zoomLevel = 0.1f;

		if (IsKeyPressed(KEY_LEFT)) rotation -= 5.0f;
		if (IsKeyPressed(KEY_RIGHT)) rotation += 5.0f;

		Vector2 mousePosition = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			dragging = true;
			previousMousePosition = mousePosition;
		}

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			dragging = false;
		}

		if (dragging) {
			Vector2 delta = Vector2Subtract(mousePosition, previousMousePosition);
			ellipsePosition = Vector2Add(ellipsePosition, delta);
			previousMousePosition = mousePosition;
		}

		// Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawEllipseWithStroke(ellipsePosition.x, ellipsePosition.y, 100, 50, SKYBLUE, DARKBLUE, 5, zoomLevel, rotation);

		EndDrawing();
	}

	CloseWindow(); // Close window and OpenGL context

	return 0;
}

void DrawEllipseWithStroke(float centerX, float centerY, float radiusH, float radiusV, Color fillColor, Color strokeColor, float strokeWidth, float zoomLevel, float rotation) {
	// Adjust radius based on zoom level
	float adjustedRadiusH = radiusH * zoomLevel;
	float adjustedRadiusV = radiusV * zoomLevel;
	float adjustedStrokeWidth = strokeWidth * zoomLevel;

	// Draw the stroke ellipse first
//	DrawEllipsePro((Vector2){centerX, centerY}, adjustedRadiusH + adjustedStrokeWidth, adjustedRadiusV + adjustedStrokeWidth, rotation, strokeColor);
	DrawEllipseHQ(centerX, centerY, adjustedRadiusH + adjustedStrokeWidth, adjustedRadiusV + adjustedStrokeWidth, strokeColor);

	// Draw the filled ellipse on top
//	DrawEllipsePro((Vector2){centerX, centerY}, adjustedRadiusH, adjustedRadiusV, rotation, fillColor);
	DrawEllipseHQ(centerX, centerY, adjustedRadiusH, adjustedRadiusV, fillColor);
}
