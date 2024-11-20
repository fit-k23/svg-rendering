#include "Group.h"

Group::Group() : elements({}) {}

Group::~Group() {
	for (auto &element: elements) delete element;
}

ElementType Group::getTypeName() {
	return ElementType::Group;
}

void Group::dbg() {
	// TODO: cout data here
}

void Group::addElement(Element *element) {
	elements.push_back(element);
}

std::vector<Element *> Group::getElements() const {
	return elements;
}
