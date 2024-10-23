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

Element::Element() {
	this->parent = nullptr;
	this->position = {0, 0};
}

Element::Element(Vector2D pos, Element *parent = nullptr) {
	this->position = pos;
	this->parent = parent;
}

Element::~Element() {
}
