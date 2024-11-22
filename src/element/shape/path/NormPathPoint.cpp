#include "NormPathPoint.h"

NormPathPoint::NormPathPoint() : PathPoint() {}
NormPathPoint::NormPathPoint(char _cmd, const Vector2D<float> &_pos) : PathPoint(_cmd, _pos) {}
NormPathPoint::NormPathPoint(const NormPathPoint &other) = default;
void NormPathPoint::output() const { PathPoint::output(); }

std::string NormPathPoint::getPointType() const {
	return PathPoint::getPointType();
}
