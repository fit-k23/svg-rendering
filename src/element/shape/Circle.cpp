#include "Circle.h"

Circle::Circle(Vector2D<double> position, const SVGColor& fillColor, const SVGColor& strokeColor, double strokeWidth, 
	           double radius) : Ellipse(position, fillColor, strokeColor, strokeWidth, Vector2D<double>(radius, radius)) {};

ElementType Circle::getTypeName() {
	return ElementType::Circle;
}

/*
* @brief print information of Circle
*/
void Circle::dbg() {
	std::cout << "[DEBUG CIRCLE]\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ")\n";
	std::cout << "Radius = " << getRadii().x << '\n';
	std::cout << "Stroke width = " << strokeWidth << '\n';
}