#ifndef SVG_RENDERING_GROUP_H
#define SVG_RENDERING_GROUP_H

#include "Element.h"
#include <iostream>
#include <vector>

class Group : public Element{
private:
	std::vector<Element *> elements;
public:
	/**
	 * @brief Default constructor for Group class
	 * @note Initially has no shapes
	 */
	Group();

	/** @brief Destructor */
	~Group();

	/**
	 * @brief Get type name of Group
	 * @return ElementType::Group
	*/
	ElementType getTypeName() override;

	/**
	 * @brief Print data of group
	 * @note This function does not change the class attributes
	*/
	void dbg() override;

	/**
	 * @brief Add an element (shape, g, ...) to current group class
	*/
	void addElement(Element *element);

	/**
	 * @brief Get all elements of current group class
	 * @return elements vector
	 * @note This function does not change the class attributes
	*/
	std::vector<Element *> getElements() const;
};

#endif //SVG_RENDERING_GROUP_H
