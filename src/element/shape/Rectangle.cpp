#include "Rectangle.h"

/** @brief Default constructor */
SVGRect::SVGRect() : Element(), width(0.0), height(0.0), radii() {}

/**
 * @brief Parameterized constructor
 * @param position: vector2D position of SVGRect
 * @param width: width of SVGRect
 * @param height: height of SVGRect
 * @param radii: radii of SVGRect
 * @param fillColor: fill color of SVGRect
 * @param strokeColor: stroke color of SVGRect
 * @param strokeWidth: stroke width of SVGRect
*/
SVGRect::SVGRect(const Vector2D<float> &_position, const SVGColor &_fillColor, const SVGColor &_strokeColor, float _strokeWidth, float _width, float _height, const Vector2D<float> &_radii) : Element(_position, _fillColor, _strokeColor, _strokeWidth), width(_width), height(_height), radii(_radii) {}

/** @brief Copy constructor */
SVGRect::SVGRect(const SVGRect &other)  : Element(other) {
	width = other.width;
	height = other.height;
	radii = other.radii;
}

/**
 * @brief get type of SVGRect
 * @return ElementType::SVGRect
*/
ElementType SVGRect::getTypeName() {
	return ElementType::Rectangle;
}

/** @brief print data of SVGRect for debugging */
void SVGRect::dbg() {
	Element::dbg();
	std::cout << "Width = " << this->getWidth() << " Height = " << this->getHeight() << '\n';
	std::cout << "Radiix = " << radii.x << " Radiiy = " << radii.y << '\n';
}

/**
 * @brief Get bounding box of svgrect
 * @return pair of top-left and bottom-right coordinate
 * @note This function doesn't change any attributes
*/
std::pair<Vector2D < float>, Vector2D<float>> SVGRect::getBoundingBox() const {
	Vector2D<float> topLeft = Vector2D<float>(position.x - strokeWidth / 2.0f, position.y - strokeWidth / 2.0f);
	Vector2D<float> bottomRight = Vector2D<float>(position.x + width + strokeWidth / 2.0f, position.y + height + strokeWidth / 2.0f);

	return {topLeft, bottomRight};
}

/**
 * @brief set width of the SVGRect
 * @param _width: passed width
*/
void SVGRect::setWidth(float _width) {
	this->width = _width;
}

/**
 * @brief set height of the SVGRect
 * @param _height: passed height
*/
void SVGRect::setHeight(float _height) {
	this->height = _height;
}

/**
 * @brief get width of the SVGRect
 * @return width of current SVGRect
*/
float SVGRect::getWidth() const {
	return this->width;
}

/**
 * @brief get height of the SVGRect
 * @return height of current SVGRect
*/
float SVGRect::getHeight() const {
	return this->height;
}

/**
 * @brief set radii of the SVGRect
 * @param radii: passed-by-reference radii
*/
void SVGRect::setRadii(const Vector2D<float> &_radii) {
	this->radii = _radii;
}

/**
 * @brief get radii of the SVGRect
 * @return radii of current SVGRect
*/
Vector2D<float> SVGRect::getRadii() const {
	return this->radii;
}
