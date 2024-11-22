#include "Circle.h"

SVGCircle::SVGCircle(const Vector2D<float> &_position, const SVGColor &fillColor, const SVGColor &strokeColor, float strokeWidth, float radius) : SVGEllipse(_position, fillColor, strokeColor, strokeWidth, Vector2D<float>(radius, radius)) {};

ElementType SVGCircle::getTypeName() {
	return ElementType::Circle;
}

void SVGCircle::dbg() {
	Element::dbg();
	std::cout << "Radius = " << getRadii().x << '\n';
}

std::pair<Vector2D<float>, Vector2D<float>> SVGCircle::getBoundingBox() const {
	float radius = getRadii().x;
	Vector2D<float> topLeft = Vector2D<float>(position.x - radius - strokeWidth / 2.0f, position.y - radius - strokeWidth / 2.0f);
	Vector2D<float> bottomRight = Vector2D<float>(position.x + radius + strokeWidth / 2.0f, position.y + radius + strokeWidth / 2.0f);
	return {topLeft, bottomRight};
}
