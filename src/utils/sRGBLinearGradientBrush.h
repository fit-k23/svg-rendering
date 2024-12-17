#ifndef SVG_RENDERING_SRGB_LINEAR_GRADIENT_BRUSH_H
#define SVG_RENDERING_SRGB_LINEAR_GRADIENT_BRUSH_H

#include <objidl.h>
#include <gdiplus.h>
#include "../element/utils/LinearGradient.h"

#ifndef RAD2DEG
#ifndef M_PI_F
#define M_PI_F 3.1415927f
#endif
#define RAD2DEG(angle) ((angle) / M_PI_F * 180.0f + ((angle) < 0 ? 360.0f : 0))
#endif

namespace sRGBLinearGradientBrushHelper{
	static Gdiplus::Bitmap *createBitmap(Gdiplus::RectF rect, const LinearGradient *gradient, float angle = 0.0f) {
		auto bitmap = new Gdiplus::Bitmap(rect.Width + rect.X, rect.Height + rect.Y);
		Gdiplus::Graphics graphics(bitmap);

		int centerX = rect.X + rect.Width / 2;
		int centerY = rect.Y + rect.Height / 2;

		graphics.TranslateTransform(centerX, centerY);
		graphics.RotateTransform(angle);
		graphics.TranslateTransform(-centerX, -centerY);

		Gdiplus::SolidBrush solidBrush({0, 0, 0, 0});

		angle = RAD2DEG(angle);

		float newWidth = abs(rect.Width * cos(angle)) + abs(rect.Height * sin(angle));
		rect.X += (rect.Width - newWidth) / 2;
		rect.Width = newWidth;

		vector<float> offsets;
		vector<SVGColor> colors;

		vector<Stop> stops = gradient->getStops();

		int stopAmount = 0;

		if (stops.front().getOffset() != 0.0f) {
			offsets.push_back(0.0f);
			++stopAmount;
			colors.push_back(stops.begin()->getStopColor());
		}
		for (auto &stop : stops) {
			offsets.push_back(stop.getOffset());
			++stopAmount;
			colors.push_back(stop.getStopColor());
		}
		if (stops.back().getOffset() != 1.0f) {
			offsets.push_back(1.0f);
			++stopAmount;
			colors.push_back(stops.back().getStopColor());
		}

		int cur = 1;
		int oldCur = 0;

		for (int x = 0; x < rect.Width; ++x) {
			float t = static_cast<float>(x) / (rect.Width - 1);

			if (t > offsets[cur]) {
				oldCur = cur;
				++cur;
			}

			float factor = (t - offsets[oldCur]) / (offsets[cur] - offsets[oldCur]);
			SVGColor gradientColor = colors[oldCur].interpol(colors[cur], factor);
			solidBrush.SetColor(gradientColor);
			graphics.FillRectangle(&solidBrush, x + rect.X, rect.Y - rect.Width / 2, 1.0f,  rect.Y + rect.Height + rect.Width);
		}

		return bitmap;
	}
}

class sRGBLinearGradientBrush : public Gdiplus::TextureBrush{
	Gdiplus::Bitmap *bitmap;
public:
	sRGBLinearGradientBrush(Gdiplus::Bitmap *bitmap) : TextureBrush(bitmap), bitmap(bitmap) {}
	~sRGBLinearGradientBrush() override;
};

#endif