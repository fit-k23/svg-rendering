#include "CubicPathPoint.h"

CubicPathPoint::CubicPathPoint() : PathPoint() {
	for (int i = 0; i < 2; ++i)
		cen[i] = Vector2D<float>();
}

CubicPathPoint::CubicPathPoint(char cmd, const Vector2D<float>& pos) : PathPoint(cmd, pos) {
	for (int i = 0; i < 2; ++i)
		cen[i] = Vector2D<float>();
}

CubicPathPoint::CubicPathPoint(char cmd, const Vector2D<float>& pos, const Vector2D<float>& cen) : PathPoint(cmd, pos) {
	this->cen[0] = cen;
}

CubicPathPoint::CubicPathPoint(char cmd, const Vector2D<float>& pos, const Vector2D<float>& cen1, const Vector2D<float>& cen2) : PathPoint(cmd, pos) {
	cen[0] = cen1;
	cen[1] = cen2;
}

CubicPathPoint::CubicPathPoint(const CubicPathPoint& other) : PathPoint(other) {
	cen[0] = other.cen[0];
	cen[1] = other.cen[1];
}

void CubicPathPoint::setCen(const Vector2D<float>& cen, int id) { this->cen[id] = cen; }

Vector2D<float> CubicPathPoint::getCen(int id) const { return cen[id]; }

void CubicPathPoint::output() const {
	PathPoint::output();
	std::cout << "Center point: ";
	for (int i = 0; i < 2; ++i)
		std::cout << "(" << cen[i].x << ", " << cen[i].y << ") ";
	std::cout << '\n';
}
