#include "Rectangle.h"
#include "conio.h"

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
Rect::Rect(Vector2D<double> position, const SVGColor& fillColor, const SVGColor& strokeColor, double strokeWidth,
	double width, double height, Vector2D<double>radii) : Element(position, fillColor, strokeColor, strokeWidth), width(width),
	height(height), radii(radii) {}

/*
* @brief Copy constructor
*/
Rect::Rect(const Rect& other) {
	this->position = other.position;
	this->width = other.width;
	this->height = other.height;
	this->strokeWidth = other.strokeWidth;
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
* @brief draw Rect
*/
void Rect::draw() {
	// TODO: use raylib to draw stuff here
	// DrawRectangle((int)position.x, (int)position.y, width, height, BLACK);
}

/*
* @brief print data of Rect for debugging
*/
void Rect::dbg() {
	std::cout << "Position: " << (this->getPosition()).x << " " << (this->getPosition()).y << '\n';
	std::cout << "Width = " << this->getWidth() << " Height = " << this->getHeight() << '\n';
	std::cout << "Radiix = " << radii.x << " Radiiy = " << radii.y << '\n';
	// TODO: print fillColor, strokeColor
	std::cout << "strokeWidth = " << this->getStrokeWidth() << '\n';
}

/*
* @brief set width of the Rect
* @param _width: passed width
*/
void Rect::setWidth(double _width) {
	this->width = _width;
}

/*
* @brief set height of the Rect
* @param _height: passed height
*/
void Rect::setHeight(double _height) {
	this->height = _height;
}

/*
* @brief get width of the Rect
* @return width of current Rect
*/
double Rect::getWidth() {
	return this->width;
}

/*
* @brief get height of the Rect
* @return height of current Rect
*/
double Rect::getHeight() {
	return this->height;
}

/*
* @brief set radii of the Rect
* @param radii: passed-by-reference radii
*/
void Rect::setRadii(const Vector2D<double>& radii) {
	this->radii = radii;
}

/*
* @brief get radii of the Rect
* @return radii of current Rect
*/
Vector2D<double> Rect::getRadii() {
	return this->radii;
}
