#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "Graphic.h"
#include "../../lib/raylib/raylib.h"
#include "../../lib/raylib/raymath.h"
#include "../../lib/raylib/rlgl.h"

class Renderer {
private:
	Vector2D<float> viewPort;
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
	Renderer(const Vector2D<float>& viewPort, const std::vector<Element*>& shapes);

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
	* @brief Draw a rounded rectangle
	* @note Draw 5 rectangle and 4 ellipse .-.
	*/
	void drawRoundedRect(float posX, float posY, float width, float height, float radiusx, float radiusy, SVGColor color, RenderTexture2D renderTexture);

	/*
	* @brief Draw a rectangle
	*/
	void drawRect(Element* element, RenderTexture2D& renderTexture);

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
