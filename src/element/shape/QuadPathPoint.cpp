#include "QuadPathPoint.h"

QuadPathPoint::QuadPathPoint() : PathPoint(), cen(Vector2D<float>()) {}

QuadPathPoint::QuadPathPoint(char cmd, const Vector2D<float>& pos) : PathPoint(cmd, pos), cen(Vector2D<float>()) {}

QuadPathPoint::QuadPathPoint(char cmd, const Vector2D<float>& pos, const Vector2D<float>& cen) : PathPoint(cmd, pos), cen(cen) {}

QuadPathPoint::QuadPathPoint(const QuadPathPoint& other) : PathPoint(other), cen(other.cen) {}

void QuadPathPoint::setCen(const Vector2D<float>& cen) { this->cen = cen; }

Vector2D<float> QuadPathPoint::getCen() const { return cen; }

void QuadPathPoint::output() const {
	PathPoint::output();
	std::cout << "Center point: " << cen.x << ", " << cen.y << '\n';
}
