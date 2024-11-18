#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <sstream>
#include "Graphic.h"
#include <gdiplus.h>

class Renderer{
private:
	Vector2D<float> screenSize;
	Vector2D<float> viewPort;
	std::vector<Element *> shapes;
	static Renderer *instance;
public:
	/*
	* @brief Get instance of XMLParser (apply singleton design pattern)
	*/
	static Renderer *getInstance();

	/*
	* @brief Delete copy constructor to ensure the singleton design pattern
	*/
	Renderer(const Renderer &other) = delete;
	
	/** @brief Traverse and draw all elements */
	void draw(Gdiplus::Graphics& graphics);
	
	void setScreenSize(const Vector2D<float> &screenSize);

	Vector2D<float> getScreenSize() const;

	void setViewPort(const Vector2D<float> &viewPort);

	Vector2D<float> getViewPort() const;

	void setShapes(const std::vector<Element *> &shapes);

	std::vector<Element *> getShapes() const;

private:
	/** @brief Default constructor */
	Renderer();

	/**
	 * @brief Parameterized constructor
	 * @param vector of pointers to Element abstract type
	*/
	Renderer(const Vector2D<float> &viewPort, const std::vector<Element *> &shapes);
	Renderer(const Vector2D<float> &viewPort, const std::vector<Element *> &shapes, const Vector2D<float> &screenSize);

	/*
	* @brief Add new shape
	*/
	void addShape(Element* shape);

	/*
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
