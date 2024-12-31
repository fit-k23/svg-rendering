#ifndef SVG_RENDERING_S_RGB_RADIAL_GRADIENT_BRUSH_H
#define SVG_RENDERING_S_RGB_RADIAL_GRADIENT_BRUSH_H

#include <objidl.h>
#include <gdiplus.h>
#include "../element/utils/RadialGradient.h"

#ifndef RAD2DEG
#ifndef M_PI_F
#define M_PI_F 3.1415927f
#endif
#define RAD2DEG(angle) ((angle) / M_PI_F * 180.0f + ((angle) < 0 ? 360.0f : 0))
#endif

namespace sRGBRadialGradientBrushHelper{
	static Gdiplus::Bitmap *createBitmap(Gdiplus::RectF rect, const RadialGradient *gradient) {
		auto bitmap = new Gdiplus::Bitmap(rect.Width + rect.X, rect.Height + rect.Y);
		Gdiplus::Graphics graphics(bitmap);

		vector<Stop> stops = gradient->getStops();
		vector<float> offsets;
		vector<SVGColor> colors;

		if (stops.front().getOffset() != 0.0f) {
			offsets.push_back(0.0f);
			colors.push_back(stops.begin()->getStopColor());
		}
		for (auto &stop : stops) {
			offsets.push_back(stop.getOffset());
			colors.push_back(stop.getStopColor());
		}
		if (stops.back().getOffset() != 1.0f) {
			offsets.push_back(1.0f);
			colors.push_back(stops.back().getStopColor());
		}

		int cur = 1;
		int oldCur = 0;

		Vector2D size = {rect.Width, rect.Height};
		Vector2D<float> focus = gradient->getFocal() * size;
		Vector2D<float> pos = gradient->getPos() * size;
		float radius = gradient->getRadius() * rect.Width;
		Vector2D<float> diff = pos - focus;

		Vector2D<float> circlePos;
		Vector2D rectPos = {rect.X, rect.Y};
		Gdiplus::Pen pen(SVG_BLANK);
		for (float i = 0.0f; i < rect.Width; i += 0.5f) {
			float t = i / (rect.Width - 1);
			float circleRadius = radius * t;
			circlePos = rectPos + focus - circleRadius + diff * t;
			if (t > offsets[cur]) {
				oldCur = cur++;
			}
			float factor = (t - offsets[oldCur]) / (offsets[cur] - offsets[oldCur]);
			pen.SetColor(colors[oldCur].interpol(colors[cur], factor));
			graphics.DrawEllipse(&pen, circlePos.x, circlePos.y, 2 * circleRadius, 2 * circleRadius);
		}
		return bitmap;
	}
}

class sRGBRadialGradientBrush final : public Gdiplus::TextureBrush{
	Gdiplus::Bitmap *bitmap;
public:
	sRGBRadialGradientBrush(Gdiplus::Bitmap *bitmap) : TextureBrush(bitmap), bitmap(bitmap) {}
	~sRGBRadialGradientBrush() override { delete bitmap; }
};

#endif
