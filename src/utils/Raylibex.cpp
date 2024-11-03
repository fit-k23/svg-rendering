#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#include "Raylibex.h"

/**
 * @brief Draw rounded rectangle [SHOULD NOT BE USED DIRECTLY]
 */
void draw_rect_roundedRLEX(float posX, float posY, float width, float height, float radiusx, float radiusy, Color color) {
	color.a = 255; // solidify

	// Draw the main rectangle
	DrawRectangle(posX + radiusx, posY + radiusy, width - 2 * radiusx, height - 2 * radiusy, color);
	// Draw the side rectangles (top, bottom, left, right)
	DrawRectangle(posX + radiusx, posY, width - 2 * radiusx, radiusy, color); // Top
	DrawRectangle(posX + radiusx, posY + height - radiusy, width - 2 * radiusx, radiusy, color); // Bottom
	DrawRectangle(posX, posY + radiusy, radiusx, height - 2 * radiusy, color); // Left
	DrawRectangle(posX + width - radiusx, posY + radiusy, radiusx, height - 2 * radiusy, color); // Right

	// Draw an ellipse, which get split into 4 parts placed at main rectangle's vertices
	rlBegin(RL_TRIANGLES);
	int cX = posX;
	int cY = posY;
	for (int i = 0; i < 360; i++) {
		if (i == 0 || i == 270) {
			cX = posX + width - radiusx;
		}
		if (i == 90 || i == 180) {
			cX = posX + radiusx;
		}
		if (i == 0 || i == 90) {
			cY = posY + height - radiusy;
		}
		if (i == 180 || i == 270) {
			cY = posY + radiusy;
		}
		rlColor4ub(color.r, color.g, color.b, 255);

		rlVertex2f((float) cX, (float) cY);
		rlVertex2f((float) cX + cosf(DEG2RAD * (i + 1)) * radiusx, (float) cY + sinf(DEG2RAD * (i + 1)) * radiusy);
		rlVertex2f((float) cX + cosf(DEG2RAD * i) * radiusx, (float) cY + sinf(DEG2RAD * i) * radiusy);
	}
	rlEnd();
}

void DrawRectangleRoundedRLEX(Rectangle rect, Vector2 radius, Color color, RenderTexture2D rt) {
	BeginTextureMode(rt);
	ClearBackground(BLANK);
	draw_rect_roundedRLEX(rect.x, rect.y, rect.width, rect.height, radius.x, radius.y, color);
	EndTextureMode();
	DrawTextureRec(rt.texture, {0, 0, (float)rt.texture.width, (float)-rt.texture.height}, {0, 0}, ColorAlpha(WHITE, (float)color.a / 255.5f));
}

void DrawRectangleRoundedStrokeRLEX(Rectangle rect, Vector2 radius, float strokeWidth, Color fillColor, Color strokeColor, RenderTexture2D rt) {
	BeginTextureMode(rt);
	ClearBackground(BLANK);
	BeginBlendMode(BLEND_SUBTRACT_COLORS); // Remove the inner part of the shape
	draw_rect_roundedRLEX(rect.x - strokeWidth, rect.y - strokeWidth, rect.width + 2 * strokeWidth, rect.height + 2 * strokeWidth, radius.x + strokeWidth, 
		radius.y + strokeWidth, strokeColor);
	draw_rect_roundedRLEX(rect.x, rect.y, rect.width, rect.height, radius.x, radius.y, strokeColor);
	EndBlendMode();
	draw_rect_roundedRLEX(rect.x, rect.y, rect.width, rect.height, radius.x, radius.y, fillColor);
	EndTextureMode();
<<<<<<< Updated upstream
	DrawTextureRec(rt.texture, {0, 0, rt.texture.width, -rt.texture.height}, {0, 0}, ColorAlpha(WHITE, strokeColor.a / 255.5f));
=======
<<<<<<< HEAD
	DrawTextureRec(rt.texture, {0, 0, (float)rt.texture.width, (float) - rt.texture.height}, {0, 0}, ColorAlpha(WHITE, strokeColor.a / 255.5f));

	BeginTextureMode(rt);
	ClearBackground(BLANK);
	BeginBlendMode(BLEND_SUBTRACT_COLORS); // Remove the inner part of the shape
	draw_rect_roundedRLEX(rect.x, rect.y, rect.width, rect.height, radius.x, radius.y, fillColor);
	EndBlendMode();
	EndTextureMode();
	DrawTextureRec(rt.texture, {0, 0, (float)rt.texture.width, (float) - rt.texture.height}, {0, 0}, ColorAlpha(WHITE, fillColor.a / 255.5f));
=======
	DrawTextureRec(rt.texture, {0, 0, rt.texture.width, -rt.texture.height}, {0, 0}, ColorAlpha(WHITE, strokeColor.a / 255.5f));
>>>>>>> c5827fd72586cae62913d9e34108d16fd4aba27a
>>>>>>> Stashed changes
}

