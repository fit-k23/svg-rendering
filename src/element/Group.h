#ifndef SVG_RENDERING_GROUP_H
#define SVG_RENDERING_GROUP_H

#include <iostream>
#include <vector>
#include <string>
#include "Element.h"

using std::vector;
using std::string;
using std::pair;

#define GroupAttr vector<pair<string, string>>

/**
 * @brief Group is a composite class that is implemented using composite design pattern.
 * @note A group object can contain several shapes or other groups
 */

class Group final : public Element{
	GroupAttr attrs;
	std::vector<Element *> elements;
public:
	Group();

	/** @brief Constructor with attributes. */
	Group(const GroupAttr &attrs);

	/** @brief Destructor.to delete allocated memories of Element */
	~Group() override;

	/** @brief Get type name of Group */
	ElementType getTypeName() override;

	/** @brief Print data of group */
	void dbg() override;

	/**
	 * @brief Add an svg element (shape, g, ...) to current group class
	 * @param element A pointer to a concrete-Element object
	 */
	void addElement(Element *element);

	/** @brief Get all elements of current group class */
	std::vector<Element *> getElements() const;

	/** @brief Add an attribute to group */
	void addAttr(const std::string &attr, const std::string &value);

	/** @brief Get all attributes of group */
	GroupAttr getAttr() const;
};

#endif //SVG_RENDERING_GROUP_H
