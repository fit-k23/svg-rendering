#include "Path.h"

SVGPath::SVGPath() : Element(), points({}), fillRule(FillRule::NON_ZERO) {}

SVGPath::SVGPath(const Vector2D<float>& position, const SVGColor& fillColor, const SVGColor& strokeColor, float strokeWidth, const std::vector<PathPoint>& points, FillRule fillRule) : Element(position, fillColor, strokeColor, strokeWidth), points(points), fillRule(fillRule) {}

ElementType SVGPath::getTypeName() { return ElementType::Path; }

void SVGPath::dbg() {
	Element::dbg();
	std::cout << "Fill rule = " << (fillRule == FillRule::NON_ZERO ? "nonzero" : "evenodd") << '\n';
	std::cout << "Set of points: \n"; 
	for (auto& point : points) {
		point.output();
		std::cout << '\n';
	}
}

std::pair<Vector2D<float>, Vector2D<float>> SVGPath::getBoundingBox() const {
	return std::pair<Vector2D<float>, Vector2D<float>>();
}

/*
* @brief Set points for path
* @param points new set of points
*/
void SVGPath::setPoints(const std::vector<PathPoint>& points) { this->points = points; }

/*
* @brief Get points for path
* @note This function doesn't change any attributes
*/
std::vector<PathPoint> SVGPath::getPoints() const { return points; }

void SVGPath::setFillRule(FillRule fillRule) { this->fillRule = fillRule; }

FillRule SVGPath::getFillRule() const { return fillRule; }

/*
* @brief Add a point to path
* @param point new point
*/
void SVGPath::addPoint(const PathPoint& point) { points.push_back(point); }

/** @brief Default constructor */
PathPoint::PathPoint() : cmd(' '), pos(Vector2D<float>()) {}

/** @brief Parameterized constructor for normal point */
PathPoint::PathPoint(char cmd, const Vector2D<float>& pos) {
	this->cmd = cmd;
	this->pos = pos;
}

/** @brief Parameterized constructor for arc point */
PathPoint::PathPoint(char cmd, Vector2D<float> pos, Vector2D<float> radii, float xRotation, bool largeArcFlag, bool sweepFlag) {
	this->cmd = cmd;
	this->pos = pos;
	this->radii = radii;
	this->xRotation = xRotation;
	this->largeArcFlag = largeArcFlag;
	this->sweepFlag = sweepFlag;
}

/** @brief Parameterized constructor for quadratic bezier curve */
PathPoint::PathPoint(char cmd, Vector2D<float> pos, Vector2D<float> cen) {
	this->cmd = cmd;
	this->pos = pos;
	this->cen[0] = cen;
}

/** @brief Parameterized constructor for cubic bezier curve */
PathPoint::PathPoint(char cmd, Vector2D<float> pos, Vector2D<float> cen1, Vector2D<float> cen2) {
	this->cmd = cmd;
	this->pos = pos;
	this->cen[0] = cen1;
	this->cen[1] = cen2;
}

void PathPoint::output() {
	std::cout << "Cmd: " << cmd << '\n';
	std::cout << "Pos: " << pos.x << ", " << pos.y << '\n';
	if (tolower(cmd) == 'q' || tolower(cmd) == 'c') {
		std::cout << "Center point: ";
		for (int i = 0; i < 2; ++i)
			std::cout << "(" << cen[i].x << ", " << cen[i].y << ") ";
		std::cout << '\n';
	}
	if (tolower(cmd) == 'a') {
		std::cout << "radii: " << radii.x << ", " << radii.y << '\n';
		std::cout << "x axis rotation: " << xRotation << '\n';
		std::cout << "largeArcFlag = " << largeArcFlag << '\n' << "sweepFlag = " << sweepFlag << '\n';
	}
}