#include "Line.h"

/*
* @brief Default constructor
*/
Line::Line() : Element(), endPosition(Vector2D<double>()) {}

/*
* @brief Parameterized constructor
*/
Line::Line(const Vector2D<double>& position, const SVGColor& fillColor, const SVGColor& strokeColor, double strokeWidth,
	const Vector2D<double>& endPosition) : Element(position, fillColor, strokeColor, strokeWidth), endPosition(endPosition) {}

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
void Line::setEndPosition(const Vector2D<double>& endPosition) { this->endPosition = endPosition;  }

/*
* @brief get end position of a line
* @note This function does not change any attributes
*/
Vector2D<double> Line::getEndPosition() const { return this->endPosition;  }

/*
* @brief Get slope coefficient of the line
* @return slope 
*/
double Line::getSlope() const {
	return (double)fabs(endPosition.y - position.y) / (double)fabs(endPosition.x - position.x);
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
Vector2D<double> Line::getIntersected(const Line& other) const {
	double a1 = getSlope(), a2 = other.getSlope();
	double b1 = position.y - a1 * position.x;
	double b2 = other.position.y - a2 * other.position.x;
	double intersectX = (double)(b2 - b1) / (double)(a1 - a2);
	double intersectY = a1 * intersectX + b1;
	return Vector2D(intersectX, intersectY);
}

/// y = a1x + b1
/// y = a2x + b2 
/// a1x + b1 = a2x + b2
/// (a1 - a2)x = b2 - b1 