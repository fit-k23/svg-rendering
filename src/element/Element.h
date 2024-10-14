#ifndef SVG_RENDERING_ELEMENT_H
#define SVG_RENDERING_ELEMENT_H

#include "utils/ElementType.h"
#include "Vector2D.h"

class Element{
public:
	const ElementType type = ElementType::Unknown;
	Element *setParent(Element *parent);
	Element *getParent();
	Element *addChild(Element *child);
private:
	Element *parent;
	Element *children;
	Vector2D position;
	void cleanUp();
	~Element();
};

#endif //SVG_RENDERING_ELEMENT_H
