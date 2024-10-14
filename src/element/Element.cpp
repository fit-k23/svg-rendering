#include "Element.h"

Element *Element::setParent(Element *parent) {
	if (parent != nullptr) {
		this->parent = parent;
	}
	return this;
}

Element *Element::getParent() { return this->parent; }

void Element::cleanUp() {
}

Element::~Element() {
}
