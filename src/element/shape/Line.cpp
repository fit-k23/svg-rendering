#include "Line.h"

/** @brief Default constructor */
SVGLine::SVGLine() : Element(), endPosition(Vector2D<float>()) {}

/** @brief Parameterized constructor */
SVGLine::SVGLine(const Vector2D<float> &_position, const SVGColor &_fillColor, const SVGColor &_strokeColor, float _strokeWidth, const Vector2D<float> &_endPosition) : Element(_position, _fillColor, _strokeColor, _strokeWidth), endPosition(_endPosition) {}

/** @brief Copy constructor */
SVGLine::SVGLine(const SVGLine &other) : Element(other) {
	endPosition = other.endPosition;
}

/**
 * @brief get type SVGLine
 * @return ElementType::SVGLine
 * @note This function is override
*/
ElementType SVGLine::getTypeName() {
	return ElementType::Line;
}

/** @brief print information of svgline */
void SVGLine::dbg() {
	Element::dbg();
	std::cout << "End position: (" << endPosition.x << ", " << endPosition.y << ")\n";
}

/**
 * @brief Get bounding box of svgline
 * @return pair of top-left and bottom-right coordinate
 * @note This function doesn't change any attributes
*/
std::pair<Vector2D < float>, Vector2D<float>> SVGLine::getBoundingBox() const {
	Vector2D<float> topLeft = Vector2D<float>(std::min(position.x, endPosition.x) - strokeWidth / 2.0f, std::min(position.y, endPosition.y) - strokeWidth / 2.0f);
	Vector2D<float> bottomRight = Vector2D<float>(std::max(position.x, endPosition.x) - strokeWidth / 2.0f, std::max(position.y, endPosition.y) + strokeWidth / 2.0f);
	return {topLeft, bottomRight};
}

/** @brief set end position of svgline */
void SVGLine::setEndPosition(const Vector2D<float> &endPosition) { this->endPosition = endPosition; }

/**
 * @brief get end position of a svgline
 * @note This function does not change any attributes
*/
Vector2D<float> SVGLine::getEndPosition() const { return this->endPosition; }

/**
 * @brief Get slope coefficient of the svgline
 * @return slope
*/
float SVGLine::getSlope() const {
	return (float) fabs(endPosition.y - position.y) / (float) fabs(endPosition.x - position.x);
}

/**
 * @brief Check if two lines intersect each other
 * @return bool
*/
bool SVGLine::isIntersect(const SVGLine &other) const {
	if (getSlope() == other.getSlope()) return false;
	return true;
}

/**
 * @brief Get intersected point
 * @return intersected point
*/
Vector2D<float> SVGLine::getIntersected(const SVGLine &other) const {
	float a1 = getSlope(), a2 = other.getSlope();
	float b1 = position.y - a1 * position.x;
	float b2 = other.position.y - a2 * other.position.x;
	float intersectX = (float) (b2 - b1) / (float) (a1 - a2);
	float intersectY = a1 * intersectX + b1;
	return {intersectX, intersectY};
}

/// y = a1x + b1
/// y = a2x + b2 
/// a1x + b1 = a2x + b2
/// (a1 - a2)x = b2 - b1 