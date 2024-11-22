#include "CubicPathPoint.h"

CubicPathPoint::CubicPathPoint() : PathPoint() {
	for (auto &i : cen)
		i = Vector2D<float>();
}

CubicPathPoint::CubicPathPoint(char _cmd, const Vector2D<float> &_pos) : PathPoint(_cmd, _pos) {
	for (auto &i : cen)
		i = Vector2D<float>();
}

CubicPathPoint::CubicPathPoint(char _cmd, const Vector2D<float> &_pos, const Vector2D<float> &_cen) : PathPoint(_cmd, _pos) {
	this->cen[0] = _cen;
}

CubicPathPoint::CubicPathPoint(char _cmd, const Vector2D<float> &_pos, const Vector2D<float> &_cen1, const Vector2D<float> &_cen2) : PathPoint(_cmd, _pos) {
	cen[0] = _cen1;
	cen[1] = _cen2;
}

CubicPathPoint::CubicPathPoint(const CubicPathPoint &other) : PathPoint(other) {
	cen[0] = other.cen[0];
	cen[1] = other.cen[1];
}

void CubicPathPoint::setCen(const Vector2D<float> &_cen, int id) { cen[id] = _cen; }

Vector2D<float> CubicPathPoint::getCen(int id) const { return cen[id]; }

void CubicPathPoint::output() const {
	PathPoint::output();
	std::cout << "Center point: ";
	for (const auto & i : cen)
		std::cout << "(" << i.x << ", " << i.y << ") ";
	std::cout << '\n';
}

std::string CubicPathPoint::getPointType() const {
	return "cubic";
}
