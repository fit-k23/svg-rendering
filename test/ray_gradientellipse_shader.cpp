#include "../lib/raylib/raylib.h"
#include "../lib/raylib/raymath.h"
#include "../lib/raylib/rlgl.h"

const char *gradientEllipseShaderCode = R"(
// gradient.fs
#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform vec2 rectPos;       // Position of the rectangle
uniform vec2 rectSize;      // Size of the rectangle
uniform vec3 startColor;    // Gradient start color
uniform vec3 endColor;      // Gradient end color

uniform float u_time;

void main() {
//	float gradient = (fragTexCoord.y - rectPos.y) / rectSize.y;
//	float gradient = rectPos.y / 600;
	vec3 color = mix(startColor, endColor, abs(sin(u_time)));
	finalColor = vec4(color, 1.0);
}
)";

Vector3 GetRandomColor() {
	return (Vector3){ GetRandomValue(0, 255) / 255.0f, GetRandomValue(0, 255) / 255.0f, GetRandomValue(0, 255) / 255.0f };
}

int main() {
	// This must be called before InitWindow
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "Gradient Ellipse Example");

	Shader shader = LoadShaderFromMemory(nullptr, gradientEllipseShaderCode);

	Rectangle rect = {100, 100, 100, 50};
	Vector2 rPos = {rect.x, rect.y};
	Vector2 rSize = {rect.width, rect.height};
	Vector2 resol = {screenWidth, screenHeight};
	Vector3 color1 = {1.0f, 0.0f, 0.0f};
	Vector3 color2 = {0.0f, 0.0f, 1.0f};
	// Rectangle parameters


	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		Vector2 mousePos = GetMousePosition();
		rect.x = mousePos.x;
		rect.y = mousePos.y;

//		color1 = GetRandomColor();
//		color2 = GetRandomColor();

		SetShaderValue(shader, GetShaderLocation(shader, "rectPos"), &rPos, SHADER_UNIFORM_VEC2);
		SetShaderValue(shader, GetShaderLocation(shader, "rectSize"), &rSize, SHADER_UNIFORM_VEC2);
		SetShaderValue(shader, GetShaderLocation(shader, "startColor"), &color1, SHADER_UNIFORM_VEC3);
		SetShaderValue(shader, GetShaderLocation(shader, "endColor"), &color2, SHADER_UNIFORM_VEC3);
		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginShaderMode(shader);
		DrawRectangleRec(rect, BLANK);
		EndShaderMode();
//		DrawRectangleRec(rect, BLUE);
		DrawRectangle(0, 0, 144, 12, BLUE);
		EndDrawing();
	}

	UnloadShader(shader);
	CloseWindow();

	return 0;
}