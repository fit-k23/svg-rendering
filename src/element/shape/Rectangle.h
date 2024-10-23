#ifndef SVG_RENDERING_RECTANGLE_H
#define SVG_RENDERING_RECTANGLE_H

#include "../Element.h"

class Rectangle : public Element {
public:
	const ElementType type = ElementType::Rect;
private:
	int x;
	int y;
	int width;
	int height;
	int rx;
	int ry;
};

#endif //SVG_RENDERING_RECTANGLE_H
