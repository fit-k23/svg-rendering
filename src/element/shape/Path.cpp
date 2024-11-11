#include "Path.h"

SVGPath::SVGPath() : Element(), points({}) {}

SVGPath::SVGPath(const Vector2D<float>& position, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth, const std::vector<PathPoint>& points) : Element(position, fillColor, strokeColor, strokeWidth), points(points) {}

ElementType SVGPath::getTypeName() { return ElementType::Path; }

void SVGPath::dbg() {
	Element::dbg();
	std::cout << "Set of points: \n"; 
	for (auto &point : points) point.output();
}

std::pair<Vector2D<float>, Vector2D<float>> SVGPath::getBoundingBox() const {
	return std::pair<Vector2D<float>, Vector2D<float>>();
}
