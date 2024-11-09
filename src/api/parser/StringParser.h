#ifndef SVG_RENDERING_STRINGPARSER_H
#define SVG_RENDERING_STRINGPARSER_H

#include "TParser.h"

class StringParser : public TParser<std::string> {
	std::string parse(rapidxml::xml_node<>* pNode, const std::string& attrName) override;
};

#endif // SVG_RENDERING_STRINGPARSER_H