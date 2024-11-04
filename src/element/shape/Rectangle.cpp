#include "Rectangle.h"

/*
* @brief Default constructor
*/
Rect::Rect() : Element(), width(0.0), height(0.0), radii() {}

/*
* @brief Parameterized constructor
* @param position: vector2D position of Rect
* @param width: width of Rect
* @param height: height of Rect
* @param radii: radii of Rect
* @param fillColor: fill color of Rect
* @param strokeColor: stroke color of Rect
* @param strokeWidth: stroke width of Rect
*/
Rect::Rect(const Vector2D<float> &_position, const SVGColor &_fillColor, const SVGColor &_strokeColor, float _strokeWidth,
	float _width, float _height, const Vector2D<float> &_radii) : Element(_position, _fillColor, _strokeColor, _strokeWidth), width(_width),
	height(_height), radii(_radii) {}

/*
* @brief Copy constructor
*/
Rect::Rect(const Rect& other) {
	this->position = other.position;
	this->fillColor = other.fillColor;
	this->strokeColor = other.strokeColor;
	this->strokeWidth = other.strokeWidth;
	this->width = other.width;
	this->height = other.height;
	this->radii = other.radii;
}

/*
* @brief get type of Rect
* @return ElementType::Rect
*/
ElementType Rect::getTypeName() {
	return ElementType::Rect;
}

/*
* @brief print data of Rect for debugging
*/
void Rect::dbg() {
	Element::dbg();
	std::cout << "Width = " << this->getWidth() << " Height = " << this->getHeight() << '\n';
	std::cout << "Radiix = " << radii.x << " Radiiy = " << radii.y << '\n';
}

/*
* @brief Get bounding box of rect
* @return pair of top-left and bottom-right coordinate
* @note This function doesn't change any attributes
*/
std::pair<Vector2D<float>, Vector2D<float>> Rect::getBoundingBox() const {
	Vector2D<float> topLeft = Vector2D<float>(position.x - strokeWidth / 2.0f, position.y - strokeWidth / 2.0f);
	Vector2D<float> bottomRight = Vector2D<float>(position.x + width + strokeWidth / 2.0f, position.y + height + strokeWidth / 2.0f);

	return {topLeft, bottomRight};
}

/*
* @brief set width of the Rect
* @param _width: passed width
*/
void Rect::setWidth(float _width) {
	this->width = _width;
}

/*
* @brief set height of the Rect
* @param _height: passed height
*/
void Rect::setHeight(float _height) {
	this->height = _height;
}

/*
* @brief get width of the Rect
* @return width of current Rect
*/
float Rect::getWidth() const {
	return this->width;
}

/*
* @brief get height of the Rect
* @return height of current Rect
*/
float Rect::getHeight() const {
	return this->height;
}

/*
* @brief set radii of the Rect
* @param radii: passed-by-reference radii
*/
void Rect::setRadii(const Vector2D<float>& radii) {
	this->radii = radii;
}

/*
* @brief get radii of the Rect
* @return radii of current Rect
*/
Vector2D<float> Rect::getRadii() const {
	return this->radii;
}
