#include "NormPathPoint.h"

NormPathPoint::NormPathPoint() : PathPoint() {}

NormPathPoint::NormPathPoint(char cmd, const Vector2D<float>& pos) : PathPoint(cmd, pos) {}

NormPathPoint::NormPathPoint(const NormPathPoint& other) : PathPoint(other) {}

void NormPathPoint::output() const { PathPoint::output(); }

std::string NormPathPoint::getPointType() const {
	return PathPoint::getPointType();
}
