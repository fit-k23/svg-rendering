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
Rect::Rect(const Vector2D<float> &_position, const SVGColor &fillColor, const SVGColor& strokeColor, float strokeWidth,
	float width, float height, Vector2D<float>radii) : Element(_position, fillColor, strokeColor, strokeWidth), width(width),
	height(height), radii(radii) {}

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
	std::cout << "[DEBUG RECT]\n";
	std::cout << "Position: " << (this->getPosition()).x << " " << (this->getPosition()).y << '\n';
	std::cout << "Width = " << this->getWidth() << " Height = " << this->getHeight() << '\n';
	std::cout << "Radiix = " << radii.x << " Radiiy = " << radii.y << '\n';
	// TODO: print fillColor, strokeColor
	std::cout << "Fill color: "; fillColor.output(); 
	std::cout << "Stroke color: "; strokeColor.output();
	std::cout << "strokeWidth = " << this->getStrokeWidth() << '\n';
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
