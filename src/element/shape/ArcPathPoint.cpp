#include "ArcPathPoint.h"

ArcPathPoint::ArcPathPoint() : PathPoint(), radii(Vector2D<float>()), xRotation(0.0f), largeArcFlag(false), sweepFlag(false) {}

ArcPathPoint::ArcPathPoint(char cmd, const Vector2D<float>& pos) : PathPoint(cmd, pos), radii(Vector2D<float>()), xRotation(0.0f), largeArcFlag(false), sweepFlag(false) {}

ArcPathPoint::ArcPathPoint(char cmd, const Vector2D<float>& pos, const Vector2D<float>& radii, float xRotation, bool largeArcFlag, bool sweepFlag) : PathPoint(cmd, pos), radii(radii), xRotation(xRotation), largeArcFlag(largeArcFlag), sweepFlag(sweepFlag) {}

ArcPathPoint::ArcPathPoint(const ArcPathPoint& other) : PathPoint(other), radii(other.radii), xRotation(other.xRotation), largeArcFlag(other.largeArcFlag), sweepFlag(other.sweepFlag) {}

void ArcPathPoint::setRadii(const Vector2D<float>& radii) { this->radii = radii; }

Vector2D<float> ArcPathPoint::getRadii() const { return radii; }

void ArcPathPoint::setXRotation(float xRotation) { this->xRotation = xRotation; }

float ArcPathPoint::getXRotation() const { return xRotation; }

void ArcPathPoint::setLargeArcFlag(bool largeArcFlag) { this->largeArcFlag = largeArcFlag; }

bool ArcPathPoint::getLargeArcFlag() const { return largeArcFlag; }

void ArcPathPoint::setSweepFlag(bool sweepFlag) { this->sweepFlag = sweepFlag; }

bool ArcPathPoint::getSweepFlag() const { return sweepFlag; }

void ArcPathPoint::output() const {
	PathPoint::output();
	std::cout << "radii: " << radii.x << ", " << radii.y << '\n';
	std::cout << "x axis rotation: " << xRotation << '\n';
	std::cout << "largeArcFlag = " << largeArcFlag << '\n' << "sweepFlag = " << sweepFlag << '\n';
}
