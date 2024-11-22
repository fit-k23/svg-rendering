#include "Rectangle.h"

SVGRect::SVGRect() : Element(), width(0.0), height(0.0), radii() {}

SVGRect::SVGRect(const Vector2D<float> &_position, const SVGColor &_fillColor, const SVGColor &_strokeColor, float _strokeWidth, float _width, float _height, const Vector2D<float> &_radii) : Element(_position, _fillColor, _strokeColor, _strokeWidth), width(_width), height(_height), radii(_radii) {}

SVGRect::SVGRect(const SVGRect &other)  : Element(other) {
	width = other.width;
	height = other.height;
	radii = other.radii;
}

ElementType SVGRect::getTypeName() {
	return ElementType::Rectangle;
}

void SVGRect::dbg() {
	Element::dbg();
	std::cout << "Width = " << this->getWidth() << " Height = " << this->getHeight() << '\n';
	std::cout << "Radiix = " << radii.x << " Radiiy = " << radii.y << '\n';
}

std::pair<Vector2D < float>, Vector2D<float>> SVGRect::getBoundingBox() const {
	Vector2D<float> topLeft = Vector2D<float>(position.x - strokeWidth / 2.0f, position.y - strokeWidth / 2.0f);
	Vector2D<float> bottomRight = Vector2D<float>(position.x + width + strokeWidth / 2.0f, position.y + height + strokeWidth / 2.0f);

	return {topLeft, bottomRight};
}

void SVGRect::setWidth(float _width) {
	this->width = _width;
}

void SVGRect::setHeight(float _height) {
	this->height = _height;
}

float SVGRect::getWidth() const {
	return this->width;
}

float SVGRect::getHeight() const {
	return this->height;
}

void SVGRect::setRadii(const Vector2D<float> &_radii) {
	this->radii = _radii;
}

Vector2D<float> SVGRect::getRadii() const {
	return this->radii;
}
