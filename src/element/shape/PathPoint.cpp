#include "PathPoint.h"

PathPoint::PathPoint() : cmd(' '), pos(Vector2D<float>()) {}

PathPoint::PathPoint(char cmd, const Vector2D<float>& pos) : cmd(cmd), pos(pos) {}

void PathPoint::output() const {
	std::cout << "Cmd: " << cmd << '\n';
	std::cout << "Pos: " << pos.x << ", " << pos.y << '\n';
}

std::string PathPoint::getPointType() const {
	return "normal";
}

PathPoint::PathPoint(const PathPoint& other) : cmd(other.cmd), pos(other.pos) {}

void PathPoint::setCMD(char cmd) { this->cmd = cmd; }

char PathPoint::getCMD() const { return cmd; }

void PathPoint::setPos(const Vector2D<float>& pos) { this->pos = pos; }

Vector2D<float> PathPoint::getPos() const { return pos; }
