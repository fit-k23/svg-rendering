#include "Path.h"

SVGPath::SVGPath() : Element(), points({}), fillRule(FillRule::NON_ZERO) {}

SVGPath::SVGPath(const Vector2D<float>& position, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth, const std::vector<PathPoint *>& points, FillRule fillRule) : Element(position, fillColor, strokeColor, strokeWidth), points(points), fillRule(fillRule) {}

SVGPath::~SVGPath() {
	for (auto &point : points)
		delete point;
}

ElementType SVGPath::getTypeName() { return ElementType::Path; }

void SVGPath::dbg() {
	Element::dbg();
	std::cout << "Fill rule = " << (fillRule == FillRule::NON_ZERO ? "nonzero" : "evenodd") << '\n';
	for (const auto &x : points) x->output();
}

std::pair<Vector2D<float>, Vector2D<float>> SVGPath::getBoundingBox() const {
	return {}; // TODO: How do we find the bounding box of this?
}

void SVGPath::setPoints(const std::vector<PathPoint *> &_points) { points = _points; }

std::vector<PathPoint *> SVGPath::getPoints() const { return points; }

void SVGPath::setFillRule(FillRule _fillRule) { fillRule = _fillRule; }

FillRule SVGPath::getFillRule() const { return fillRule; }

void SVGPath::addPoint(PathPoint *point) { points.push_back(point); }