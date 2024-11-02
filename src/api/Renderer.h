#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "Graphic.h"
#include "../utils/Raylibex.h"

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
	Renderer(const Vector2D<float> &viewPort, const std::vector<Element*> &shapes);

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
	void drawRect(Rectangle *element, RenderTexture2D &renderTexture);

	/*
	* @brief Draw an ellipse
	*/
	void drawEllipse(Ellipse *element);

	/*
	* @brief Draw a circle
	*/
	void drawCircle(Circle *element);

	/*
	* @brief Draw a line
	*/
	void drawLine(Line *element);

	/*
	* @brief Draw polyline
	*/
	void drawPolyline(Polyline *element);

	/*
	* @brief Draw a polygon
	*/
	void drawPolygon(Polygon *element);

	/*
	* @brief Draw text
	*/
	void drawText(Text *element);

	/*
	* @brief Draw path
	*/
	void drawPath(Path *element);
};

#endif //RENDERER_H
