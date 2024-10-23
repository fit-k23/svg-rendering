#ifndef SVG_RENDERING_TEXT_H
#define SVG_RENDERING_TEXT_H

#include "../Element.h"

class Text : public Element{
public:
	const ElementType type = ElementType::Text;
};

#endif //SVG_RENDERING_TEXT_H
