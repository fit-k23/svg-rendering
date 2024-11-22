#ifndef SVG_RENDERING_RENDERER_H
#define SVG_RENDERING_RENDERER_H

#include <vector>
#include <sstream>
#include "Graphic.h"
#include <gdiplus.h>

/** @brief Singleton instance for managing the rendering of Element */
class Renderer final{
	/** @param viewPort The viewport of svg */
	Vector2D<float> viewPort;
	/** @param instance the pointer to current instance of Renderer */
	static Renderer *instance;

	Renderer();
	/**
	 * @brief Apply transformation to gdiplus graphics
	 * @param transformation List of transformation in string format
	*/
	void applyTransformation(Gdiplus::Graphics &graphics, const std::vector<std::string> &transformations);
	/** @brief Draw a rectangle */
	void drawRect(Gdiplus::Graphics &graphics, SVGRect *element);
	/** @brief Draw an ellipse */
	void drawEllipse(Gdiplus::Graphics &graphics, SVGEllipse *element);
	/** @brief Draw a circle */
	void drawCircle(Gdiplus::Graphics &graphics, SVGCircle *element);
	/** @brief Draw a line */
	void drawLine(Gdiplus::Graphics &graphics, SVGLine *element);
	/** @brief Draw polyline */
	void drawPolyline(Gdiplus::Graphics &graphics, SVGPolyline *element);
	/** @brief Draw a polygon */
	void drawPolygon(Gdiplus::Graphics &graphics, SVGPolygon *element);
	/** @brief Draw text */
	void drawText(Gdiplus::Graphics &graphics, SVGText *element);
	/** @brief Draw path */
	void drawPath(Gdiplus::Graphics &graphics, SVGPath *element);
public:
	/** @brief Get the singleton instance of Renderer */
	static Renderer *getInstance();

	Renderer(const Renderer &other) = delete;

	/** @brief Traverse and draw all elements */
	void draw(Gdiplus::Graphics &graphics, Element *par);

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
