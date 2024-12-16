#include "Ellipse.h"

SVGEllipse::SVGEllipse() {}

SVGEllipse::SVGEllipse(const Vector2D<float> &_position, const SVGColor &_fillColor, const SVGColor &_strokeColor, float strokeWidth, const Vector2D<float> &_radii) : Element(_position, _fillColor, _strokeColor, strokeWidth), radii(_radii) {}

ElementType SVGEllipse::getTypeName() {
	return ElementType::Ellipse;
}

void SVGEllipse::dbg() {
	Element::dbg();
	std::cout << "Stroke Width: " << strokeWidth << '\n';
}

std::pair<Vector2D <float>, Vector2D<float>> SVGEllipse::getBoundingBox() const {
	Vector2D<float> topLeft = Vector2D<float>(position.x - radii.x - strokeWidth / 2.0f, position.y - radii.y - strokeWidth / 2.0f);
	Vector2D<float> bottomRight = Vector2D<float>(position.x + radii.x + strokeWidth / 2.0f, position.y + radii.y + strokeWidth / 2.0f);
	return {topLeft, bottomRight};
}

void SVGEllipse::setRadii(const Vector2D<float> &_radii) { this->radii = _radii; }

Vector2D<float> SVGEllipse::getRadii() const {
	return radii;
}
