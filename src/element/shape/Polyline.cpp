#include "Polyline.h"

SVGPolyline::SVGPolyline() : Element(), points{}, fillRule(FillRule::NON_ZERO) {}
SVGPolyline::SVGPolyline(const Vector2D<float> &_position, const SVGColor &_fillColor, const SVGColor &_strokeColor, float _strokeWidth, const std::vector<Vector2D<float>> &_points) : Element(_position, _fillColor, _strokeColor, _strokeWidth), points(_points), fillRule(FillRule::NON_ZERO) {}
SVGPolyline::SVGPolyline(const Vector2D<float> &_position, const SVGColor &_fillColor, const SVGColor &_strokeColor, float _strokeWidth, const std::vector<Vector2D<float>> &_points, FillRule _fillRule) : Element(_position, _fillColor, _strokeColor, _strokeWidth), points(_points), fillRule(_fillRule) {}
SVGPolyline::SVGPolyline(const SVGPolyline &other) : Element(other), points(other.points), fillRule{other.fillRule} {}

ElementType SVGPolyline::getTypeName() { return ElementType::Polyline; }

void SVGPolyline::dbg() {
	Element::dbg();
	std::cout << "Fill rule: " << (fillRule == FillRule::NON_ZERO ? "nonzero" : "evenodd") << '\n';
	std::cout << "Set of lines are ";
	for (auto &point : points) {
		std::cout << "(" << point.x << ", " << point.y << ")";
	}
}

std::pair<Vector2D<float>, Vector2D<float>> SVGPolyline::getBoundingBox() const {
	Vector2D<float> topLeft = {99999.0f, 99999.0f};
	Vector2D<float> bottomRight = {-99999.0f, -99999.0f};
	for (int i = 0; i < (int) points.size(); ++i) {
		Vector2D<float> sta = points[i];
		Vector2D<float> fin = points[(i + 1) % points.size()];
		topLeft.x = (std::min)(topLeft.x, (std::min)(sta.x, fin.x));
		bottomRight.x = (std::max)(bottomRight.x, (std::max)(sta.x, fin.x));
		topLeft.y = (std::min)(topLeft.y, (std::min)(sta.y, fin.y));
		bottomRight.y = (std::max)(bottomRight.y, (std::max)(sta.y, fin.y));
	}
	topLeft.x += strokeWidth / 2.0f;
	topLeft.y += strokeWidth / 2.0f;
	bottomRight.x += strokeWidth / 2.0f;
	bottomRight.y += strokeWidth / 2.0f;
	return {topLeft, bottomRight};
}

void SVGPolyline::setPoints(const std::vector<Vector2D<float>> &_points) { points = _points; }
void SVGPolyline::addPoints(const Vector2D<float> &point) { points.push_back(point); }
std::vector<Vector2D<float>> SVGPolyline::getPoints() const { return points; }
void SVGPolyline::setFillRule(const FillRule &_fillRule) { fillRule = _fillRule; }
FillRule SVGPolyline::getFillRule() const { return fillRule; }