void DrawEllipseRLEX(int centerX, int centerY, float radiusH, float radiusV, Color color, int step) {
	rlBegin(RL_TRIANGLES);
	rlColor4ub(color.r, color.g, color.b, color.a);
	for (int i = 0; i < 360; i += step) {
		rlVertex2f((float) centerX, (float) centerY);
		rlVertex2f((float) centerX + cosf(DEG2RAD * (i + step)) * radiusH, (float) centerY + sinf(DEG2RAD * (i + step)) * radiusV);
		rlVertex2f((float) centerX + cosf(DEG2RAD * i) * radiusH, (float) centerY + sinf(DEG2RAD * i) * radiusV);
	}
	rlEnd();
}

void DrawEllipseVRLEX(Vector2 position, Vector2 radius, Color color, int step) {
	DrawEllipseRLEX(position.x, position.y, radius.x, radius.y, color, step);
}

void DrawRectangleGradientHQ(Rectangle rec, Color topLeft, Color bottomLeft, Color topRight, Color bottomRight) {
	static Texture2D texShapes = {1, 1, 1, 1,7}; // Texture used on shapes drawing (white pixel loaded by rlgl)
	static Rectangle texShapesRec = {0.0f, 0.0f, 1.0f, 1.0f};   // Texture source rectangle used on shapes drawing

	rlSetTexture(texShapes.id);
	Rectangle shapeRect = texShapesRec;

	rlBegin(RL_QUADS);
	rlNormal3f(0.0f, 0.0f, 1.0f);

	// NOTE: Default raylib font character 95 is a white square
	rlColor4ub(topLeft.r, topLeft.g, topLeft.b, topLeft.a);
	rlTexCoord2f(shapeRect.x / texShapes.width, shapeRect.y / texShapes.height);
	rlVertex2f(rec.x, rec.y);

	rlColor4ub(bottomLeft.r, bottomLeft.g, bottomLeft.b, bottomLeft.a);
	rlTexCoord2f(shapeRect.x / texShapes.width, (shapeRect.y + shapeRect.height) / texShapes.height);
	rlVertex2f(rec.x, rec.y + rec.height);

	rlColor4ub(topRight.r, topRight.g, topRight.b, topRight.a);
	rlTexCoord2f(
			(shapeRect.x + shapeRect.width) / texShapes.width, (shapeRect.y + shapeRect.height) / texShapes.height);
	rlVertex2f(rec.x + rec.width, rec.y + rec.height);

	rlColor4ub(bottomRight.r, bottomRight.g, bottomRight.b, bottomRight.a);
	rlTexCoord2f((shapeRect.x + shapeRect.width) / texShapes.width, shapeRect.y / texShapes.height);
	rlVertex2f(rec.x + rec.width, rec.y);
	rlEnd();

	rlSetTexture(0);
}

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

