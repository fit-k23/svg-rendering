#ifndef SVG_RENDERING_TPARSER_H
#define SVG_RENDERING_TPARSER_H

#include <iostream>
#include <sstream>
#include <algorithm>
#include "IParser.h"
#include "../../../lib/rapidxml/rapidxml.hpp"

template<typename T>
class TParser : public IParser {
public:
	virtual T parse(rapidxml::xml_node<> *pNode, const std::string &attrName) = 0;
};

#endif //SVG_RENDERING_TPARSER_H
