#ifndef SVG_RENDERING_GROUP_H
#define SVG_RENDERING_GROUP_H

#include "Element.h"
#include <vector>

class Group : public Element{
public:
	const ElementType type = ElementType::Group;
	void addShape(Element *shape);
private:
	std::vector<Element *> shapes;
};

#endif //SVG_RENDERING_GROUP_H
