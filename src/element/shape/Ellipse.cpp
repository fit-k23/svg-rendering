#include "Ellipse.h"

/**
 * @brief Default Constructor
 * @note Only use class Element and Vector2D so reuse the default constructor of those 2 classes
*/
SVGEllipse::SVGEllipse() : Element(), radii() {}

/** @brief Full-parameterized constructor of SVGEllipse */
SVGEllipse::SVGEllipse(const Vector2D<float> &_position, const SVGColor &_fillColor, const SVGColor &_strokeColor, float strokeWidth, const Vector2D<float> &_radii) : Element(_position, _fillColor, _strokeColor, strokeWidth), radii(_radii) {}

/**
 * @brief Get the type of element
 * @return ElementType::SVGEllipse
*/
ElementType SVGEllipse::getTypeName() {
	return ElementType::Ellipse;
}


/** @brief Print all data of SVGEllipse */
void SVGEllipse::dbg() {
	Element::dbg();
	std::cout << "Stroke Width: " << strokeWidth << '\n';
}

/**
 * @brief Get bounding box of SVGEllipse
 * @return pair of top-left and bottom-right coordinate
 * @note This function doesn't change any attributes
*/
std::pair<Vector2D < float>, Vector2D<float>> SVGEllipse::getBoundingBox() const {
	Vector2D<float> topLeft = Vector2D<float>(position.x - radii.x - strokeWidth / 2.0f, position.y - radii.y - strokeWidth / 2.0f);
	Vector2D<float> bottomRight = Vector2D<float>(position.x + radii.x + strokeWidth / 2.0f, position.y + radii.y + strokeWidth / 2.0f);
	return {topLeft, bottomRight};
}

/**
 * @brief Set horizontal and vertical radius of the SVGEllipse
 * @param radii updated radius
*/
void SVGEllipse::setRadii(const Vector2D<float> &_radii) { this->radii = _radii; }

/**
 * @brief Get horizontal and vertical radius of the SVGEllipse
 * @return Vector<T> Return the radius of the SVGEllipse
 * @note This function doesn't change any attributes
*/
Vector2D<float> SVGEllipse::getRadii() const { return radii; }
