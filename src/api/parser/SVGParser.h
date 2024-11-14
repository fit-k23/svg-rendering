#ifndef SVG_RENDERING_SVGPARSER_H
#define SVG_RENDERING_SVGPARSER_H

#include <iostream>
#include "TParser.h"
#include "../../element/Element.h"

class SVGParser : public TParser<std::vector<Element *>>{
	std::vector<Element *> parse(rapidxml::xml_node<> *pNode, const std::string &attributeName) override;
};

#endif //SVG_RENDERING_SVGPARSER_H
