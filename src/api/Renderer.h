#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "Graphic.h"
#include <gdiplus.h>

class Renderer{
private:
	Vector2D<float> screenSize;
	Vector2D<float> viewPort;
	std::vector<Element *> shapes;
public:
	/*
	* @brief Default constructor
	*/
	Renderer();

	/*
	* @brief Parameterized constructor
	* @param vector of pointers to Element abstract type
	*/
	Renderer(const Vector2D<float> &viewPort, const std::vector<Element *> &shapes);

	Renderer(const Vector2D<float> &viewPort, const std::vector<Element *> &shapes, Vector2D<float> screenSize);

	/*
	* @brief Destructor
	* @note Delete all pointers in shapes vector
	*/
	~Renderer();

	void addShape(Element *shape) {
		shapes.push_back(shape);
	}

	/*
	* @brief Traverse and draw all elements
	*/
	void draw();

	/*
	* @brief Draw a rectangle
	*/
	void drawRect(SVGRect *element);

	/*
	* @brief Draw an ellipse
	*/
	void drawEllipse(SVGEllipse *element);

	/*
	* @brief Draw a circle
	*/
	void drawCircle(SVGCircle *element);

	/*
	* @brief Draw a line
	*/
	void drawLine(SVGLine *element);

	/*
	* @brief Draw polyline
	*/
	void drawPolyline(SVGPolyline *element);

	/*
	* @brief Draw a polygon
	*/
	void drawPolygon(SVGPolygon *element);

	/*
	* @brief Draw text
	*/
	void drawText(SVGText *element, float offset);

	/*
	* @brief Draw path
	*/
	void drawPath(SVGPath *element);
};

#endif //RENDERER_H
