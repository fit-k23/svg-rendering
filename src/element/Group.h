#ifndef SVG_RENDERING_GROUP_H
#define SVG_RENDERING_GROUP_H

#include "Element.h"
#include <iostream>
#include <vector>
#include <string>

#ifndef GROUP_ATTRIBUTE
#define GROUP_ATTRIBUTE
#define groupAttr std::vector<std::pair<std::string, std::string>>
#endif // GROUP_ATTRIBUTE

class Group : public Element{
private:
	groupAttr attrs;
	std::vector<Element *> elements;
public:
	/**
	 * @brief Default constructor for Group class
	 * @note Initially has no shapes
	 */
	Group();

	/**
	 * @brief Constructor with attributes.
	 */
	Group(const groupAttr& attrs);

	/**
	 * @brief Destructor.to delete allocated memories of Element
	 */
	~Group();

	/**
	 * @brief Get type name of Group
	 * @return ElementType
	 */
	ElementType getTypeName() override;

	/**
	 * @brief Print data of group
	 * @note This function does not change the class attributes
	 */
	void dbg() override;

	/**
	 * @brief Add an svg element (shape, g, ...) to current group class
	 * @param element a pointer to a concrete-Element object
	 */
	void addElement(Element *element);

	/**
	 * @brief Get all elements of current group class
	 * @return vector<Element *>
	 * @note This function does not change the class attributes
	 */
	std::vector<Element *> getElements() const;

	/**
	 * @brief Add an attribute to group 
	 * @param element a pointer to a concrete-Element object
	 */
	void addAttr(const std::string &attr, const std::string &value);

	/**
	 * @brief Get all attributes of group 
	 * @return groupAttr
	 * @note This function does not change the class attributes
	 */
	groupAttr getAttr() const;

};

#endif //SVG_RENDERING_GROUP_H
