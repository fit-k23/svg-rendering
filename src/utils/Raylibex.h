#ifndef SVG_RENDERING_RAYLIBEX_H
#define SVG_RENDERING_RAYLIBEX_H

#include "../../lib/raylib/raylib.h"
#include "../../lib/raylib/rlgl.h"
#include "../../lib/raylib/raymath.h"

void DrawEllipseHQ(int centerX, int centerY, float radiusH, float radiusV, Color color, int step = 10);

void DrawRectangleGradientHQ(Rectangle rec, Color topLeft, Color bottomLeft, Color topRight, Color bottomRight);

void DrawRectangleGradientOP(Rectangle rec, Color topLeft, Color bottomLeft, Color topRight, Color bottomRight);

void DrawEllipseGradientHQ(float centerX, float centerY, float radiusX, float radiusY, Color topLeft, Color bottomLeft, Color topRight, Color bottomRight);

void DrawEllipseGradientHQ(Rectangle rec, Color topLeft, Color bottomLeft, Color topRight, Color bottomRight);

void DrawEllipseGradientRadius(int centerX, int centerY, float radiusX, float radiusY, Color color1, Color color2, int segment = 100);

#endif //SVG_RENDERING_RAYLIBEX_H
