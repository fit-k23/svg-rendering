#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <sstream>
#include "Graphic.h"
#include <gdiplus.h>

/**
 * @brief A class to render shapes
 * @param screenSize the screen size
 * @param viewPort the viewport of svg
 * @param instance the pointer to current instance of Renderer
 */

class Renderer{
private:
	Vector2D<float> screenSize;
	Vector2D<float> viewPort;
	static Renderer *instance;
public:
	/** 
	 * @brief Get instance of XMLParser (apply singleton design pattern)
	 */
	static Renderer *getInstance();

	/** 
	 * @brief Delete copy constructor to ensure the singleton design pattern
	 */
	Renderer(const Renderer &other) = delete;
	
	/** @brief Traverse and draw all elements */
	void draw(Gdiplus::Graphics& graphics, Element *par);

	/** 
	 * @brief Set new screen size
	 * @param screenSize new screen size
	 */
	void setScreenSize(const Vector2D<float> &screenSize);

	/** 
	 * @brief Get the screen size
	 * @note This function doesn't change any attributes
	 */
	Vector2D<float> getScreenSize() const;

	/** 
	 * @brief Set new view port
	 * @param viewPort new view port
	 */
	void setViewPort(const Vector2D<float> &viewPort);

	/** 
	 * @brief Get the view port
	 * @note This function doesn't change any attributes
	 */	
	Vector2D<float> getViewPort() const;
private:
	/** @brief Default constructor */
	Renderer();

	/**
	 * @brief Parameterized constructor
	 * @param vector of pointers to Element abstract type
	*/
	Renderer(const Vector2D<float> &viewPort);
	
	/**
	 * @brief Constructor with view port and screen size.
	 */
	Renderer(const Vector2D<float> &viewPort, const Vector2D<float> &screenSize);

	/** 
	 * @brief Apply transformation to gdiplus graphics path
	 * @param path the graphics path
	 * @param transformation the vector of transformation
	 */
	void applyTransformation(Gdiplus::Graphics &graphics, const std::vector<std::string>& transformations);

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
};

#endif //RENDERER_H
