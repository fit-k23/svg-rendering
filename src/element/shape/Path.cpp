#include "Path.h"

SVGPath::SVGPath() : Element(), points({}), instructions({}) {}

ElementType SVGPath::getTypeName() { return ElementType::Path; }

void SVGPath::dbg() {
	Element::dbg();
	std::cout << "d = "; 
	for (int i = 0; i < (int)instructions.size(); ++i)
		std::cout << instructions << "(" << points[i].x << ", " << points[i].y << ")" << (i + 1 < (int)instructions.size() ? " " : "");
}

std::pair<Vector2D<float>, Vector2D<float>> SVGPath::getBoundingBox() const {
	return std::pair<Vector2D<float>, Vector2D<float>>();
}
