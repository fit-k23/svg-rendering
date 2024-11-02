#include "../../lib/raylib/raylib.h"
#include "../../lib/raylib/raymath.h"
#include "../../lib/raylib/rlgl.h"

#ifndef SMOOTH_CIRCLE_ERROR_RATE
#define SMOOTH_CIRCLE_ERROR_RATE 0.5f
#endif

void DrawRectangleRoundedLinesEx2(Rectangle rec, Vector2 roundness, int segments, float lineThick, Color color) {
	if (lineThick < 0) lineThick = 0;

	// Not a rounded rectangle
	if (roundness.x <= 0.0f && roundness.y <= 0.0f) {
		DrawRectangleLinesEx((Rectangle){rec.x - lineThick, rec.y - lineThick, rec.width + 2 * lineThick, rec.height + 2 * lineThick}, lineThick, color);
		return;
	}

	// Clamp roundness values to 1.0f maximum
	if (roundness.x > 1.0f) roundness.x = 1.0f;
	if (roundness.y > 1.0f) roundness.y = 1.0f;

	// Calculate corner radius
	float radiusX = (rec.width * roundness.x) / 2;
	float radiusY = (rec.height * roundness.y) / 2;

	// Calculate number of segments to use for the corners
	if (segments < 4) {
		// Calculate the maximum angle between segments based on the error rate (usually 0.5f)
		float th = acosf(2 * powf(1 - SMOOTH_CIRCLE_ERROR_RATE / fminf(radiusX, radiusY), 2) - 1);
		segments = (int)(ceilf(2 * PI / th) / 2.0f);
		if (segments <= 0) segments = 4;
	}

	float stepLength = 90.0f / (float)segments;
	const float outerRadiusX = radiusX + lineThick, outerRadiusY = radiusY + lineThick;
	const float innerRadiusX = radiusX, innerRadiusY = radiusY;

	// Define the points and centers for the rounded corners
	const Vector2 point[16] = {
			{rec.x + innerRadiusX, rec.y - lineThick}, {rec.x + rec.width - innerRadiusX, rec.y - lineThick},
			{rec.x + rec.width + lineThick, rec.y + innerRadiusY}, {rec.x + rec.width + lineThick, rec.y + rec.height - innerRadiusY},
			{rec.x + rec.width - innerRadiusX, rec.y + rec.height + lineThick}, {rec.x + innerRadiusX, rec.y + rec.height + lineThick},
			{rec.x - lineThick, rec.y + rec.height - innerRadiusY}, {rec.x - lineThick, rec.y + innerRadiusY},
			{rec.x + innerRadiusX, rec.y}, {rec.x + rec.width - innerRadiusX, rec.y},
			{rec.x + rec.width, rec.y + innerRadiusY}, {rec.x + rec.width, rec.y + rec.height - innerRadiusY},
			{rec.x + rec.width - innerRadiusX, rec.y + rec.height}, {rec.x + innerRadiusX, rec.y + rec.height},
			{rec.x, rec.y + rec.height - innerRadiusY}, {rec.x, rec.y + innerRadiusY}
	};

	const Vector2 centers[4] = {
			{rec.x + innerRadiusX, rec.y + innerRadiusY}, {rec.x + rec.width - innerRadiusX, rec.y + innerRadiusY},
			{rec.x + rec.width - innerRadiusX, rec.y + rec.height - innerRadiusY}, {rec.x + innerRadiusX, rec.y + rec.height - innerRadiusY}
	};

	const float angles[4] = {180.0f, 270.0f, 0.0f, 90.0f};

	if (lineThick > 1) {
#if defined(SUPPORT_QUADS_DRAW_MODE)
		rlSetTexture(GetShapesTexture().id);
        Rectangle shapeRect = GetShapesTextureRectangle();
        rlBegin(RL_QUADS);

        for (int k = 0; k < 4; ++k)
        {
            float angle = angles[k];
            const Vector2 center = centers[k];
            for (int i = 0; i < segments; i++)
            {
                rlColor4ub(color.r, color.g, color.b, color.a);

                rlTexCoord2f(shapeRect.x / texShapes.width, shapeRect.y / texShapes.height);
                rlVertex2f(center.x + cosf(DEG2RAD * angle) * innerRadiusX, center.y + sinf(DEG2RAD * angle) * innerRadiusY);

                rlTexCoord2f((shapeRect.x + shapeRect.width) / texShapes.width, shapeRect.y / texShapes.height);
                rlVertex2f(center.x + cosf(DEG2RAD * (angle + stepLength)) * innerRadiusX, center.y + sinf(DEG2RAD * (angle + stepLength)) * innerRadiusY);

                rlTexCoord2f((shapeRect.x + shapeRect.width) / texShapes.width, (shapeRect.y + shapeRect.height) / texShapes.height);
                rlVertex2f(center.x + cosf(DEG2RAD * (angle + stepLength)) * outerRadiusX, center.y + sinf(DEG2RAD * (angle + stepLength)) * outerRadiusY);

                rlTexCoord2f(shapeRect.x / texShapes.width, (shapeRect.y + shapeRect.height) / texShapes.height);
                rlVertex2f(center.x + cosf(DEG2RAD * angle) * outerRadiusX, center.y + sinf(DEG2RAD * angle) * outerRadiusY);

                angle += stepLength;
            }
        }
        rlEnd();
        rlSetTexture(0);
#else
		rlBegin(RL_TRIANGLES);

		// Draw all of the 4 corners first: Upper Left Corner, Upper Right Corner, Lower Right Corner, Lower Left Corner
		for (int k = 0; k < 4; ++k) // Hope the compiler is smart enough to unroll this loop
		{
			float angle = angles[k];
			const Vector2 center = centers[k];

			for (int i = 0; i < segments; i++) {
				rlColor4ub(color.r, color.g, color.b, color.a);

				rlVertex2f(center.x + cosf(DEG2RAD*angle)*innerRadiusX, center.y + sinf(DEG2RAD*angle)*innerRadiusY);
				rlVertex2f(center.x + cosf(DEG2RAD*(angle + stepLength))*innerRadiusX, center.y + sinf(DEG2RAD*(angle + stepLength))*innerRadiusY);
				rlVertex2f(center.x + cosf(DEG2RAD*angle)*outerRadiusX, center.y + sinf(DEG2RAD*angle)*outerRadiusY);

				rlVertex2f(center.x + cosf(DEG2RAD*(angle + stepLength))*innerRadiusX, center.y + sinf(DEG2RAD*(angle + stepLength))*innerRadiusY);
				rlVertex2f(center.x + cosf(DEG2RAD*(angle + stepLength))*outerRadiusX, center.y + sinf(DEG2RAD*(angle + stepLength))*outerRadiusY);
				rlVertex2f(center.x + cosf(DEG2RAD*angle)*outerRadiusX, center.y + sinf(DEG2RAD*angle)*outerRadiusY);

				angle += stepLength;
			}
		}

		// Upper rectangle
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f(point[0].x, point[0].y);
		rlVertex2f(point[8].x, point[8].y);
		rlVertex2f(point[9].x, point[9].y);
		rlVertex2f(point[1].x, point[1].y);
		rlVertex2f(point[0].x, point[0].y);
		rlVertex2f(point[9].x, point[9].y);

		// Right rectangle
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f(point[10].x, point[10].y);
		rlVertex2f(point[11].x, point[11].y);
		rlVertex2f(point[3].x, point[3].y);
		rlVertex2f(point[2].x, point[2].y);
		rlVertex2f(point[10].x, point[10].y);
		rlVertex2f(point[3].x, point[3].y);

		// Lower rectangle
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f(point[13].x, point[13].y);
		rlVertex2f(point[5].x, point[5].y);
		rlVertex2f(point[4].x, point[4].y);
		rlVertex2f(point[12].x, point[12].y);
		rlVertex2f(point[13].x, point[13].y);
		rlVertex2f(point[4].x, point[4].y);

		// Left rectangle
		rlColor4ub(color.r, color.g, color.b, color.a);
		rlVertex2f(point[7].x, point[7].y);
		rlVertex2f(point[6].x, point[6].y);
		rlVertex2f(point[14].x, point[14].y);
		rlVertex2f(point[15].x, point[15].y);
		rlVertex2f(point[7].x, point[7].y);
		rlVertex2f(point[14].x, point[14].y);
		rlEnd();
#endif
	}
	else
	{
		// Use LINES to draw the outline
		rlBegin(RL_LINES);
		for (int k = 0; k < 4; ++k)
		{
			float angle = angles[k];
			const Vector2 center = centers[k];
			for (int i = 0; i < segments; i++)
			{
				rlColor4ub(color.r, color.g, color.b, color.a);
				rlVertex2f(center.x + cosf(DEG2RAD * angle) * outerRadiusX, center.y + sinf(DEG2RAD * angle) * outerRadiusY);
				rlVertex2f(center.x + cosf(DEG2RAD * (angle + stepLength)) * outerRadiusX, center.y + sinf(DEG2RAD * (angle + stepLength)) * outerRadiusY);
				angle += stepLength;
			}
		}
		for (int i = 0; i < 8; i += 2)
		{
			rlColor4ub(color.r, color.g, color.b, color.a);
			rlVertex2f(point[i].x, point[i].y);
			rlVertex2f(point[i + 1].x, point[i + 1].y);
		}
		rlEnd();
	}
}

