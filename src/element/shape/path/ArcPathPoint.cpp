#include "ArcPathPoint.h"

ArcPathPoint::ArcPathPoint() : radii(Vector2D<float>()), xRotation(0.0f), largeArcFlag(false), sweepFlag(false) {}
ArcPathPoint::ArcPathPoint(char _cmd, const Vector2D<float> &_pos) : PathPoint(_cmd, _pos), radii(Vector2D<float>()), xRotation(0.0f), largeArcFlag(false), sweepFlag(false) {}
ArcPathPoint::ArcPathPoint(char _cmd, const Vector2D<float> &_pos, const Vector2D<float> &_radii, float _xRotation, bool _largeArcFlag, bool _sweepFlag) : PathPoint(_cmd, _pos), radii(_radii), xRotation(_xRotation), largeArcFlag(_largeArcFlag), sweepFlag(_sweepFlag) {}

Vector2D<float> ArcPathPoint::getRadii() const { return radii; }
float ArcPathPoint::getXRotation() const { return xRotation; }
bool ArcPathPoint::getLargeArcFlag() const { return largeArcFlag; }
bool ArcPathPoint::getSweepFlag() const { return sweepFlag; }

void ArcPathPoint::setRadii(const Vector2D<float> &_radii) { radii = _radii; }
void ArcPathPoint::setXRotation(float _xRotation) { xRotation = _xRotation; }
void ArcPathPoint::setLargeArcFlag(bool _largeArcFlag) { largeArcFlag = _largeArcFlag; }
void ArcPathPoint::setSweepFlag(bool _sweepFlag) { sweepFlag = _sweepFlag; }

void ArcPathPoint::output() const {
	PathPoint::output();
	std::cout << "Radius: (" << radii.x << ", " << radii.y << ")\n";
	std::cout << "X-axis rotation: " << xRotation << '\n';
	std::cout << "LargeArcFlag = " << largeArcFlag << '\n' << "SweepFlag = " << sweepFlag << '\n';
}

std::string ArcPathPoint::getPointType() const {
	return "arc";
}
