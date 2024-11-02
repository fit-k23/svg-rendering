#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "Graphic.h"
#include "../../lib/raylib/raylib.h"
#include "../../lib/raylib/raymath.h"
#include "../../lib/raylib/rlgl.h"

class Renderer {
private:
	Vector2D<double> viewPort;
	std::vector<Element*> shapes;
public: 
	/*
	* @brief Default constructor
	*/
	Renderer();

	/*
	* @brief Parameterized constructor
	* @param vector of pointers to Element abstract type
	*/
	Renderer(const Vector2D<double>& viewPort, const std::vector<Element*>& shapes);

	/*
	* @brief Destructor
	* @note Delete all pointers in shapes vector
	*/
	~Renderer();

	/*
	* @brief Traverse and draw all elements 
	*/
	void draw();

	/*
	* @brief Draw a rectangle
	*/
	void drawRect(Element* element);

	/*
	* @brief Draw an ellipse
	*/
	void drawEllipse(Element* element);

	/*
	* @brief Draw a circle
	*/
	void drawCircle(Element* element);

	/*
	* @brief Draw a line
	*/
	void drawLine(Element* element);

	/*
	* @brief Draw polyline
	*/
	void drawPolyline(Element* element);

	/*
	* @brief Draw a polygon
	*/
	void drawPolygon(Element* element);

	/*
	* @brief Draw text
	*/
	void drawText(Element* element);

	/*
	* @brief Draw path
	*/
	void drawPath(Element* element);
};

#endif //RENDERER_H
