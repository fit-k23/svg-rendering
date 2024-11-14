#ifndef SVG_RENDERING_COLOR_PARSER_H
#define SVG_RENDERING_COLOR_PARSER_H

#include "TParser.h"
#include "../../element/utils/SVGColor.h"

class ColorParser : public TParser<SVGColor>{
	SVGColor parse(rapidxml::xml_node<> *pNode, const std::string &attributeName) override;
};

#endif //SVG_RENDERING_COLOR_PARSER_H
