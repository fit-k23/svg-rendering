#include "Circle.h"

Circle::Circle(Vector2D<float> position, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth,
	           float radius) : Ellipse(position, fillColor, strokeColor, strokeWidth, Vector2D<float>(radius, radius)) {};

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
	std::cout << "Fill color: "; fillColor.output(); std::cout << '\n';
	std::cout << "Stroke color: "; strokeColor.output(); std::cout << '\n';
}