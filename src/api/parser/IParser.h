#ifndef SVG_RENDERING_IPARSER_H
#define SVG_RENDERING_IPARSER_H

#include "../../../lib/rapidxml/rapidxml.hpp"
#include "../../element/Element.h"
#include <iostream>

class IParser {
public:
	virtual Element *parse(rapidxml::xml_node<> *pNode);
	virtual std::string getAttributeName() = 0;
};

#endif //SVG_RENDERING_IPARSER_H
