#ifndef SVG_RENDERING_PATH_H
#define SVG_RENDERING_PATH_H

#include "../Element.h"

class Path : public Element{
public:
	const ElementType type = ElementType::Path;
};


#endif //SVG_RENDERING_PATH_H