void DrawEllipseGradientHQ(Rectangle rec, Color topLeft, Color bottomLeft, Color topRight, Color bottomRight) {
	// Static texture and rectangle used for shapes drawing (white pixel loaded by rlgl)
	static Texture2D texShapes = { 1, 1, 1, 1, 7 };
	static Rectangle texShapesRec = { 0.0f, 0.0f, 1.0f, 1.0f };

	// Precalculate texture coordinates for efficiency
	float texWidthInv = 1.0f / texShapes.width;
	float texHeightInv = 1.0f / texShapes.height;
	float tx0 = texShapesRec.x * texWidthInv;
	float ty0 = texShapesRec.y * texHeightInv;
	float tx1 = (texShapesRec.x + texShapesRec.width) * texWidthInv;
	float ty1 = (texShapesRec.y + texShapesRec.height) * texHeightInv;

	// Ellipse center and radii
	float centerX = rec.x + rec.width / 2;
	float centerY = rec.y + rec.height / 2;
	float radiusX = rec.width / 2;
	float radiusY = rec.height / 2;

	// Number of segments to approximate the ellipse
	int numSegments = 72; // More segments for a higher quality ellipse
	float angleIncrement = 2.0f * PI / numSegments;

	// Set texture for shapes drawing
	rlSetTexture(texShapes.id);

	rlBegin(RL_TRIANGLES);

	// Generate ellipse vertices and apply gradient colors
	for (int i = 0; i < numSegments; i++) {
		float theta = i * angleIncrement;
		float nextTheta = (i + 1) * angleIncrement;

		float dx = cosf(theta);
		float dy = sinf(theta);
		float nextDx = cosf(nextTheta);
		float nextDy = sinf(nextTheta);

		// Center vertex
		rlColor4ub(
				(topLeft.r + bottomLeft.r + topRight.r + bottomRight.r) / 4,
				(topLeft.g + bottomLeft.g + topRight.g + bottomRight.g) / 4,
				(topLeft.b + bottomLeft.b + topRight.b + bottomRight.b) / 4,
				(topLeft.a + bottomLeft.a + topRight.a + bottomRight.a) / 4);
		rlTexCoord2f((tx0 + tx1) / 2, (ty0 + ty1) / 2);
		rlVertex2f(centerX, centerY);

		auto interpolateColor = [&](float dx, float dy){
			float weightX = (dx + 1) / 2;
			float weightY = (dy + 1) / 2;
			Color color;
			color.r = (unsigned char)(
					topLeft.r * (1 - weightX) * (1 - weightY) +
					topRight.r * weightX * (1 - weightY) +
					bottomLeft.r * (1 - weightX) * weightY +
					bottomRight.r * weightX * weightY);
			color.g = (unsigned char)(
					topLeft.g * (1 - weightX) * (1 - weightY) +
					topRight.g * weightX * (1 - weightY) +
					bottomLeft.g * (1 - weightX) * weightY +
					bottomRight.g * weightX * weightY);
			color.b = (unsigned char)(
					topLeft.b * (1 - weightX) * (1 - weightY) +
					topRight.b * weightX * (1 - weightY) +
					bottomLeft.b * (1 - weightX) * weightY +
					bottomRight.b * weightX * weightY);
			color.a = (unsigned char)(
					topLeft.a * (1 - weightX) * (1 - weightY) +
					topRight.a * weightX * (1 - weightY) +
					bottomLeft.a * (1 - weightX) * weightY +
					bottomRight.a * weightX * weightY);
			return color;
		};

		// First edge vertex
		Color color1 = interpolateColor(dx, dy);
		rlColor4ub(color1.r, color1.g, color1.b, color1.a);
		rlTexCoord2f(tx0 + (tx1 - tx0) * (dx + 1) / 2, ty0 + (ty1 - ty0) * (dy + 1) / 2);
		rlVertex2f(centerX + dx * radiusX, centerY + dy * radiusY);

		// Second edge vertex
		Color color2 = interpolateColor(nextDx, nextDy);
		rlColor4ub(color2.r, color2.g, color2.b, color2.a);
		rlTexCoord2f(tx0 + (tx1 - tx0) * (nextDx + 1) / 2, ty0 + (ty1 - ty0) * (nextDy + 1) / 2);
		rlVertex2f(centerX + nextDx * radiusX, centerY + nextDy * radiusY);
	}
	rlEnd();

	// Reset texture to default
	rlSetTexture(0);
}

