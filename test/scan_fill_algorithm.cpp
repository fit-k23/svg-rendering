#include "../lib/raylib/raylib.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Point {
public:
	float x, y;
};

class Poly {
public:
	vector<Point> points;
	vector<int> intersections;
	int vertexCount;
	float xmin, ymin, xmax, ymax;
	int color;
	void initialize();
	void calcs();
	void display(float width);
	void computeIntersections(float yScan);
	void drawScanLineIntersections(float yScan);
	void sortIntersections();
};

void Poly::initialize() {
	vertexCount = 7; // Number of vertices
	points.resize(vertexCount + 1);

	Vector2 vertices[] = {
			{775, 183},
			{859, 1000},
			{170, 60},
			{ 911, 407 },
			{ 520, 134 },
			{ 392, 408 },
			{37, 454},
	};

	for (int i = 0; i < vertexCount; i++) {
		points[i].x = vertices[i].x;
		points[i].y = vertices[i].y;
	}
	points[vertexCount] = points[0]; // Close the polygon

	xmin = xmax = points[0].x;
	ymin = ymax = points[0].y;
}

void Poly::calcs() {
	for (int i = 0; i < vertexCount; i++) {
		if (xmin > points[i].x) xmin = points[i].x;
		if (xmax < points[i].x) xmax = points[i].x;
		if (ymin > points[i].y) ymin = points[i].y;
		if (ymax < points[i].y) ymax = points[i].y;
	}
}

void Poly::computeIntersections(float yScan) {
	float x1, x2, y1, y2;
	intersections.clear();

	for (int i = 0; i < vertexCount; ++i) {
		x1 = points[i].x;
		y1 = points[i].y;
		x2 = points[(i + 1) % vertexCount].x;
		y2 = points[(i + 1) % vertexCount].y;

		if (y2 < y1) {
			swap(x1, x2);
			swap(y1, y2);
		}

		if (yScan <= y2 && yScan >= y1) {
			int xIntersection = (y1 == y2) ? x1 : ((x2 - x1) * (yScan - y1)) / (y2 - y1) + x1;
			if (xIntersection >= xmin && xIntersection <= xmax) // && xIntersection != x2)
				intersections.push_back(xIntersection);
		}
	}
}

void Poly::sortIntersections() {
	sort(intersections.begin(), intersections.end());
}

void Poly::drawScanLineIntersections(float yScan) {
	sortIntersections();
	for (size_t i = 0; i < intersections.size(); i += 2) {
		DrawLine(intersections[i], yScan, intersections[i + 1], yScan, Color{0, 0, 0, 255 });
//		DrawLine(intersections[i], yScan, intersections[i + 1], yScan, Color{GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 });
	}
}

void Poly::display(float width) {
	for (float yScan = ymin; yScan <= ymax; yScan += width) {
		computeIntersections(yScan);
		drawScanLineIntersections(yScan);
	}
}

int main() {
	int screenWidth = 1000;
	int screenHeight = 1000;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Scan Fill Algorithm with Raylib");
	SetTargetFPS(60);

	Poly polygon;
	polygon.initialize();
	polygon.calcs();

	polygon.color = 0;

	Camera2D camera;
	camera.target = {screenWidth / 2.0f, screenHeight / 2.0f};
	camera.offset = camera.target;
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_W)) camera.rotation += 0.5;
		if (IsKeyDown(KEY_S)) camera.rotation -= 0.5;
		if (IsKeyDown(KEY_A)) camera.zoom -= 0.05;
		if (IsKeyDown(KEY_D)) camera.zoom += 0.05;
		if (camera.zoom <= 0.0f) camera.zoom = 0.01f;
		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(camera);
		polygon.display(1.0f / camera.zoom);
		EndMode2D();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}