#ifndef SVG_RENDERING_RENDERER_H
#define SVG_RENDERING_RENDERER_H

#include <vector>
#include "Graphic.h"
#include <gdiplus.h>
#include "../Application.h"
#include "Camera.h"

using std::string;
using std::vector;

#ifndef RAD2DEG
#ifndef M_PI_F
#define M_PI_F 3.1415927f
#endif
#define RAD2DEG(angle) ((angle) / M_PI_F * 180.0f + ((angle) > 0 ? 0 : 360.0f))
#endif

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
	static Gdiplus::Brush *getBrush(Gdiplus::RectF boundingBox, Gradient *grad, const SVGColor &color, Gdiplus::GraphicsPath *path = nullptr);
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
	static void configGraphic(Gdiplus::Graphics &graphics);
	static void configCamera(Gdiplus::Graphics &graphics);

	static sRGBLinearGradientBrush *getSRGBLinearGradientBrush(Gdiplus::RectF boundingBox, const LinearGradient *gradient);
	static sRGBRadialGradientBrush *getSRGBRadialGradientBrush(Gdiplus::RectF boundingBox, const RadialGradient *gradient);

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
