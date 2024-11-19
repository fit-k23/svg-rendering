#include "LinearGradient.h"

LinearGradient::LinearGradient() : Gradient() {
	pos[0] = Vector2D<float>();
	pos[1] = Vector2D<float>(1.0f, 0.0f);
}

LinearGradient::LinearGradient(const std::string& id, const std::vector<std::string>& transforms, const std::string &units) : Gradient(id, transforms, units) {
	pos[0] = Vector2D<float>();
	pos[1] = Vector2D<float>(1.0f, 0.0f);
}

LinearGradient::LinearGradient(const std::string& id, const std::vector<std::string>& transforms, const std::string &units, Vector2D<float> pos1, Vector2D<float> pos2) : Gradient(id, transforms, units) {
	pos[0] = pos1; 
	pos[1] = pos2;
}

std::string LinearGradient::getType() const { return "linear"; }

void LinearGradient::dbg() const {
	Gradient::dbg();
	std::cout << "x1, y1 = " << pos[0].x << ", " << pos[0].y << '\n';
	std::cout << "x2, y2 = " << pos[1].x << ", " << pos[1].y << '\n';
}

void LinearGradient::setPos(int id, const Vector2D<float> &newPos) { pos[id] = newPos; }

Vector2D<float> LinearGradient::getPos(int id) const { return pos[id]; }
