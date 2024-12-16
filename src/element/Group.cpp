#include "Group.h"

Group::Group() : attrs({}), elements({}) {}

Group::Group(const GroupAttr &_attrs) : attrs(_attrs) {}

Group::~Group() {
	for (auto &element: elements) 
		delete element;
	std::cout << "Deleting allocated elements in group\n";
}

ElementType Group::getTypeName() { return ElementType::Group; }

void Group::dbg() {
	Element::dbg();
	std::cout << "Attributes: ";
	for (auto &attr : attrs)
		std::cout << "{" << attr.first << ", " << attr.second << "} ";
	std::cout << '\n';
}

void Group::addElement(Element *element) { elements.push_back(element); }
vector<Element *> Group::getElements() const { return elements; }
void Group::addAttr(const string &attr, const string &value) { attrs.emplace_back( attr, value ); }
GroupAttr Group::getAttr() const { return attrs; }