//void DrawRectangleRounded2(Rectangle rec, Vector2 roundness, int segments, Color color) {
//	// Not a rounded rectangle
//	if (roundness.x <= 0.0f || roundness.y <= 0.0f || (rec.width < 1) || (rec.height < 1)) {
//		DrawRectangleRec(rec, color);
//		return;
//	}
//
//	if (roundness.x >= 1.0f) roundness.x = 1.0f;
//	if (roundness.y >= 1.0f) roundness.y = 1.0f;
//
//	float radiusX = (rec.width > rec.height) ? (rec.height * roundness.y) / 2 : (rec.width * roundness.x) / 2;
//	float radiusY = (rec.height > rec.width) ? (rec.width * roundness.x) / 2 : (rec.height * roundness.y) / 2;
//	if (radiusX <= 0.0f || radiusY <= 0.0f) return;
//
//	// Calculate number of segments to use for the corners
//	if (segments < 4) {
//		// Calculate the maximum angle between segments based on the error rate (usually 0.5f)
//		float th = acosf(2 * powf(1 - SMOOTH_CIRCLE_ERROR_RATE / radius, 2) - 1);
//		segments = (int) (ceilf(2 * PI / th) / 4.0f);
//		if (segments <= 0) segments = 4;
//	}
//
//	float stepLength = 90.0f / (float) segments;
//
//	/*
//	Quick sketch to make sense of all of this,
//	there are 9 parts to draw, also mark the 12 points we'll use
//
//		  P0____________________P1
//		  /|                    |\
//		 /1|          2         |3\
//	 P7 /__|____________________|__\ P2
//	   |   |P8                P9|   |
//	   | 8 |          9         | 4 |
//	   | __|____________________|__ |
//	 P6 \  |P11              P10|  / P3
//		 \7|          6         |5/
//		  \|____________________|/
//		  P5                    P4
//	*/
//	// Coordinates of the 12 points that define the rounded rect
//	const Vector2 point[12] = {
//			{(float) rec.x + radius,               rec.y},
//			{(float) (rec.x + rec.width) - radius, rec.y},
//			{rec.x + rec.width,                    (float) rec.y + radius},     // PO, P1, P2
//			{rec.x + rec.width,                    (float) (rec.y + rec.height) - radius},
//			{(float) (rec.x + rec.width) - radius, rec.y + rec.height},           // P3, P4
//			{(float) rec.x + radius,               rec.y + rec.height},
//			{rec.x,                                (float) (rec.y + rec.height) - radius},
//			{rec.x,                                (float) rec.y + radius},    // P5, P6, P7
//			{(float) rec.x + radius,               (float) rec.y + radius},
//			{(float) (rec.x + rec.width) - radius, (float) rec.y + radius},                   // P8, P9
//			{(float) (rec.x + rec.width) - radius, (float) (rec.y + rec.height) - radius},
//			{(float) rec.x + radius,               (float) (rec.y + rec.height) - radius} // P10, P11
//	};
//
//	const Vector2 centers[4] = {point[8], point[9], point[10], point[11]};
//	const float angles[4] = {180.0f, 270.0f, 0.0f, 90.0f};
//
//#if defined(SUPPORT_QUADS_DRAW_MODE)
//	rlSetTexture(GetShapesTexture().id);
//	Rectangle shapeRect = GetShapesTextureRectangle();
//
//	rlBegin(RL_QUADS);
//		// Draw all the 4 corners: [1] Upper Left Corner, [3] Upper Right Corner, [5] Lower Right Corner, [7] Lower Left Corner
//		for (int k = 0; k < 4; ++k) // Hope the compiler is smart enough to unroll this loop
//		{
//			float angle = angles[k];
//			const Vector2 center = centers[k];
//
//			// NOTE: Every QUAD actually represents two segments
//			for (int i = 0; i < segments/2; i++)
//			{
//				rlColor4ub(color.r, color.g, color.b, color.a);
//				rlTexCoord2f(shapeRect.x/texShapes.width, shapeRect.y/texShapes.height);
//				rlVertex2f(center.x, center.y);
//
//				rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, shapeRect.y/texShapes.height);
//				rlVertex2f(center.x + cosf(DEG2RAD*(angle + stepLength*2))*radius, center.y + sinf(DEG2RAD*(angle + stepLength*2))*radius);
//
//				rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
//				rlVertex2f(center.x + cosf(DEG2RAD*(angle + stepLength))*radius, center.y + sinf(DEG2RAD*(angle + stepLength))*radius);
//
//				rlTexCoord2f(shapeRect.x/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
//				rlVertex2f(center.x + cosf(DEG2RAD*angle)*radius, center.y + sinf(DEG2RAD*angle)*radius);
//
//				angle += (stepLength*2);
//			}
//
//			// NOTE: In case number of segments is odd, we add one last piece to the cake
//			if (segments%2)
//			{
//				rlColor4ub(color.r, color.g, color.b, color.a);
//				rlTexCoord2f(shapeRect.x/texShapes.width, shapeRect.y/texShapes.height);
//				rlVertex2f(center.x, center.y);
//
//				rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
//				rlVertex2f(center.x + cosf(DEG2RAD*(angle + stepLength))*radius, center.y + sinf(DEG2RAD*(angle + stepLength))*radius);
//
//				rlTexCoord2f(shapeRect.x/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
//				rlVertex2f(center.x + cosf(DEG2RAD*angle)*radius, center.y + sinf(DEG2RAD*angle)*radius);
//
//				rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, shapeRect.y/texShapes.height);
//				rlVertex2f(center.x, center.y);
//			}
//		}
//
//		// [2] Upper Rectangle
//		rlColor4ub(color.r, color.g, color.b, color.a);
//		rlTexCoord2f(shapeRect.x/texShapes.width, shapeRect.y/texShapes.height);
//		rlVertex2f(point[0].x, point[0].y);
//		rlTexCoord2f(shapeRect.x/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
//		rlVertex2f(point[8].x, point[8].y);
//		rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
//		rlVertex2f(point[9].x, point[9].y);
//		rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, shapeRect.y/texShapes.height);
//		rlVertex2f(point[1].x, point[1].y);
//
//		// [4] Right Rectangle
//		rlColor4ub(color.r, color.g, color.b, color.a);
//		rlTexCoord2f(shapeRect.x/texShapes.width, shapeRect.y/texShapes.height);
//		rlVertex2f(point[2].x, point[2].y);
//		rlTexCoord2f(shapeRect.x/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
//		rlVertex2f(point[9].x, point[9].y);
//		rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
//		rlVertex2f(point[10].x, point[10].y);
//		rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, shapeRect.y/texShapes.height);
//		rlVertex2f(point[3].x, point[3].y);
//
//		// [6] Bottom Rectangle
//		rlColor4ub(color.r, color.g, color.b, color.a);
//		rlTexCoord2f(shapeRect.x/texShapes.width, shapeRect.y/texShapes.height);
//		rlVertex2f(point[11].x, point[11].y);
//		rlTexCoord2f(shapeRect.x/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
//		rlVertex2f(point[5].x, point[5].y);
//		rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
//		rlVertex2f(point[4].x, point[4].y);
//		rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, shapeRect.y/texShapes.height);
//		rlVertex2f(point[10].x, point[10].y);
//
//		// [8] Left Rectangle
//		rlColor4ub(color.r, color.g, color.b, color.a);
//		rlTexCoord2f(shapeRect.x/texShapes.width, shapeRect.y/texShapes.height);
//		rlVertex2f(point[7].x, point[7].y);
//		rlTexCoord2f(shapeRect.x/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
//		rlVertex2f(point[6].x, point[6].y);
//		rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
//		rlVertex2f(point[11].x, point[11].y);
//		rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, shapeRect.y/texShapes.height);
//		rlVertex2f(point[8].x, point[8].y);
//
//		// [9] Middle Rectangle
//		rlColor4ub(color.r, color.g, color.b, color.a);
//		rlTexCoord2f(shapeRect.x/texShapes.width, shapeRect.y/texShapes.height);
//		rlVertex2f(point[8].x, point[8].y);
//		rlTexCoord2f(shapeRect.x/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
//		rlVertex2f(point[11].x, point[11].y);
//		rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, (shapeRect.y + shapeRect.height)/texShapes.height);
//		rlVertex2f(point[10].x, point[10].y);
//		rlTexCoord2f((shapeRect.x + shapeRect.width)/texShapes.width, shapeRect.y/texShapes.height);
//		rlVertex2f(point[9].x, point[9].y);
//
//	rlEnd();
//	rlSetTexture(0);
//#else
//	rlBegin(RL_TRIANGLES);
//
//	// Draw all of the 4 corners: [1] Upper Left Corner, [3] Upper Right Corner, [5] Lower Right Corner, [7] Lower Left Corner
//	for (int k = 0; k < 4; ++k) { // Hope the compiler is smart enough to unroll this loop
//		float angle = angles[k];
//		const Vector2 center = centers[k];
//		for (int i = 0; i < segments; i++) {
//			rlColor4ub((color.r + i) % 256, color.g, color.b, (color.a + k * 237 - 10) % 256);
//			rlVertex2f(center.x, center.y);
//			rlVertex2f(
//			center.x + cosf(DEG2RAD * (angle + stepLength)) * radius,
//			center.y + sinf(DEG2RAD * (angle + stepLength)) * radius);
//			rlVertex2f(center.x + cosf(DEG2RAD * angle) * radius, center.y + sinf(DEG2RAD * angle) * radius);
//			angle += stepLength;
//		}
//	}
//
//	// [2] Upper Rectangle
//	rlColor4ub(color.r, color.g, color.b, color.a);
//	rlVertex2f(point[0].x, point[0].y);
//	rlVertex2f(point[8].x, point[8].y);
//	rlVertex2f(point[9].x, point[9].y);
//	rlVertex2f(point[1].x, point[1].y);
//	rlVertex2f(point[0].x, point[0].y);
//	rlVertex2f(point[9].x, point[9].y);
//
//	// [4] Right Rectangle
//	rlColor4ub(color.r, color.g, color.b, color.a);
//	rlVertex2f(point[9].x, point[9].y);
//	rlVertex2f(point[10].x, point[10].y);
//	rlVertex2f(point[3].x, point[3].y);
//	rlVertex2f(point[2].x, point[2].y);
//	rlVertex2f(point[9].x, point[9].y);
//	rlVertex2f(point[3].x, point[3].y);
//
//	// [6] Bottom Rectangle
//	rlColor4ub(color.r, color.g, color.b, color.a);
//	rlVertex2f(point[11].x, point[11].y);
//	rlVertex2f(point[5].x, point[5].y);
//	rlVertex2f(point[4].x, point[4].y);
//	rlVertex2f(point[10].x, point[10].y);
//	rlVertex2f(point[11].x, point[11].y);
//	rlVertex2f(point[4].x, point[4].y);
//
//	// [8] Left Rectangle
//	rlColor4ub(color.r, color.g, color.b, color.a);
//	rlVertex2f(point[7].x, point[7].y);
//	rlVertex2f(point[6].x, point[6].y);
//	rlVertex2f(point[11].x, point[11].y);
//	rlVertex2f(point[8].x, point[8].y);
//	rlVertex2f(point[7].x, point[7].y);
//	rlVertex2f(point[11].x, point[11].y);
//
//	// [9] Middle Rectangle
//	rlColor4ub(color.r, color.g, color.b, color.a);
//	rlVertex2f(point[8].x, point[8].y);
//	rlVertex2f(point[11].x, point[11].y);
//	rlVertex2f(point[10].x, point[10].y);
//	rlVertex2f(point[9].x, point[9].y);
//	rlVertex2f(point[8].x, point[8].y);
//	rlVertex2f(point[10].x, point[10].y);
//	rlEnd();
//#endif
//}

