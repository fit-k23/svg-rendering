#include "Rectangle.h"

/*
* @brief Default constructor
*/
Rectangle::Rectangle() : Element(), width(0.0), height(0.0), radii() {}

/*
* @brief Parameterized constructor
* @param position: vector2D position of Rectangle
* @param width: width of Rectangle
* @param height: height of Rectangle
* @param radii: radii of Rectangle
* @param fillColor: fill color of Rectangle
* @param strokeColor: stroke color of Rectangle
* @param strokeWidth: stroke width of Rectangle
*/
Rectangle::Rectangle(const Vector2D<float> &_position, const SVGColor &_fillColor, const SVGColor &_strokeColor, float _strokeWidth, float _width, float _height, const Vector2D<float> &_radii) : Element(_position, _fillColor, _strokeColor, _strokeWidth), width(_width), height(_height), radii(_radii) {}

/*
* @brief Copy constructor
*/
Rectangle::Rectangle(const Rectangle &other)  : Element(other) {
	this->position = other.position;
	this->fillColor = other.fillColor;
	this->strokeColor = other.strokeColor;
	this->strokeWidth = other.strokeWidth;
	this->width = other.width;
	this->height = other.height;
	this->radii = other.radii;
}

/*
* @brief get type of Rectangle
* @return ElementType::Rectangle
*/
ElementType Rectangle::getTypeName() {
	return ElementType::Rectangle;
}

/*
* @brief print data of Rectangle for debugging
*/
void Rectangle::dbg() {
	Element::dbg();
	std::cout << "Width = " << this->getWidth() << " Height = " << this->getHeight() << '\n';
	std::cout << "Radiix = " << radii.x << " Radiiy = " << radii.y << '\n';
}

/*
* @brief Get bounding box of rect
* @return pair of top-left and bottom-right coordinate
* @note This function doesn't change any attributes
*/
std::pair<Vector2D < float>, Vector2D<float>>

Rectangle::getBoundingBox() const {
	Vector2D<float> topLeft = Vector2D<float>(position.x - strokeWidth / 2.0f, position.y - strokeWidth / 2.0f);
	Vector2D<float> bottomRight = Vector2D<float>(position.x + width + strokeWidth / 2.0f, position.y + height + strokeWidth / 2.0f);

	return {topLeft, bottomRight};
}

/*
* @brief set width of the Rectangle
* @param _width: passed width
*/
void Rectangle::setWidth(float _width) {
	this->width = _width;
}

/*
* @brief set height of the Rectangle
* @param _height: passed height
*/
void Rectangle::setHeight(float _height) {
	this->height = _height;
}

/*
* @brief get width of the Rectangle
* @return width of current Rectangle
*/
float Rectangle::getWidth() const {
	return this->width;
}

/*
* @brief get height of the Rectangle
* @return height of current Rectangle
*/
float Rectangle::getHeight() const {
	return this->height;
}

/*
* @brief set radii of the Rectangle
* @param radii: passed-by-reference radii
*/
void Rectangle::setRadii(const Vector2D<float> &_radii) {
	this->radii = _radii;
}

/*
* @brief get radii of the Rectangle
* @return radii of current Rectangle
*/
Vector2D<float> Rectangle::getRadii() const {
	return this->radii;
}
