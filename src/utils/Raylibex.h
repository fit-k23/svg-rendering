#ifndef SVG_RENDERING_RAYLIBEX_H
#define SVG_RENDERING_RAYLIBEX_H

#include "../../lib/raylib/raylib.h"
#include "../../lib/raylib/rlgl.h"
#include "../../lib/raylib/raymath.h"

void draw_rect_roundedRLEX(float posX, float posY, float width, float height, float radiusx, float radiusy, Color color);

void DrawRectangleRoundedRLEX(Rectangle rect, Vector2 radius, Color color, RenderTexture2D rt);

void DrawRectangleRoundedStrokeRLEX(Rectangle rect, Vector2 radius, float stroke, Color fillColor, Color strokeColor, RenderTexture2D rt);

void DrawEllipseRLEX(int centerX, int centerY, float radiusH, float radiusV, Color color, int step = 10);
void DrawEllipseVRLEX(Vector2 position, Vector2 radius, Color color, int step = 10);
void DrawEllipseStrokeRLEX(Vector2 position, Vector2 radius, float stroke, Color fillColor, Color strokeColor, int step, RenderTexture2D rt, Camera2D camera);

void DrawRectangleGradientHQ(Rectangle rec, Color topLeft, Color bottomLeft, Color topRight, Color bottomRight);

void DrawRectangleGradientOP(Rectangle rec, Color topLeft, Color bottomLeft, Color topRight, Color bottomRight);

void DrawEllipseGradientHQ(float centerX, float centerY, float radiusX, float radiusY, Color topLeft, Color bottomLeft, Color topRight, Color bottomRight);

void DrawEllipseGradientHQ(Rectangle rec, Color topLeft, Color bottomLeft, Color topRight, Color bottomRight);

void DrawEllipseGradientRadius(int centerX, int centerY, float radiusX, float radiusY, Color color1, Color color2, int segment = 100);

#endif //SVG_RENDERING_RAYLIBEX_H
