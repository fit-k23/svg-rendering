#ifndef SVG_RENDERING_CIRCLE_H
#define SVG_RENDERING_CIRCLE_H

#include "Ellipse.h"

class Circle : public Ellipse{
public:
	const ElementType type = ElementType::Circle;
};


#endif //SVG_RENDERING_CIRCLE_H