void DrawEllipseGradientHQ(float centerX, float centerY, float radiusX, float radiusY, Color topLeft, Color bottomLeft, Color topRight, Color bottomRight) {
	// Static texture and rectangle used for shapes drawing (white pixel loaded by rlgl)
	static Texture2D texShapes = { rlGetTextureIdDefault(), 1, 1, 1, RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
	static Rectangle texShapesRec = { 0.0f, 0.0f, 1.0f, 1.0f };

	// Number of segments to approximate the ellipse
	int segments = 360;
	float angleStep = 360.0f / segments;

	rlSetTexture(texShapes.id);
	rlBegin(RL_TRIANGLES);

	for (int i = 0; i < segments; i++) {
		// Calculate angle for the current segment
		float angle = DEG2RAD * (angleStep * i);
		float nextAngle = DEG2RAD * (angleStep * (i + 1));

		// Calculate positions of the current and next vertices
		float x1 = centerX + cosf(angle) * radiusX;
		float y1 = centerY + sinf(angle) * radiusY;
		float x2 = centerX + cosf(nextAngle) * radiusX;
		float y2 = centerY + sinf(nextAngle) * radiusY;

		// Interpolate colors for gradient effect
		float t1 = (cosf(angle) + 1.0f) / 2.0f;
		float u1 = (sinf(angle) + 1.0f) / 2.0f;
		float t2 = (cosf(nextAngle) + 1.0f) / 2.0f;
		float u2 = (sinf(nextAngle) + 1.0f) / 2.0f;

		// Calculate interpolated color
		Color c1 = {
				(unsigned char)(topLeft.r * (1 - t1) * (1 - u1) + topRight.r * t1  * (1 - u1) + bottomLeft.r* (1 - t1) * u1  + bottomRight.r * t1 * u1),
				(unsigned char)(topLeft.g * (1 - t1) * (1 - u1) + topRight.g * t1  * (1 - u1) + bottomLeft.g* (1 - t1) * u1  + bottomRight.g * t1 * u1),
				(unsigned char)(topLeft.b * (1 - t1) * (1 - u1) + topRight.b * t1  * (1 - u1) + bottomLeft.b* (1 - t1) * u1  + bottomRight.b * t1 * u1),
				(unsigned char)(topLeft.a * (1 - t1) * (1 - u1) + topRight.a * t1  * (1 - u1) + bottomLeft.a* (1 - t1) * u1  + bottomRight.a * t1 * u1)
		};

		Color c2 = {
				(unsigned char)(topLeft.r * (1 - t2) * (1 - u2) + topRight.r * t2  * (1 - u2) + bottomLeft.r* (1 - t2) * u2  + bottomRight.r * t2 * u2),
				(unsigned char)(topLeft.g * (1 - t2) * (1 - u2) + topRight.g * t2  * (1 - u2) + bottomLeft.g* (1 - t2) * u2  + bottomRight.g * t2 * u2),
				(unsigned char)(topLeft.b * (1 - t2) * (1 - u2) + topRight.b * t2  * (1 - u2) + bottomLeft.b* (1 - t2) * u2  + bottomRight.b * t2 * u2),
				(unsigned char)(topLeft.a * (1 - t2) * (1 - u2) + topRight.a * t2  * (1 - u2) + bottomLeft.a* (1 - t2) * u2  + bottomRight.a * t2 * u2)
		};

		// Draw the triangle for the current segment
		rlColor4ub(c1.r, c1.g, c1.b, c1.a);
		rlTexCoord2f(texShapesRec.x, texShapesRec.y);
		rlVertex2f(x1, y1);

		rlColor4ub(c2.r, c2.g, c2.b, c2.a);
		rlTexCoord2f(texShapesRec.x + texShapesRec.width, texShapesRec.y);
		rlVertex2f(x2, y2);

		rlColor4ub((topLeft.r + topRight.r + bottomLeft.r + bottomRight.r) / 4,
				   (topLeft.g + topRight.g + bottomLeft.g + bottomRight.g) / 4,
				   (topLeft.b + topRight.b + bottomLeft.b + bottomRight.b) / 4,
				   (topLeft.a + topRight.a + bottomLeft.a + bottomRight.a) / 4);
		rlTexCoord2f(texShapesRec.x + texShapesRec.width / 2, texShapesRec.y + texShapesRec.height / 2);
		rlVertex2f(centerX, centerY);
	}

	rlEnd();
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

#pragma clang diagnostic pop