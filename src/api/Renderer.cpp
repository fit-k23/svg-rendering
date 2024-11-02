#include "Renderer.h"
/*
* @brief Default constructor
*/
Renderer::Renderer() {
	viewPort = Vector2D<double>();
	shapes.clear();
}

/*
* @brief Parameterized constructor
* @param vector of pointers to Element abstract type
*/
Renderer::Renderer(const Vector2D<double>& viewPort, const std::vector<Element*>& shapes) : viewPort(viewPort), shapes(shapes) {}

/*
* @brief Destructor
* @note Delete all pointers in shapes vector
*/
Renderer::~Renderer() {
	for (int i = 0; i < (int)shapes.size(); ++i)
		delete shapes[i];
}

/*
* @brief Traverse and draw all elements
*/
void Renderer::draw() {
	InitWindow(viewPort.x, viewPort.y, "SVG-Renderer");

	while (!WindowShouldClose()) {
		BeginDrawing();

		for (int i = 0; i < (int)shapes.size(); ++i) {
			if (shapes[i]->getTypeName() == ElementType::Rect) {
				drawRect(shapes[i]);
			}
			else if (shapes[i]->getTypeName() == ElementType::Ellipse) {
				drawEllipse(shapes[i]);
			}
			else if (shapes[i]->getTypeName() == ElementType::Circle) {
				drawCircle(shapes[i]);
			}
			else if (shapes[i]->getTypeName() == ElementType::Line) {
				drawLine(shapes[i]);
			}
			else if (shapes[i]->getTypeName() == ElementType::Polyline) {
				drawPolyline(shapes[i]);
			}
			else if (shapes[i]->getTypeName() == ElementType::Polygon) {
				drawPolygon(shapes[i]);
			}
			else if (shapes[i]->getTypeName() == ElementType::Text) {
				drawText(shapes[i]);
			}
			else if (shapes[i]->getTypeName() == ElementType::Path) {
				drawPath(shapes[i]);
			}
		}

		EndDrawing();
	}

	CloseWindow();
}

/*
* @brief Draw a rectangle
*/
void Renderer::drawRect(Element* element) {
	Vector2D<double> position = element->getPosition();
	SVGColor fillColor = element->getFillColor();
	SVGColor strokeColor = element->getStrokeColor();
	double strokeWidth = element->getStrokeWidth();
	double width = static_cast<Rect*>(element)->getWidth();
	double height = static_cast<Rect*>(element)->getHeight();
	Vector2D<double> radii = static_cast<Rect*>(element)->getRadii();
	if (strokeWidth == 0) {
		DrawRectangleV(Vector2{ position.x, position.y }, Vector2{ width, height }, Color{ fillColor.r, fillColor.g, fillColor.b, fillColor.a });
	}
}

/*
* @brief Draw an ellipse
*/
void Renderer::drawEllipse(Element* element) {

}

/*
* @brief Draw a circle
*/
void Renderer::drawCircle(Element* element) {

}

/*
* @brief Draw a line
*/
void Renderer::drawLine(Element* element) {

}

/*
* @brief Draw polyline
*/
void Renderer::drawPolyline(Element* element) {

}

/*
* @brief Draw a polygon
*/
void Renderer::drawPolygon(Element* element) {

}

/*
* @brief Draw text
*/
void Renderer::drawText(Element* element) {

}

/*
* @brief Draw path
*/
void Renderer::drawPath(Element* element) {

}
