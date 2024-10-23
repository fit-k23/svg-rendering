#ifndef SVG_RENDERING_POLYLINE_H
#define SVG_RENDERING_POLYLINE_H

#include "../Element.h"

class Polyline : public Element {
public:
	const ElementType type = ElementType::Polyline;
};

#endif //SVG_RENDERING_POLYLINE_H
