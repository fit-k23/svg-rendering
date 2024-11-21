#include "Group.h"

Group::Group() : attrs({}), elements({}) {}

Group::Group(const groupAttr& attrs) : attrs(attrs) {}

Group::~Group() {
	for (auto &element: elements) 
		delete element;
	std::cout << "Deleting allocated elements in group\n";
}

ElementType Group::getTypeName() { return ElementType::Group; }

void Group::dbg() {
	Element::dbg();
}

void Group::addElement(Element *element) { 
	elements.push_back(element);
}

std::vector<Element*> Group::getElements() const { return elements; }

void Group::addAttr(const std::string& attr, const std::string& value) { attrs.push_back({ attr, value }); }

groupAttr Group::getAttr() const { return attrs; }
