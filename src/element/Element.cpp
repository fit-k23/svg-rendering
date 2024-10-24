#include "Element.h"

/*
* @cmt: Parameterized constructor
* @note: easier for subclass to inherit and write its constructor
*/
Element::Element(Vector2D<double> position, const SVGColor& fillColor, const SVGColor& strokeColor, double strokeWidth) {
	this->position = position;
	this->fillColor = fillColor;
	this->strokeColor = strokeColor;
	this->strokeWidth = strokeWidth;
}

/*
* @cmt: set position of an svg element
* @param: x and y coordinates (double)
*/
void Element::setPosition(double x, double y) {
	this->position.x = x;
	this->position.y = y;
}

/*
* @cmt: set position of an svg element
* @param: a passed-by-referenced vector2D object
*/
void Element::setPosition(const Vector2D<double>& position) {
	this->position.x = position.x;
	this->position.y = position.y;
}

/*
* @cmt: get position of an svg element
* @return: a vector2D
*/
Vector2D<double> Element::getPosition() {
	return position;
}

/*
* @cmt: set fill color of an svg element
* @param: a passed-by-referenced SVGColor object
*/
void Element::setFillFolor(const SVGColor& color) {
	this->fillColor = color;
}

/*
* @cmt: get fill color of an svg element
* @return: an SVGColor object
*/
SVGColor Element::getFillColor() {
	return this->fillColor;
}

/*
* @cmt: set stroke color of an svg element
* @param: a passed-by-referenced SVGColor object
*/
void Element::setStrokeColor(const SVGColor& color) {
	this->strokeColor = color;
}

/*
* @cmt: get stroke color of an svg element
* @return: a SVGColor object
*/
SVGColor Element::getStrokeColor() {
	return this->strokeColor;
}

/*
* @cmt: set stroke width of an svg element
* @param: a double variable
*/
void Element::setstrokeWidth(double width) {
	this->strokeWidth = width;
}

/*
* @cmt: get stroke width of an svg element
* @return: double
*/
double Element::getstrokeWidth() {
	return this->strokeWidth;
}

/*
* @cmt: set gradient of an svg element
* @param: a pointer to an abstract Gradient object
*/
void Element::setGradient(Gradient* grad) {
	this->gradient = grad;
}

/*
* @cmt: get gradient of an svg element
* @param: a pointer to a Gradient object
*/
Gradient* Element::getGradient() {
	return this->gradient;
}

/*
* @cmt: set parent node of an svg element
* @param: a pointer to a same-class object (parent)
*/
void Element::setParent(Element* parent) {
	this->parent = parent;
}

/*
* @cmt: get parent node of an svg element
* @return: a pointer to a same-class object (parent)
*/
Element* Element::getParent() {
	return this->parent;
}
