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
	Element::dbg();
	std::cout << "Radius = " << getRadii().x << '\n';
}

/*
* @brief Get bounding box of circle
* @return pair of top-left and bottom-right coordinate
* @note This function doesn't change any attributes
*/
std::pair<Vector2D<float>, Vector2D<float>> Circle::getBoundingBox() const {
	float radius = getRadii().x;
	Vector2D<float> topLeft = Vector2D<float>(position.x - radius - strokeWidth / 2.0f, position.y - radius - strokeWidth / 2.0f);
	Vector2D<float> bottomRight = Vector2D<float>(position.x + radius + strokeWidth / 2.0f, position.y + radius + strokeWidth / 2.0f);
	return { topLeft, bottomRight };
}
