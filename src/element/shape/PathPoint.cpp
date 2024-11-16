#include "PathPoint.h"

PathPoint::PathPoint() : cmd(' '), pos(Vector2D<float>()) {}
PathPoint::PathPoint(char _cmd, const Vector2D<float> &_pos) : cmd(_cmd), pos(_pos) {}

void PathPoint::output() const {
	std::cout << "Cmd: " << cmd << '\n';
	std::cout << "Pos: " << pos.x << ", " << pos.y << '\n';
}

PathPoint::PathPoint(const PathPoint &other) : cmd(other.cmd), pos(other.pos) {}

void PathPoint::setCMD(char _cmd) { cmd = _cmd; }

std::string PathPoint::getPointType() const {
	return "normal";
}

char PathPoint::getCMD() const { return cmd; }
void PathPoint::setPos(const Vector2D<float> &_pos) { pos = _pos; }

Vector2D<float> PathPoint::getPos() const { return pos; }

PathPoint::operator Vector2D<float>() {
	return pos;
}
