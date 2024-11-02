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
	void display();
	void computeIntersections(float yScan);
	void drawScanLineIntersections(float yScan);
	void sortIntersections();
};

void Poly::initialize() {
	vertexCount = 7; // Number of vertices
	points.resize(vertexCount + 1);

	Vector2 vertices[] = {
			{ 100.0f, 150.0f },
			{ 150.0f, 350.0f },
			{ 300.0f, 150.0f },
			{ 200.0f, 50.0f },
			{ 350.0f, 250.0f },
			{ 250.0f, 350.0f },
			{ 50.0f, 250.0f },
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

	for (int i = 0; i < vertexCount; i++) {
		x1 = points[i].x; y1 = points[i].y;
		x2 = points[i + 1].x; y2 = points[i + 1].y;

		if (y2 < y1) {
			swap(x1, x2);
			swap(y1, y2);
		}

		if (yScan <= y2 && yScan >= y1) {
			int xIntersection = (y1 == y2) ? x1 : ((x2 - x1) * (yScan - y1)) / (y2 - y1) + x1;
			if (xIntersection <= xmax && xIntersection >= xmin)
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
		WaitTime(0.002);  // Raylib function to wait/pause for 0.2 seconds

		DrawLine(intersections[i], yScan, intersections[i + 1], yScan, Color{ static_cast<unsigned char>(color), static_cast<unsigned char>(color), static_cast<unsigned char>(color), 255 });
	}
}

void Poly::display() {
	for (float yScan = ymin; yScan <= ymax; yScan += 1.0f) {
		computeIntersections(yScan);
//		TraceLog(LOG_INFO, "Pausing for 3 seconds...");
		drawScanLineIntersections(yScan);
	}
}

int main() {
	int screenWidth = 800;
	int screenHeight = 600;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Scan Fill Algorithm with Raylib");
	SetTargetFPS(60);

	Poly polygon;
	polygon.initialize();
	polygon.calcs();

	polygon.color = 0;

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		polygon.display();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}