void DrawEllipseHQ(int centerX, int centerY, float radiusH, float radiusV, Color color, int step) {
	rlBegin(RL_TRIANGLES);
	rlColor4ub(color.r, color.g, color.b, color.a);
	for (int i = 0; i < 360; i += step) {
		rlVertex2f((float) centerX, (float) centerY);
		rlVertex2f((float) centerX + cosf(DEG2RAD * (i + step)) * radiusH,(float) centerY + sinf(DEG2RAD * (i + step)) * radiusV);
		rlVertex2f((float) centerX + cosf(DEG2RAD * i) * radiusH, (float) centerY + sinf(DEG2RAD * i) * radiusV);
	}
	rlEnd();
}

int main() {
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [shapes] example - DrawTriangleFan()");

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	RenderTexture2D rt = LoadRenderTexture(screenWidth, screenHeight);
	// Main game loop
	while (!WindowShouldClose()) {
		BeginTextureMode(rt);
		ClearBackground(BLANK);
//		DrawRectangleRounded2({100, 100, 300, 200}, 3.2, 180, BLUE);
		DrawRectangleRoundedLinesEx2({100, 100, 300, 200}, {1, 1}, 180, 5.0, BLUE);
		EndTextureMode();

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("HEllO WORLD", 150, 150, 20, BLUE);
		DrawTextureV(rt.texture, {0, 0}, ColorAlpha(WHITE, 0.7));
		EndDrawing();
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}