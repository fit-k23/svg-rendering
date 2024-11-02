#include "Line.h"

/*
* @brief Default constructor
*/
Line::Line() : Element(), endPosition(Vector2D<float>()) {}

/*
* @brief Parameterized constructor
*/
Line::Line(const Vector2D<float>& position, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth,
	const Vector2D<float>& endPosition) : Element(position, fillColor, strokeColor, strokeWidth), endPosition(endPosition) {}

/*
* @brief Copy constructor
*/
Line::Line(const Line& other) {
	this->position = other.position;
	this->fillColor = other.fillColor;
	this->strokeColor = other.strokeColor;
	this->strokeWidth = other.strokeWidth;
	this->endPosition = other.endPosition;
}


/*
* @brief get type Line
* @return ElementType::Line
* @note This function is override
*/
ElementType Line::getTypeName() {
	return ElementType::Line;
}

/*
* @brief print information of line
*/
void Line::dbg() {
	std::cout << "[DEBUG LINE]\n";
	std::cout << "Start position: (" << position.x << ", " << position.y << ")\n";
	std::cout << "End position: (" << endPosition.x << ", " << endPosition.y << ")\n";
	std::cout << "Stroke width: " << strokeWidth << '\n';
}

/*
* @brief set end position of line
*/
void Line::setEndPosition(const Vector2D<float>& endPosition) { this->endPosition = endPosition;  }

/*
* @brief get end position of a line
* @note This function does not change any attributes
*/
Vector2D<float> Line::getEndPosition() const { return this->endPosition;  }

/*
* @brief Get slope coefficient of the line
* @return slope 
*/
float Line::getSlope() const {
	return (float)fabs(endPosition.y - position.y) / (float)fabs(endPosition.x - position.x);
}

/*
* @brief Check if two lines intersect each other
* @return bool
*/
bool Line::isIntersect(const Line& other) const {
	if (getSlope() == other.getSlope()) return false;
	return true;
}

/*
* @brief Get intersected point
* @return intersected point
*/
Vector2D<float> Line::getIntersected(const Line& other) const {
	float a1 = getSlope(), a2 = other.getSlope();
	float b1 = position.y - a1 * position.x;
	float b2 = other.position.y - a2 * other.position.x;
	float intersectX = (float)(b2 - b1) / (float)(a1 - a2);
	float intersectY = a1 * intersectX + b1;
	return Vector2D(intersectX, intersectY);
}

/// y = a1x + b1
/// y = a2x + b2 
/// a1x + b1 = a2x + b2
/// (a1 - a2)x = b2 - b1 