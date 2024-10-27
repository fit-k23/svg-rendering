#include "Circle.h"

Circle::Circle(Vector2D<double> position, const SVGColor& fillColor, const SVGColor& strokeColor, double strokeWidth, double radius) : Ellipse(position, fillColor, strokeColor, strokeWidth, Vector2D<double>(radius, radius)) {};

ElementType Circle::getTypeName() {
	return ElementType::Circle;
}
