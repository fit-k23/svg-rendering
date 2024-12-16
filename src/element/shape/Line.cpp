#include "Line.h"

SVGLine::SVGLine() : endPosition(Vector2D<float>()) {}
SVGLine::SVGLine(const Vector2D<float> &_position, const SVGColor &_fillColor, const SVGColor &_strokeColor, float _strokeWidth, const Vector2D<float> &_endPosition) : Element(_position, _fillColor, _strokeColor, _strokeWidth), endPosition(_endPosition) {}

ElementType SVGLine::getTypeName() {
	return ElementType::Line;
}

void SVGLine::dbg() {
	Element::dbg();
	std::cout << "End position: (" << endPosition.x << ", " << endPosition.y << ")\n";
}

std::pair<Vector2D < float>, Vector2D<float>> SVGLine::getBoundingBox() const {
	Vector2D<float> topLeft = Vector2D<float>(std::min(position.x, endPosition.x) - strokeWidth / 2.0f, std::min(position.y, endPosition.y) - strokeWidth / 2.0f);
	Vector2D<float> bottomRight = Vector2D<float>(std::max(position.x, endPosition.x) - strokeWidth / 2.0f, std::max(position.y, endPosition.y) + strokeWidth / 2.0f);
	return {topLeft, bottomRight};
}

void SVGLine::setEndPosition(const Vector2D<float> &endPosition) { this->endPosition = endPosition; }

Vector2D<float> SVGLine::getEndPosition() const { return this->endPosition; }

float SVGLine::getSlope() const {
	return fabs(endPosition.y - position.y) / fabs(endPosition.x - position.x);
}

bool SVGLine::isIntersect(const SVGLine &other) const {
	if (getSlope() == other.getSlope()) return false;
	return true;
}

Vector2D<float> SVGLine::getIntersected(const SVGLine &other) const {
	float a1 = getSlope(), a2 = other.getSlope();
	float b1 = position.y - a1 * position.x;
	float b2 = other.position.y - a2 * other.position.x;
	float intersectX = (b2 - b1) / (a1 - a2);
	float intersectY = a1 * intersectX + b1;
	return {intersectX, intersectY};
}
