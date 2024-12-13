#include "QuadPathPoint.h"

QuadPathPoint::QuadPathPoint(char _cmd, const Vector2D<float> &_pos, const Vector2D<float> &_cen) : PathPoint(_cmd, _pos), cen(_cen) {}
void QuadPathPoint::setCen(const Vector2D<float> &_cen) { cen = _cen; }
Vector2D<float> QuadPathPoint::getCen() const { return cen; }

void QuadPathPoint::output() const {
	PathPoint::output();
	std::cout << "Center point: " << cen.x << ", " << cen.y << '\n';
}

std::string QuadPathPoint::getPointType() const {
	return "quad";
}
