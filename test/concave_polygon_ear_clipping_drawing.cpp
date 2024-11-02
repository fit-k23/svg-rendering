#include "../lib/raylib/raylib.h"
#include "../lib/raylib/rlgl.h"
#include "../lib/raylib/raymath.h"

#include <iostream>

// Function to determine if a point is inside a triangle
bool IsPointInTriangle(Vector2 pt, Vector2 v1, Vector2 v2, Vector2 v3) {
    float d1 = (pt.x - v2.x) * (v1.y - v2.y) - (v1.x - v2.x) * (pt.y - v2.y);
    float d2 = (pt.x - v3.x) * (v2.y - v3.y) - (v2.x - v3.x) * (pt.y - v3.y);
    float d3 = (pt.x - v1.x) * (v3.y - v1.y) - (v3.x - v1.x) * (pt.y - v1.y);
    return (d1 >= 0) && (d2 >= 0) && (d3 >= 0);
}

// Function to determine if a triangle (v1, v2, v3) is convex
bool IsTriangleConvex(Vector2 v1, Vector2 v2, Vector2 v3) {
    float crossProduct = (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
    return crossProduct < 0; // Clockwise points for Raylib (screen coordinate system)
}

// Function to triangulate and draw a concave polygon using the Ear Clipping method
void DrawPolyPro(Vector2 center, Vector2 *points, int pointCount, Color color) {
    if (pointCount >= 3 && points != nullptr) {
        auto* vertices = new Vector2[pointCount];
        for (int i = 0; i < pointCount; i++) vertices[i] = points[i];

        int* indices = new int[pointCount];
        for (int i = 0; i < pointCount; i++) indices[i] = i;

        int vertexCount = pointCount;
        rlBegin(RL_TRIANGLES);
        rlColor4ub(color.r, color.g, color.b, color.a);

        while (vertexCount > 3) {
            bool earFound = false;

            for (int i = 0; i < vertexCount; i++) {
                int prev = (i + vertexCount - 1) % vertexCount;
                int next = (i + 1) % vertexCount;

                Vector2 v1 = vertices[indices[prev]];
                Vector2 v2 = vertices[indices[i]];
                Vector2 v3 = vertices[indices[next]];

                if (IsTriangleConvex(v1, v2, v3)) {
                    bool ear = true;
                    for (int j = 0; j < vertexCount; j++) {
                        if (j != prev && j != i && j != next) {
                            if (IsPointInTriangle(vertices[indices[j]], v1, v2, v3)) {
                                ear = false;
                                break;
                            }
                        }
                    }

                    if (ear) {
                        rlVertex2f(v1.x, v1.y);
                        rlVertex2f(v2.x, v2.y);
                        rlVertex2f(v3.x, v3.y);

                        // Remove ear vertex
                        for (int k = i; k < vertexCount - 1; k++) {
                            indices[k] = indices[k + 1];
                        }
                        vertexCount--;
                        earFound = true;
                        break;
                    }
                }
            }

            if (!earFound) {
                std::cerr << "Error: Cannot find an ear, polygon may be degenerate." << std::endl;
                break;
            }
        }

        if (vertexCount == 3) {
            Vector2 v1 = vertices[indices[0]];
            Vector2 v2 = vertices[indices[1]];
            Vector2 v3 = vertices[indices[2]];

            rlVertex2f(v1.x, v1.y);
            rlVertex2f(v2.x, v2.y);
            rlVertex2f(v3.x, v3.y);
        }

        rlEnd();
        delete[] vertices;
        delete[] indices;
    }
}

int main() {
    InitWindow(800, 600, "Draw Concave Polygon Example");
    SetTargetFPS(60);

	// Define the vertices of a concave polygon
	Vector2 vertices[] = {
			{ 100.0f, 150.0f },
			{ 200.0f, 50.0f },
			{ 300.0f, 150.0f },
			{ 350.0f, 350.0f },
			{ 250.0f, 250.0f },
			{ 150.0f, 350.0f },
			{ 50.0f, 250.0f },
	};
	int vertexCount = sizeof(vertices) / sizeof(vertices[0]);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the concave polygon
        Vector2 center = {200.0f, 200.0f}; // Arbitrary center point for demonstration
        DrawPolyPro(center, vertices, vertexCount, BLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}