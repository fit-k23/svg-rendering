#include "../lib/raylib/raylib.h"
#include "../lib/raylib/rlgl.h"
#include "../lib/raylib/raymath.h"

// Function to draw a gradient ellipse from color1 to color2 between point1 and point2
void DrawGradientEllipse(float centerX, float centerY, float radiusX, float radiusY, Color color1, Color color2, Vector2 point1, Vector2 point2) {
	const int numSegments = 360; // More segments for a smoother ellipse

	// Calculate the total distance between the gradient points for normalization
	float totalDistance = Vector2Distance(point1, point2);

	// Ensure there's no division by zero
	if (totalDistance == 0) totalDistance = 1.0f;

	rlBegin(RL_TRIANGLES);
	for (int i = 0; i < numSegments; i++) {
		float theta1 = (float)i * 2.0f * PI / (float)numSegments;
		float theta2 = (float)(i + 1) * 2.0f * PI / (float)numSegments;

		// Calculate vertex positions on the perimeter of the ellipse
		Vector2 pointOnEllipse1 = { centerX + radiusX * cosf(theta1), centerY + radiusY * sinf(theta1) };
		Vector2 pointOnEllipse2 = { centerX + radiusX * cosf(theta2), centerY + radiusY * sinf(theta2) };

		// Normalize distances from the gradient points
		float t1 = Vector2Distance(pointOnEllipse1, point1) / totalDistance;
		float t2 = Vector2Distance(pointOnEllipse2, point1) / totalDistance;

		t1 = Clamp(t1, 0.0f, 1.0f);
		t2 = Clamp(t2, 0.0f, 1.0f);

		// Interpolate colors based on normalized distances
		Color interpolatedColor1 = {
				(unsigned char)(color1.r * (1.0f - t1) + color2.r * t1),
				(unsigned char)(color1.g * (1.0f - t1) + color2.g * t1),
				(unsigned char)(color1.b * (1.0f - t1) + color2.b * t1),
				(unsigned char)(color1.a * (1.0f - t1) + color2.a * t1)
		};

		Color interpolatedColor2 = {
				(unsigned char)(color1.r * (1.0f - t2) + color2.r * t2),
				(unsigned char)(color1.g * (1.0f - t2) + color2.g * t2),
				(unsigned char)(color1.b * (1.0f - t2) + color2.b * t2),
				(unsigned char)(color1.a * (1.0f - t2) + color2.a * t2)
		};

		// Draw the triangles forming the ellipse segments
		rlColor4ub(interpolatedColor1.r, interpolatedColor1.g, interpolatedColor1.b, interpolatedColor1.a);
		rlVertex2f(centerX, centerY);
		rlVertex2f(pointOnEllipse1.x, pointOnEllipse1.y);

		rlColor4ub(interpolatedColor2.r, interpolatedColor2.g, interpolatedColor2.b, interpolatedColor2.a);
		rlVertex2f(pointOnEllipse2.x, pointOnEllipse2.y);
	}
	rlEnd();
}

int main(void) {
	const int screenWidth = 800;
	const int screenHeight = 600;

	SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
	InitWindow(screenWidth, screenHeight, "raylib [shapes] example - gradient ellipse with vector points");

	Vector2 gradientPoint1 = {200, 200};
	Vector2 gradientPoint2 = {600, 400};

	Color gradientColor1 = RED;
	Color gradientColor2 = BLUE;

	SetTargetFPS(60); // Set our game to run at 60 frames-per-second

	// Main game loop
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		// Update

		// Draw
		BeginDrawing();

		ClearBackground(RAYWHITE);

		// Draw the gradient ellipse
		DrawGradientEllipse(screenWidth / 2, screenHeight / 2, 200, 100, gradientColor1, gradientColor2, gradientPoint1, gradientPoint2);

		// Draw circles to visualize gradient points
		DrawCircleV(gradientPoint1, 5, gradientColor1);
		DrawCircleV(gradientPoint2, 5, gradientColor2);

		// Debug points on the ellipse to ensure vertices are calculated correctly
		for (int i = 0; i <= 360; i += 30) { // Draw some points along the ellipse
			float theta = (float)i * PI / 180.0f;
			Vector2 pointOnEllipse = { screenWidth / 2 + 200 * cosf(theta), screenHeight / 2 + 100 * sinf(theta) };
			DrawCircleV(pointOnEllipse, 3, GREEN);
		}

		EndDrawing();
	}

	// De-Initialization
	CloseWindow(); // Close window and OpenGL context

	return 0;
}