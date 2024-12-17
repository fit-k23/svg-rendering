#include "RadialGradient.h"

RadialGradient::RadialGradient() {
	pos = Vector2D<float>(0.5f, 0.5f);
	radius = 0.5f;
	focal = pos; // TODO: maybe change 
}

RadialGradient::RadialGradient(const string &id, const vector<string> &transforms, const string &units) : Gradient(id, transforms, units) {
	pos = Vector2D<float>(0.5f, 0.5f);
	radius = 0.5f;
	focal = pos; // TODO: maybe change
}

RadialGradient::RadialGradient(const string &id, const vector<string> &transforms, const string &units, const Vector2D<float> &pos, float radius, const Vector2D<float> &focal) : Gradient(id, transforms, units), pos(pos), radius(radius), focal(focal) {}

void RadialGradient::dbg() const {
	Gradient::dbg();
	std::cout << "Center: {" << pos.x << ", " << pos.y << "}\n"
				 "Radius: " << radius << "\n"
				 "Focal: {" << focal.x << ", " << focal.y << "}\n";
}

void RadialGradient::setPos(const Vector2D<float> &_pos) { pos = _pos; }
void RadialGradient::setRadius(float _radius) { radius = _radius; }
void RadialGradient::setFocal(const Vector2D<float> &_focal) { focal = _focal; }
Vector2D<float> RadialGradient::getPos() const { return pos; }
float RadialGradient::getRadius() const { return radius; }
Vector2D<float> RadialGradient::getFocal() const { return focal; }


