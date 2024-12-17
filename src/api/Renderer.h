#ifndef SVG_RENDERING_RENDERER_H
#define SVG_RENDERING_RENDERER_H

#include <vector>
#include "Graphic.h"
#include <gdiplus.h>
#include "Camera.h"

using std::string;
using std::vector;

#ifndef M_PI_F
#define M_PI_F 3.1415927f
#endif
#define RAD2DEG(angle) ((angle) / M_PI_F * 180.0f + ((angle) > 0 ? 0 : 360.0f))

/** @brief Singleton instance for managing the rendering of Element */
class Renderer final{
	/** @param viewPort The viewport of svg */
	Vector2D<float> viewPort;
	/** @param instance the pointer to current instance of Renderer */
	static Renderer *instance;

	Renderer();
	/**
	 * @brief Apply transformation to gdiplus graphics
	 * @param transformations List of transformation in string format
	 */
	static void applyTransformation(Gdiplus::Graphics &graphics, const std::vector<std::string> &transformations);
	/**
	 * @brief Get the correct type of brush
	 * @note Brush class is an abstract base class that defines a Brush object. 
	 * @note A Brush object is used to paint the interior of graphics shapes, such as rectangles, ellipses, pies, polygons, and paths.
	 */
	static Gdiplus::Brush *getBrush(Gdiplus::RectF boundingBox, Gradient *grad, const SVGColor &color);
	static Gdiplus::SolidBrush *getBrush(const SVGColor &color);

	/** @brief Draw a rectangle */
	static void drawRect(Gdiplus::Graphics &graphics, const SVGRect *element);
	/** @brief Draw an ellipse */
	static void drawEllipse(Gdiplus::Graphics &graphics, const SVGEllipse *element);
	/** @brief Draw a circle */
	static void drawCircle(Gdiplus::Graphics &graphics, SVGCircle *element);
	/** @brief Draw a line */
	static void drawLine(Gdiplus::Graphics &graphics, const SVGLine *element);
	/** @brief Draw polyline */
	static void drawPolyline(Gdiplus::Graphics &graphics, const SVGPolyline *element);
	/** @brief Draw a polygon */
	static void drawPolygon(Gdiplus::Graphics &graphics, const SVGPolygon *element);
	/** @brief Draw text */
	static void drawText(Gdiplus::Graphics &graphics, const SVGText *element);
	/** @brief Draw path */
	static void drawPath(Gdiplus::Graphics &graphics, const SVGPath *element);
public:
	static void configGraphic(Gdiplus::Graphics &graphics) {
		graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias8x8);
		graphics.SetTextContrast(100);
		graphics.SetCompositingMode(Gdiplus::CompositingModeSourceOver);
		graphics.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality);
		graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);
	}

	static void configCamera(Gdiplus::Graphics &graphics) {
		graphics.TranslateTransform(Camera::startPosition.x, Camera::startPosition.y);
		graphics.TranslateTransform(Camera::mousePosition.x, Camera::mousePosition.y);
		graphics.ScaleTransform(Camera::zoom, Camera::zoom);
		graphics.RotateTransform(Camera::rotation);
		graphics.TranslateTransform(-Camera::mousePosition.x, -Camera::mousePosition.y);
	}

	static Gdiplus::Brush *getGradientBrush(Gdiplus::RectF boundingBox, const Gradient *gradient) {
		if (gradient == nullptr) {
			return nullptr;
		}

		auto *gradientBitmap = new Gdiplus::Bitmap(static_cast<int>(boundingBox.Width + boundingBox.X), static_cast<int>(boundingBox.Height + boundingBox.Y));
		Gdiplus::Graphics graphics(gradientBitmap);

		float globalHeight = boundingBox.Height + boundingBox.Y;
		int width = static_cast<int>(boundingBox.Width);

		const vector<Stop> stops = gradient->getStops();
		if (stops.size() == 1)
			return new Gdiplus::SolidBrush(stops.begin()->getStopColor());

		vector<float> offsets;
		vector<Gdiplus::Color> colors;
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
		// TODO: Process linear and radial brush
		if (gradient->getType() == GradientType::Linear) {
			auto linearGradient = static_cast<const LinearGradient *>(gradient); // NOLINT(*-pro-type-static-cast-downcast)
			if (linearGradient->getPos(0) == linearGradient->getPos(1)) {
				return new Gdiplus::SolidBrush(stops.back().getStopColor());
			}

			float x1 = linearGradient->getX1();
			float y1 = linearGradient->getY1();
			float x2 = linearGradient->getX2();
			float y2 = linearGradient->getY2();

			float diffX = x2 - x1;
			float diffY = y2 - y1;

			if (diffX != 0) {
				boundingBox.X -= x1 * boundingBox.Width;
				boundingBox.Width *= diffX;
			}
			if (diffY != 0) {
				boundingBox.Y -= y1 * boundingBox.Height;
				boundingBox.Height *= diffY;
			}

			float angle = atan2f(diffY, diffX); // rad

			auto *lBrush = new Gdiplus::LinearGradientBrush(boundingBox, SVG_BLANK, SVG_BLANK, RAD2DEG(angle), false);
			lBrush->SetInterpolationColors(colors.data(), offsets.data(), stopAmount);
			return lBrush;
		}
		return nullptr;
	}

	/** @brief Get the singleton instance of Renderer */
	static Renderer *getInstance();
	Renderer(const Renderer &other) = delete;
	/** @brief Traverse and draw all elements */
	void draw(Gdiplus::Graphics &graphics, const Group *parent);

	/**
	 * @brief Set current viewport to input viewport
	 * @param viewPort New viewport
	 */
	void setViewPort(const Vector2D<float> &viewPort);

	/**
	 * @brief Get the view port
	 * @note This function doesn't change any attributes
	 */
	Vector2D<float> getViewPort() const;
};

#endif // SVG_RENDERING_RENDERER_H
