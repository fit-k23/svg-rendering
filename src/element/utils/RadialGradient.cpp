#include "RadialGradient.h"

RadialGradient::RadialGradient() : Gradient() {
	pos = Vector2D<float>(0.5f, 0.5f);
	radius = 0.5f;
	focal = pos; // TODO: maybe change 
}

RadialGradient::RadialGradient(const std::string& id, const std::vector<std::string>& transforms, const std::string &units) : Gradient(id, transforms, units) {
	pos = Vector2D<float>(0.5f, 0.5f);
	radius = 0.5f;
	focal = pos; // TODO: maybe change
}

RadialGradient::RadialGradient(const std::string& id, const std::vector<std::string>& transforms, const std::string &units, const Vector2D<float>& pos, float radius, const Vector2D<float>& focal) : Gradient(id, transforms, units), pos(pos), radius(radius), focal(focal) {}

std::string RadialGradient::getType() const { return "radial"; }

void RadialGradient::dbg() const {
	Gradient::dbg();
	std::cout << "cx, cy = " << pos.x << ", " << pos.y << '\n';
	std::cout << "r = " << radius << '\n' << " fx, fy = " << focal.x << ", " << focal.y << '\n';
}

void RadialGradient::setPos(const Vector2D<float>& pos) { this->pos = pos; }

Vector2D<float> RadialGradient::getPos() const { return pos; }

void RadialGradient::setRadius(float radius) { this->radius = radius; }

float RadialGradient::getRadius() const { return radius; }

void RadialGradient::setFocal(const Vector2D<float>& focal) { this->focal = focal; }

Vector2D<float> RadialGradient::getFocal() const { return focal; }


