#include "Group.h"

/**
 * @brief Default constructor for Group class
 * @note Initially has no shapes
 */
Group::Group() : elements({}) {}

/**
 * @brief Destructor 
 */
Group::~Group() {
	for (auto &element: elements)
		delete element;
}

/**
 * @brief Get type name of Group
 * @return ElementType::Group
 */
ElementType Group::getTypeName() {
	return ElementType::Group;
}

/**
 * @brief Print data of group
 * @note This function does not change the class attributes
 */
void Group::dbg() {
	// TODO: cout data here
}

/**
 * @brief Add an element (shape, g, ...) to current group class
 */
void Group::addElement(Element *element) {
	elements.push_back(element);
}

/**
 * @brief Get all elements of current group class
 * @return elements vector
 * @note This function does not change the class attributes
 */
std::vector<Element *> Group::getElements() const {
	return elements;
}
